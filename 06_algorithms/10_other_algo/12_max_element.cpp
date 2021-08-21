

/*
 * Date:2021-08-21 16:28
 * filename:12_max_element.cpp
 *
 */

/*
 * 返回一个迭代器，指向序列之中数值最大的元素
 */

//Version 1:
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (*result < *first) *result = *first;
	return result;
}

//Version 2
template <class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp) {
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last) 
		if (comp(*result, *first)) result = first;
	return result;
}
