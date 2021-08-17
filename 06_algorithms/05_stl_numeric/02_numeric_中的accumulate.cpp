

/*
 * Date:2021-08-17 15:35
 * filename:02_numeric_中的accumulate.cpp
 *
 */

//版本1
template <class InputIterator, class T>
T accumulate(InputIterator first, InputIterator last, T init) {
	for (; first != last; ++first) 
		init = init + *first;//将每个元素累加到初值init身上
	return init;
}

//版本2
template <class InputIterator, class T, class BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op) {
	for (; first != last; ++first)
		init = binary_op(init, *first);//对每一个元素执行二元操作
	return init;
}

/*
 * 式中的二元操作符不必满足交换律(commutative)和结合律(associative)
 * accumulate的行为顺序有明确的定义:先将init初始化,然后针对[first, last)
 * 区间中的每一个迭代器i,依序执行init = init + *i或者init = binary_op(init, *i)
 *
 */
