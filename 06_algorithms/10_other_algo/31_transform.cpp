

/*
 * Date:2021-08-28 09:28
 * filename:31_transform.cpp
 *
 */

/*
 * tranform()的第一版本以仿函数op作用于[first, last)中的每一个元素身上，并以其结果产生出一个新序列。
 * 第二版本以仿函数binary_op作用于一双元素身上(其中一个元素来自[first1, last),另一个元素来自"从first2开始的序列"),
 * 并以其结果产生出一个新序列。如果第二序列的元素少于第一序列，执行结果未可预期。
 *
 */

/*
 * transform()的两个版本都把执行结果放进迭代器result所标示的容器中。result也可以指向源端容器，那么transform()的运算
 * 结果就会取代该容器内的元素。返回值OutputIterator指向结果序列的最后元素的下一位置
 */

//Version 1:
template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOperation op) {
	for (; first != last; ++first, ++result) 
		*result = op(*first);
	return result;
}

//Version 2:
template <class InputIterator1, class InputIterator2, class OutputIterator, class BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, OutputIterator result,
		BinaryOperation binary_op) {
	for (; first1 != last1; ++first1, ++first2, ++result) 
		*result = binary_op(*first1, *first2);
	return result;
}
