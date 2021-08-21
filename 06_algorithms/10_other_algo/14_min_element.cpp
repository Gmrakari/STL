

/*
 * Date:2021-08-21 17:11
 * filename:14_min_element.cpp
 *
 */

/*
 * 返回一个迭代器，指向序列之中数值数值最小的元素
 */

template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (*first < *result) *result = *first;
	return result;
}

//Version 2

template <class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (comp(*first, *result)) result = first;
	return result;
}
