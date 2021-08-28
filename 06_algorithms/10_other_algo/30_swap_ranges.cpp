

/*
 * Date:2021-08-28 09:21
 * filename:30_swap_ranges.cpp
 *
 */

/*
 * 将[frist1, last1)区间内的元素与"从first2开始、个数相同"的元素互相交换。
 * 这两个序列可位于同一容器中，也可位于不同的容器中。如果第二序列的长度小于第一序列，
 * 或是两序列在同一容器中且彼此重叠，执行结果未可预期。此算法返回一个迭代器，指向
 * 第二个序列中的最后一个被交换元素的下一位置。
 */

//将两段等长区间内的元素互换
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2) {
	for (; first1 != last1; ++first1, ++first2)
		iter_swap(first1, first2);
	return first2;
}
