

/*
 * Date:2021-08-21 16:02
 * filename:10_generate.cpp
 *
 */

/*
 * 将仿函数gen的运算结果填写在[first, last)区间内的所有元素身上。
 * 所谓填写，用的是迭代器所指元素之assignment操作符
 */
template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen) {
	for (; first != last; ++first) //整个序列区间
		*first = gen();
}


//generate_n

/*
 * 将仿函数gen的运算结果填写在从迭代器first开始的n个元素身上。
 * 所谓填写，用的是迭代器所指元素的assignment操作符
 */
template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen) {
	for (; n > 0; --n, ++first) 
		*first = gen();
	return first;
}
