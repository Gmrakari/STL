

/*
 * Date:2021-08-20 15:08
 * filename:02_adjacent_find.cpp
 *
 */

/*
 * 找出第一组满足条件的相邻元素。
 * 在版本一中指"两元素相等"
 * 在版本二中允许用户指定一个二元运算，两个操作数分别是相邻的第一元素和第二元素
 */

//version_1
template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
	if (first == last) return last;
	ForwardIterator next = first;
	while (++next != last) {
		if (*first == *next) return first;
		first = next;
	}
	return last;
}

//version_2
template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred) {
	if (first == last) return last;
	ForwardIterator next = first;
	while (++next != last) {
		//如果找到相邻的元素符合外界指定条件，就结束
		//以下，两个操作数分别是相邻的第一元素和第二元素
		if (binary_pred(*first, *next)) return first;
		first = next;
	}
	return last;
}


