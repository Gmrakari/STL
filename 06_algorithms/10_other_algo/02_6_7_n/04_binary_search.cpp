

/*
 * Date:2021-08-29 11:37
 * filename:04_binary_search.cpp
 *
 */

/*
 * binary_search是一种二分查找法,试图在已排序的[first, last)中寻找元素value.
 * 如果[first, last)内有等同于value的元素，便返回true,否则返回false
 *
 * 返回单纯的bool或许不能满足你，前面所介绍的lower_bound和upper_bound能够提供额外的信息。
 * 事实上binary_search便是利用lower_bound先找出”假设value存在的话，应该出现的位置",然后再对比该位置上的值
 * 是否为我们所要查找的目标，并返回对比结果。
 */

//Version 1
template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value) {
	ForwardIterator i = lower_bound(first, last, value);
	return i != last && !(value < *i);
}

//version 2
template <class ForwardIterator, class T, class Compare>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
	ForwardIterator i = lower_bound(first, last, value, comp);
	return i != last && !comp(value, *i);
}

