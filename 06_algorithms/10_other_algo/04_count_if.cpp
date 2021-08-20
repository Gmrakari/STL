

/*
 * Date:2021-08-20 15:20
 * filename:04_count_if.cpp
 *
 */

/*
 * 将指定操作(一个仿函数)pred实施于[first, last)区间内的每一个元素身上，
 * 并将"造成pred之计算结果为true"的所有元素的个数返回
 */
template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
	//声明一个计数器n
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first != last; ++first)
		if (pred(*first))
			++n;
	return n;
}

/*
 * 早期版本 计数器由参数提供
 *
 */
template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
void count_if(InputIterator first, InputIterator last, Predicate pred, Size& n) {
	for (; first != last; ++first) {
		if (pred(*first))
			++n;
	}
}
