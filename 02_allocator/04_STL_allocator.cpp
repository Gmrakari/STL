

/*
 * Date:2021-05-06 19:45
 * filename:04_STL_allocator.cpp
 *
 */

/*
 * STL allocator
 * 内存配置操作由alloc:allocate()负责，内存释放操作由alloc::deallocate()负责
 * 对象构造操作由::construct()负责，对象析构操作由::destroy()负责
 *
 */

/*
 *
#include <stl_alloc.h> 			//负责内存空间的配置和释放
#include <stl_construct.h> 		//负责对象内容的构造和析构

*/

/*
 *
#include <new.h>

*/
template <class T1,class T2>
inline void construct(T1* p,const T2& value)
{
	new(p) T1(value);						//placement new;调用T1::T1(value);
}

//destroy version 1.0,accept one pointer
template <class T>
inline void destroy(T* pointer)
{
	pointer->~T();
}

//destroy version 2.0,accept two iterator
//此函数设法找出元素的数值型别，进而利用__type_traits<>求取最适当措施
template <class ForwardIterator>
inline void destroy(ForwardIterator first,ForwardIterator last)
{
	__destroy(first,last,value_type(first));
}

//判断元素的数值型别(value type)是否有trivial destructor
template <class ForwardIterator,class T>
inline void __destroy(ForwardIterator first,ForwardIterator last,T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destroy_aux(first,last,trivial_destructor());
}

//如果元素的数值型别(value type)有non-trivial destructor***
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator first,ForwardIterator last,__false_type)
{
	for(;first < last;++first)
		destroy(&*first);
}

//如果元素的数值型别(value type) 有trivial destructor***
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator,__true_type) {}

//以下是destroy() 第二个版本对迭代器为char *和wchar_t* 的特化版
inline void destroy(char*,char*) {}
inline void destroy(wchar_t*,wchar_t*) {}


