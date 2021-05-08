

/*
 * Date:2021-05-08 16:12
 * filename:07_allocate_fun.cpp
 *
 */

/*
 *
身为一个配置器,__default_alloc_template拥有配置器的标准接口函数allocate().
此函数首先判断区块大小，大于128bytes就调用第一级配置器，小于128bytes就检查对应的free list。
如果free list之内有可用的区块，就直接拿来用，如果没有可用区块，就将区块大小上调8倍数边界，
然后调用refill(),准备为free list重新填充空间
 *
 */

// n must be > 0
static void * allocate(size_t n)
{
	obj * volatile *my_free_list;
	obj * result;

	// > 128 the first level configurator
	if(n > (size_t) __MAX_BYTES){
		return (malloc_alloc::allocate(n));
	}

	//find properly in 16-free lists
	my_free_list = free_list + FREELIST_INDEX(n);
	result = *my_free_list;
	if(result == 0)
	{
		void *r = refill(ROUND_UP(n));
		return r;
	}

	//resize free list
	*my_free_list = result->free_list_link;
	return (result);
}
