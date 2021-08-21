

/*
 * Date:2021-08-21 16:32
 * filename:13_merge.cpp
 *
 */

/*
 * 将两个经过排序的集合S1和S2，合并起来置于另一段空间。所得结果也是一个有序(sorted)序列
 * 返回一个迭代器，指向最后结果序列的最后一个元素的下一位置
 */

//version 1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
	while (first1 != last1 && first2 != last2) {
		if (*first2 < *first1) {
			*result = *first2;
			++first2;
		} 
		else {
			*result = *first1;
			++first1;
		}
		++result;
	}
	//最后剩余元素以copy复制到目的端
	return copy(first2, last2, copy(first1, last1, result));
}

//Version 2
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp) {
	while (first1 != last1 && first2 != last2) {
		if (comp(*first2, *first1)) {
			*result = *first2;
			++first2;
		}
		else {
			*result = *first1;
			++first1;
		}
		++result;
	}
	return copy(first2, last2, copy(first1, last1, result));
}
