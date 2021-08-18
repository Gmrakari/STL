

/*
 * Date:2021-08-18 11:24
 * filename:02_algobase_equal.cpp
 *
 */

/*
 * 如果两个序列在[first, last) 区间内想等，equal()返回true
 * 如果第二序列的元素比较多，多出来的元素不予考虑。
 * 因此，如果我们希望保证两个序列完全相等，必须先判断其元素个数是否相同
 */
if (vec1.size() == vec2.size() && equal(vec1.begin(), vec1.end(), vec2.begin()))

	/*
	 * 抑或使用容器所提供的euality操作符，例如vec1 == vec2
	 * 如果第二序列的元素比第一序列的少，这个算法内部进行迭代行为时，会超越序列的尾端，造成不可预测的结果
	 * 第一版本缺省采用元素型别所提供的equality操作符来进行大小比较，第二版本允许我们指定仿函数pred作为比较依据
	 */

template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator1 last, InputIterator2 first2) {
	//以下，将序列走过一遍。序列二也一步步走
	//如果序列一的元素个数多过序列而的元素个数，就糟糕了
	for (; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2)
			return false;
	return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred) {
	for (; first1 != last1; ++first1, ++first2) 
		if (!binary_pred(*first1, *first2))
			return false;
	return true;
}
