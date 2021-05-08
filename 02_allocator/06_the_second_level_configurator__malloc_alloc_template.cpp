

/*
 * Date:2021-05-08 15:38
 * filename:06_the_second_level_configurator__malloc_alloc_template.cpp
 *
 */

/*
 *
SGI第二级配置器的做法是:如果区块够大,超过128bytes时,就移交第一级配置器处理.当区块小于128bytes时,则以内存池(memory pool)管理
此法又称为次级配置(sub-allocation):每次配置一大块内存,并维护对应之自由链表(free-list).
下次若再有相同大小的内存需求,就直接从free-lists中拔出.如果客户端释还小额区块,就由配置器回收到free-lists中--配置器除了负责
配置,也负责回收.为了方便管理,SGI第二级配置器会主动将任何小额区块的内存需求量上调至8的背书,并维护16个free-lists,各自管理大小
分别为8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128bytes的小额区块.
 *
 */

/* free-lists的结点结构如下 */
union obj
{
	union obj * free_list_link;
	char client_data[1];
};

/*
 * 上述obk所用的是union,由于union之故,从其第一字段观之,obj可被视为一个指针,指向相同形式的另一个obj.
 * 从其第二字段观之,obj可被视为一个指针,指向实际区块.
 * 一物二用的结果是,不会为了维护链表所必须的指针而造成内存的另一种浪费
 * 这种技巧在强型(strongly typed)语言如Java中行不通,但是在非强型语言如C++中十分普遍
 */

/* 下面是第二级配置器的部分实现内容 */
enum { __ALIGN = 8 };
enum {__MAX_BYTES = 128};
enum {__NFREELISTS = __MAX_BYTES/__ALIGN};

//第二级配置器
template <bool threads,int inst>
class __default_alloc_template
{
private:
	//round_up 将bytes 上调至8的倍数
	static size_t ROUND_UP(size_t bytes)
	{
		return (((bytes) + __ALIGN - 1) & ~(__ALIGN - 1));
	}
private:
	union obj
	{
		union obj * free_list_link;
		char client_data[1];
	};
private:
	//16个free-lists
	static obj * volatile free_list[__NFREELISTS];
	//以下函数根据区块大小，决定使用第n号free-list。n从0起算
	static sizt_t FREELIST_INDEX(size_t bytes){
		return ((bytes) + __ALIGN - 1/__ALIGN - 1);
	}

	//返回一个大小为n的对象，并可能加入大小为n的其它区块到free list
	static void *refill(size_t n);

	//如果一大块空间，可容纳nobjs个大小为"size"的区块
	//如果配置nobjs个区块有所不便，nobjs可能会降低
	static char *chunk_alloc(size_t size,int &nobjs);

	//Chunk allocation state
	static char *start_free;
	static char *end_free;
	static size_t head_size;

public:
	static void * allocate(size_t n){}
	static void deallocate(void *p,size_t n) {}
	static void * reallocate(void *p,size_t old_sz,size_t new_sz);
};

//以下是static data member的定义与初值设定
template <bool threads,int inst>
char *__default_alloc_template<threads,inst>::start_free = 0;

template <bool threads,int inst>
char *__default_alloc_template<threads,inst>::end_free = 0;

template <bool threads,int inst>
char *__default_alloc_template<threads,inst>::heap_size = 0;

template <bool threads,int inst>
__default_alloc_template<threads,inst>::obj * valatile
__default_alloc_template<threads,inst>::free_list[__NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

