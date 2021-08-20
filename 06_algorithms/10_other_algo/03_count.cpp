

/*
 * Date:2021-08-20 15:16
 * filename:03_count.cpp
 *
 */

/*
 * 运用equality操作符,将[first, last)区间内的每一个元素拿来和指定值value比较
 * 并返回与value相等的元素个数
 *
 */

template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
	//以下声明一个计数器n
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first != last; ++first) 
		if (*first == value)
			++n;
	return n;
}

/*
 * 早期版本
 * 计数器由参数提供
 */
template <class InputIterator, class T, class Size>
void count(InputIterator first, InputIterator last, const T& value, Size& n) {
	for (; first != last; ++first)
		if (*first == value)
			++n;
}


