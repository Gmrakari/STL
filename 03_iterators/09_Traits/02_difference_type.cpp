

/*
 * Date:2021-05-20 20:20
 * filename:02_difference_type.cpp
 *
 */

/*
 * difference type 是用来表示两个迭代器之间的距离,因此也可以用来表示一个容器的最大容量，
 * 因为对于连续空间的容器而言,头尾之间的距离就是其最大容量，如果一个泛型算法提供计数功能，
 * 例如STL的count()，其传回值就必须使用迭代器的difference type:
 */
template <class I,class T>
typename iterator_traits<I>::difference_type
count(I first, I last, const T& value) {
	typename iterator_traits<I>::difference_type n = 0;
	for (; first != last; ++first)
	  if (*first == value)
		++n;
	return n;
}

/*
 * 针对相应型别difference type,traits的如下两个(针对原生指针而写的)特化版本,
 * 以c++内建的ptrdiff_t作为原生指针的differce type:
 */
template <class I>
struct iterator_traits {
	...
	typedef typename I::difference_type difference_type;
};

//针对原生指针而设计的"偏特化(partial specialization)"版
template <class T>
struct iterator_traits<T*> {
	...
	typedef ptrdiff_t difference_type;
};

template <class T>
struct iterator_traits<const T*> {
	...
	typedef ptrdiff_t difference_type;
};

/*
 * 现在，任何时候当我们需要任何迭代器I的difference type,可以这么写
 */
typename iterator_traits<I>::difference_type ****;
