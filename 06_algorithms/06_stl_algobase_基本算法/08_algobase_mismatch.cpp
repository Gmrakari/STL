

/*
 * Date:2021-08-18 14:12
 * filename:08_algobase_mismatch.cpp
 *
 */

/*
 * 用来平行比较两个序列，指出两者之间的第一个不匹配点。
 * 返回一对迭代器分别指向两序列中的不匹配点
 * 如果两序列的所有对应元素都匹配，返回的便是两序列各自的last迭代器。
 * 却省情况下是以equality操作符来比较元素;
 * 但第二版本允许用户指定比较操作。
 * 如果第二序列的元素个数比第一序列多，多出来的元素忽略不计
 * 如果第二序列的元素个数比第一序列少，会发生未可预期的行为
 *
 */

template <class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2) {
	//以下 如果序列一走完，就结束
	//如果序列一和序列二的对应元素想等，就结束
	//显然 序列一的元素个数必须多过序列二的元素个数，否则结果无可预期
	while (first1 != last1 && *first1 == *first2) {
		++first1;
		++first2;
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1,
		InputIterator1 last1,InputIterator1 first2, BinaryPredicate binary_pred) {
	while (first1 != last1 && binary_pred(*first1, *first2)) {
		++first1;
		++first2;
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}


