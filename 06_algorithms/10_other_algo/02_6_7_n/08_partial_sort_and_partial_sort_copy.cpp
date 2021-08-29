

/*
 * Date:2021-08-29 16:59
 * filename:08_partial_sort_and_partial_sort_copy.cpp
 *
 */

/*
 * 本算法接受一个middle迭代器(位于序列[first, last)之内)，然后重新安排[first, last),使序列中的middle-first
 * 个最小元素以递增顺序排列，置于[first, middle)内。其余last-middle个元素安置于[middle, last)中，不保证有任何
 * 特定顺序
 *
 * 使用sort算法，同样能够保证较小的N个元素以递增顺序置于[first, first + N)之内。选择partial_sort而非sort的唯一理由
 * 是效率。
 *
 * 如果只是挑出前N个最小元素来排序，当然比对整个序列排序快上许多
 *
 * partial_sort有两个版本，其差别在于如何定义某个元素小于另一元素。第一版本使用less-than操作符，第二版本使用仿函数comp
 *
 */

/*
 * 实现:
 * partial_sort的任务是找出middle-first个最小元素，因此，首先界定出区间[first, middle)，并利用make_heap()将它
 * 组织成一个max-heap,然后就可以将[middle,last)中的每一个元素拿来于max-heap的最大值比较(max-heap的最大值就是在
 * 地一个元素身上)
 *
 * 如果小于该最大值，就互换位置并重新保持max-heap的状态。如此依赖，当我们走遍整个[middle, last)时，较大的元素都已经被
 * 抽离出[first, middle),这时再以sort_heap()将[first, middle)做一次排序，即功德圆满
 *
 */

//Version 1:
template <class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
	__partial_sort(first, middle, last, value_type(first));
}

template <class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*) {
	make_heap(first, middle);

	//以下i < last判断操作，只适用于random iterator
	for (RandomAccessIterator i = middle; i < last; ++i) 
		if (*i < *first)
			__pop_heap(first, middle, i, T(*i), distance_type(first));
	sort_heap(first, middle);
}

//partial_sort有一个姐妹，就是partial_sort_copy;
//Version 1
template <class InputIterator, class RandomAccessIterator>
inline RandomAccessIterator partial_sort_copy(InputIterator first, InputIterator last,
		RandomAccessIterator result_first, RandomAccessIterator result_last);

//version 2
template <class InputIterator, class RandomAccessIterator, class Compare>
inline RandomAccessIterator partial_sort_copy(InputIterator first, InputIterator last, RandomAccessIterator result_first,
		RandomAccessIterator result_last, Compare comp);

//将(last-first)个最小元素(或最大元素,视comp)排序后的所得结果置于[result_first, result_last)
