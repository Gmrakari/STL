

/*
 * Date:2021-08-17 17:20
 * filename:07_numeric_中的iota.cpp
 *
 */

/*
 * SGI专属。它用来设定某个区间的内容，使其内的每个元素从指定的value值开始，呈现递增状态
 * 它改变了区间的内容，是属于一种质变算法
 */
template <class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value) {
	while (first != last)
		*first++ = value++;
}
