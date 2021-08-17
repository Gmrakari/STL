

/*
 * Date:2021-08-17 17:01
 * filename:05_numeric_中的partial_sum.cpp
 *
 */

//版本1
template <class InputIterator, class OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last,
		OutputIterator result) {
	if (first == last) return result;
	*result = *first;
	return __partial_sum(first, last, result, value_type(first));
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*) {
	T value = *first;
	while (++first != last) {
		value = value + *first;
		*++result = value;
	}
	return ++result;
}

//版本2
template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
	if (first == last) return result;
	*result = *first;
	return __partial_sum(first, last, result, value_type(first), binary_op);
}

template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __partial_sum(InputIterator first, InputIterator last, OutputIterator result, T*, BinaryOperation binary_op) {
	T value = *first;
	while (++first != last) {
		value = binary_op(value, *first);		//前n个元素的总计
		*++result = value;									//指定给目的端
	}
	return ++result;
}

/*
 * 算法partial_sum用来计算局部总和
 * 它会将*first 赋值给*result。对于[first + 1, last)中每个迭代器i,从头至尾依序执行sum = sum + *i
 * 或sum = binary_op(sum, *i)(第二个版本),然后再将sum赋值给*(result + (i - first))
 *
 * 本算法返回输出区间的最尾端位置:result + (last - first)
 *
 * partial_sum与adjacent_difference互为逆运算
 * 如果对区间值1, 2, 3, 4, 5执行partial_sum，获得结果为1, 3, 6, 10, 15
 * 再对结果执行adjacent_difference, 便会获得原始区间值1, 2, 3, 4, 5
 *
 */
