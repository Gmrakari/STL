

/*
 * Date:2021-08-18 12:32
 * filename:04_algobase_iter_swap.cpp
 *
 */

/*
 * 将两个ForwardIterators所指的对象对调
 *
 * iter_swap()
 *
 */
template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
	__iter_swap(a, b, value_type(a));//第三个参数的型别value_type
}

template <class ForwardIterator1, class ForwardIterator2, class T>
inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
 * iter_swap()是"迭代器之value type"派上用场的一个例子
 * 该函数必须知道迭代器的value type，才能够据此声明一个对象，用来暂时存放迭代器所指对象。
 *
 * 此源码特别设计了一个双层构造，第一层调用第二层，并多出一个额外的参数value_type(a)
 * 这么一来，第二层就有value type可以用了。
 * 调用端是value_type(a),接受端是T*
 * value_type的定义如下:
 */

//by <stl_iterator.h>
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

//直接这么写更直接
template <class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
	typename iterator_traits<ForwardIterator1>::value_type tmp = *a;
	*a = *b;
	*b = tmp;
}
