

/*
 * Date:2021-05-11 19:02
 * filename:10_memory_pool.cpp
 *
 */

//从内存池中取空间给free list使用,是chunk_alloc()的工作

//假设参数nobjs是pass by reference

template <bool threads,int inst>
char * __default_alloc_template<threads,inst>::chunk_alloc(size_t size,int& nobjs)
{
	char * result;
	size_t total_bytes = size * nobjs;
	size_t bytes_left = end_free - start_free;//内存池剩余空间		

	if(bytes_left >= total_bytes)
	{
		//内存池剩余空间完全满足需求量
		result = start_free;
		start_free += total_bytes;
		return(result);
	}else if(bytes_left >= size)
	{
		//内存池剩余空间不能完全满足需求量,但足够供应一个(含)以上的区块
		nobjs = bytes_left / size;
		total_bytes  = size * nobjs;
		result = start_free;
		start_free += total_bytes;
		return (result);
	}else
	{
		//内存池剩余空间连一个区块的大小都无法提供
		size_t bytes_to_get = 2 * total_bytes + ROUND_UP(head_size >> 4);

		//试着让内存池中的残余零头还有利用价值
		if(bytes_left > 0 )
		{
			//先配给适当的free list
			//首先寻找适当的free list
			obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);

			//调整free list，将内存池中的残余空间编入
			((obj *)start_free)->free_list_link = *my_free_list;
			*my_free_list = (obj *)start_free;
		}

		//配置heap空间，用来补充内存池
		start_free = (char *)malloc(bytes_to_get);
		if(0 == start_free){
			//heap 空间不足，malloc()失败
			int i;
			obj * volatile * my_free_list,*p;
			//试着验视我们手上拥有的东西,这不会造成伤害,我们不打算尝试配置
			//较小的区块,因为那在多进程(multi-process)机器上容易导致灾难
			//以下搜寻适当的free list
			//所谓适当是指"尚有未用区块,且区块够大"之free list
			for(i = size;i <= __MAX_BYTES;i += __ALIGN){
				my_free_list = free_list + FREELIST_INDEX(i);
				p = *my_free_list;
				if(0 != p)
				{
					//free list内尚有未用区块
					*my_free_list = p->free_list_link;
					start_free = (char *)p;
					end_free = start_free + i;
					//递归调用自己,为了修正nobjs
					return (chunk_alloc(size,nobjs));
					//注意,任何残余零头终将被编入适当的free-list中备用
				}
			}
			end_free = 0;		//如果出现意外,到处都没内存可用
			//调用第一级配置器,看看out-of-memory机制能否尽点力
			start_free = (char *)malloc_alloc::allocate(bytes_to_get);
			//这会导致跑出异常(exception)，或内存不足的情况获得改善
		}
		heap_size += bytes_to_get;
		end_free = start_free + bytes_to_get;

		//递归调用自己,为了修正nobjs
		return (chunk_alloc(size,nobjs));
	}
}

/*
 * chunk_alloc()函数以end_free - start_free来判断内存池的水量
 * 如果水量充足,就直接调出20个区块返回给free list.如果水量不足以提供20个区块,
 * 但还足够提供一个以上的区块,就拨出这不足20个区块的空间出去,这时候其pass by reference的nobjs参数
 * 将被修改为实际能够供应的区块数。如果内存池连一个区块空间都无法供应,对客端显然无法交代,此时便需利用malloc()
 * 从heap中配置内存，为内存池注入源头活水以应付需求。新水量的大小为需求量的两倍,再加上一个随着配置次数增加而
 * 愈来愈大的附加量
 */

