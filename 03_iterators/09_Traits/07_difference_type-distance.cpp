

/*
 * Date:2021-05-21 15:41
 * filename:07_difference_type-distance.cpp
 *
 */

/*
 * distance()常用的一个迭代器操作函数，用来计算两个迭代器之间的距离
 * 针对不同的迭代器类型，它可以有不同的计算方式，带来不同的效率。
 */

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last) {
		++first;++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline iterator_traits<RandomAccessIterator>::difference_type 
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
	return last - first;
}

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	typedef typename iterator_traits<InputIterator>::iterator_category category;
	return __distance(first,last,category());
}


