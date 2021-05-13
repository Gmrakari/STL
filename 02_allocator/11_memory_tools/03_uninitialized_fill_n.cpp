

/*
 * Date:2021-05-13 21:04
 * filename:03_uninitialized_fill_n.cpp
 *
 */

template <class ForwardIterator,class Size,class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first,Size n,const T& x);

/*
 * uninitialized_fill_n()能够使我们将内存配置与对象构造行为分离开来,
 * 它会为指定范围内的所有元素设定相同的初值
 *
 * 如果[first,first + n]范围内的每一个迭代器都指向未初始化的内存,
 * 那么uninitialzed_fill_n()会调用copy constructor,在该范围内产生x的复制品
 * 也就是说,面对[first,first + n]范围内的每个迭代器i,uninitialized_fill_n()
 * 会调用construct(&*i,x)，在对应位置处产生x的复制品
 *
 */

//实现

template <class ForwardIterator,class Size,class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first,Size n,const T& x)
{
	return __uninitialized_fill_n(first,n,x,value_type(first));
}

/*
 * 这个函数的进行的逻辑是,首先萃取出迭代器first的value type,然后判断该型别是否为POD型别:
 */

template <class ForwardIterator,class Size,class T,class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T&x, T1*)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first,n,x,is_POD());
}

/*
 * POD(Plain Old Data),也就是标量型别(scalar types)或传统的C struct()型别
 * POD型别必然拥有trivial ctor/dtor/copy/assignment函数
 * 因此，我们可以对POD型别采用最有效率的初值填写手法,而对non-POD型别采取最保险安全的做法:
 */

//如果copy construction 等同于 assignment,而且 destructor是trivial,以下就有效
//如果是POD型别,执行流程就会转进到以下函数
//这是藉由function template 的参数推导机制而得
template <class ForwardIterator,class Size,class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,__true_type)
{
	return fill_n(first,n,x);
}

template <class ForwardIterator,class Size,class T>
ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,__false_type)
{
	ForwardIterator cur = first;
	for(; n > 0;--n,++cur)
	{
		construct(&*cur,x);
	}
	return cur;
}
