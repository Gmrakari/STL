

/*
 * Date:2021-08-25 15:15
 * filename:24_reverse.cpp
 *
 */

/*
 * 将序列[first, last)的元素在原容器中颠倒重排。
 * 例如序列[0,1,1,3,5],颠倒重排为[5,3,1,1,0]
 * 迭代器的双向或随机定位能力，影响了这个算法的效率，所以设计为双层架构
 */

//分派函数(dispatch function)
template <class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last) {
	__reverse(first, last, iterator_category(first));
}

//reverse的bidirectional iterator版
template <class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag) {
	while (true)
		if (first == last || first == --last)
			return ;
	else
		iter_swap(first++, last);
}

//reverse的random access iterator版
template <class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
	//以下，头尾两两互换，然后头部累进一个位置，尾部累退一个位置。两者交错时即停止
	//注意，只有random iterators才能做以下的first < last 判断
	while (first < last) iter_swap(first++, --last);
}
