

/*
 * Date:2021-08-17 15:41
 * filename:02_numeric_中的adjacent_difference.cpp
 *
 */

//版本1
template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result) {
	if (first == last) return result;
	*result = *first;//首先记录第一个元素
	return __adjacent_difference(first, last, result, value_type(first));

	/*
	jjhou() {
		if (first == last) return result;
		*result = *first;
		iterator_traits<InputIterator>::value_type value = *first;
		while (++first != last) {
			//以下同__adjacnet_difference()的对应内容
		}
	}
	*/
}

template <class InputIterator, class OutputIterator, class T>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, T*) {
	T value = *first;
	while (++first != last) {	//走过整个区间
		T tmp = *first;
		*++result = tmp - value;	//将相邻两元素的差额(后- 前),赋值给目的端
		value = tmp;
	}
	return ++result;
}

//版本2
template <class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op) {
	if (first == last) return result;
	*result = *first;//记录第一个元素
	return __adjacent_difference(first, last, result, value_type(first), binary_op);
}

template <class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator __adjacent_difference(InputIterator first, InputIterator last,
		OutputIterator result, T*, BinaryOperation binary_op) {
	T value = *first;
	while (++first != last) { //走过整个区间
		T tmp = *first;
		*++result = binary_op(tmp, value);		//将相邻两元素的运算结果，赋值给目的端
		value = tmp;
	}
	return ++result;
}

/*
 * adjacent_difference用来计算[first, last)中相邻元素的差额。
 * 它将*first赋值给*result,并针对[first + 1, last)内的每个迭代器i,
 * 将*i - *(i - 1)之值赋值给*(result + (i - first))
 */

/*
 * "储存第一元素之值，然后储存后继元素之差值"这种做法很有用，因为这么一来
 * 便有足够的信息可以重建输入区间的原始内容。
 * 如果加法与减法的定义一如常规定义，那么adjacent_difference与partial_sum互为逆运算
 * 如果对区间值1,2,3,4,5执行adjacent_difference,获得结果为1,1,1,1,1
 * 再对此结果执行partial_sum,便会获得原始区间值1,2,3,4,5
 */
