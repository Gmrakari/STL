

/*
 * Date:2021-05-13 21:00
 * filename:02_uninitialized_fill.cpp
 *
 */

template <class ForwardIterator,class T>
void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x);

/*
 * uninitialized_fill()也能够使我们将内存配置与对象的构造行为分离开来.
 * 如果[first,last]范围内的每个迭代器都指向未初始化的内存，
 * 那么uninitialized_fill()会产生该范围内x的复制品
 *
 * 换句话说,uninitialized_fill()会针对操作范围内的每个迭代器i,
 * 调用construct(&*i,x),在i所指之处产生x的复制品
 *
 */


template <class ForwardIterator,class T>
void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x)
{
	__uninitialized_fill(first,last,x,value_type(first));
}

template <class ForwardIterator,class T>
inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x,T1*)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	__uninitialized_fill_aux(first,last,is_POD());
}

template <class ForwardIterator,class T>
inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& x,__true_type)
{
	fill(first,last,x);
}


template <class ForwardIterator,class T>
inline void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& x,__false_type)
{
	ForwardIterator cur = first;
	for(; cur != last;++cur)
		construct(&*cur,x);
}
