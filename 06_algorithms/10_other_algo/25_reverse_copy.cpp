

/*
 * Date:2021-08-25 15:45
 * filename:25_reverse_copy.cpp
 *
 */

/*
 * 行为类似于reverse(),但产生出来的新序列会被置于以result指出的容器中。
 * 返回值OutputIterator指向新产生的最后元素的下一位置。原序列没有任何改变。
 *
 */
template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result) {
	while (first != last) {				//整个序列走一遍
		--last;											//尾端前移一个位置				
		*result = *last;						//将尾端所指元素复制到result所指位置
		++result;										//result前进一个位置
	}
	return result;
}
