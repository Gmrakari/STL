

/*
 * Date:2021-05-08 16:21
 * filename:08_deallocate_fun.cpp
 *
 */


/*
 *
身为一个$配置器,__default_alloc_template拥有配置器的标准接口函数deallocate().
此函数首先判断区块大小，大于128bytes就调用第一级配置器，小于128bytes就检查对应的free list,将区块回收。
 *
 */

// p 不可以是 0
static void deallocate(void *p,size_t n)
{
	obj *q = (obj *)p;
	obj * volatile * my_free_list;

	// 大于128就调用第一级配置器
	if(n > (size_t) __MAX_BYTES)
	{
		malloc_alloc::deallocate(p,n);
		return ;
	}

	//寻找对应的free list
	my_free_list = free_list + FREELIST_INDEX(n);

	//调整free list,回收区块
	q->free_list_link = *my_free_list;
	*my_free_list = q;
}


