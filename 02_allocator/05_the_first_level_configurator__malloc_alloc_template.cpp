

/*
 * Date:2021-05-07 20:28
 * filename:05_第一级配置器__malloc_alloc_template.cpp
 *
 */

#if 0
#include <new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include <iostream>
#define __THROW_BAD_ALLOC cerr << "out of memory" << endl;exit(1)
#endif 

//malloc-based allocator 慢
//一般而言是thread-safe,并且对于空间的运用比较高效(efficient)

template<int inst>
class __malloc_alloc_template{
private:
	//以下函数处理内存不足的情况
	//oom:out of memory
	static void *oom_malloc(size_t);
	static void *oom_realloc(void *,size_t);
	static void (* __malloc_alloc_oom_handler)();
public:
	static void * allocate(size_t n)
	{
		void *result = malloc(n);
		//以下无法满足需求时，改用oom_malloc()
		if(0 == result) result = oom_malloc(n);
		return result;
	}

	static void deallocate(void *p,size_t /* n */)
	{
		free(p);//一级配置器直接用free()
	}

	static void * reallocate(void *p,size_t /* old_sz */,size_t new_sz)
	{
		void * result = realloc(p,new_sz);

		//以下无法满足需求时，改用oom_realloc()
		if( 0 == result ) result = oom_realloc(p,new_sz);
		return result;
	}

	/*
	 * Date:2021-05-07 20:41
	 * 不太明白下面这个函数的操作
	 */

	//以下仿真C++的set_new_handler()，通过它指定自己的out-of-memory handler
	static void (* set_malloc_handler(void (*f)())) ()
	{
		void (* old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return (old);
	}
};

//malloc_alloc out-of-memory handling
template <int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template<int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n)
{
	void (* my_malloc_handler)();
	void *result;

	for(;;)	//不断尝试释放、配置、再释放、再配置...
	{
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(n);
		if(result) return (result);
	}
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p,size_t n)
{
	void (* my_malloc_handler)();
	void *result;

	for(;;)
	{
		my_malloc_handler = __malloc_alloc_oom_handler;
		if(0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(p,n);
		if(result) return (result);
	}
}

typedef __malloc_alloc_template<0> malloc_alloc;



