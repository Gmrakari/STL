

/*
 * Date:2021-08-18 11:33
 * filename:02_algobase_fill.cpp
 *
 */

/*
 * 将[first, last)内的所有元素改填新值
 */
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
	for (; first != last; ++first)
		*first = value;
}

/*
 * 将[first, last)内的前n个元素改填新值，返回迭代其指向被填入的最后一个元素的下一位置
 *
 */

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
	for (; n > 0; --n, ++first) 
		*first = value;
	return first;
}

/*
 * 如果n超越了容器的现有大小?
 */
int ia[3] = {0, 1, 2};
vector<int> iv(ia, ia + 3);
fill_n(iv.begin(), 5, 7);

/*
 * 由于每次迭代进行的是assignment操作，是一种覆写(overwrite)操作，所以一旦操作区间超越了容器大小
 * 就会造成不可预期的结果。
 * 解决：
 * 利用inserter()产生一个具有插入(insert)而非覆写(overwrite)能力的迭代器
 * inserter()可产生一个用来修饰迭代器的配接器(iterator apapter)
 */

int ia[3] = {0, 1, 2};
vector<int> iv(ia, ia + 3);//0 1 2
fill_n(inserter(iv.begin()), 5, 7); //7 7 7 7 7 0 1 2
