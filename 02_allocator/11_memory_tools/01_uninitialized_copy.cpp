

/*
 * Date:2021-05-13 20:51
 * filename:01_uninitialized_copy.cpp
 *
 */

/*
 * uninitialized_copy()使我们能够将内存的配置与对象的构造行为分离开来。
 * 如果作为输出目的地的[result,result + (last - first)]范围内的每一个迭代器都指向未初始化区域
 * 则uninitialized_copy()会使用copy constructor,给身为输入来源之[first,last]范围内的每一个对象
 * 产生一粉复制品,放进输入范围中。
 * 换句话说,针对输入范围内的每一个迭代器i,该函数会调用construct(&*(result + (i - first)), *i)
 * 产生*i的复制品,放置于输出范围的相对位置上
 *
 *
 * 全区间构造函数(range constructor)通常以两个步骤完成:
 * 配置内存区块,足以包含范围内的所有元素
 *
 * C++标准规格书要求uninitialized_copy() 
 * 具有"commit or rollback" --> 意思是要么"构造处所有必要元素",
 * 要么"当有任何一个copy constructor 失败时" 不构造任何东西
 */


template <class InputIterator,class ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result)
{
	return __uninitialized_copy(first,last,result,value_type(result));
}


template <class InputIterator,class ForwardIterator,class T>
inline ForwardIterator __uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result,T*)
{
	
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_copy_aux(first,last,result,is_POD());
}

template <class InputIterator,class ForwardIterator>
inline ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__true_type)
{
	return copy(first,last,result);
}

template <class InputIterator,class ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,ForwardIterator result,__false_type)
{
	ForwardIterator cur = result;
	for(; first != last;++first,++cur)
		construct(&*cur,*first);		//必须一个一个元素地构造,无法批量进行
	return cur;
}

/*
 * 针对char *和wchar_t *两种型别，可以采用最具有效率地做法memmove(直接移动内存内容)来执行复制行为
 * SGI得以为这两种型别设计一份特化版本
 */

//const char* version
inline char* uninitialized_copy(const char* first,const char* last,char* result)
{
	memmove(result,first,last - first);
	return result + (last - first);
}

//const wchar_t* version

inline wchar_t* uninitialized_copy(const wchar_t* first,const wchar_t* last,wchar_t* result)
{
	memmove(result,first,sizeof(wchar_t) * (last - first));
	return result + (last - first);
}
