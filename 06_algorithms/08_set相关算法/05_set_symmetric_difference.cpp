

/*
 * Date:2021-08-19 16:05
 * filename:05_set_symmetric_difference.cpp
 *
 */

/*
 * set_symmetric_difference可构造S1,S2之对称差积
 * 它能构造出集合(S1 - S2) U (S2 - S1)
 * 此集合内含"出现与S1但不出现于S2"，以及"出现于S2但不出现于S1"的每一个元素
 *
 * 由于S1和S2内的每个元素都不需要唯一，因此如果某个值在S1出现n次，在S2出现m次，
 * 那么该值在输出区间中会出现|n - m|次。
 * 如果n > m,输出区间内的最后n - m个元素将由S1复制而来，
 * 如果n < m,则输出区间内的最后m - n个元素将由S2复制而来
 * 在STL set容器内，m <= 1 且 n <= 1
 *
 */

/*
 *
 * 第一版本使用operator<进行比较，第二版本采用仿函数comp进行比较
 *
 */

//对称差集，求存在于[first1, last1) 且不存在于[first2, last2)的所有元素，
//以及存在于[first2, last2)且不存在于[first1, last1)的所有元素
//上述定义只有在"元素值独一无二"的情况下才成立。
//如果set一般化，允许出现重复元素，那么set_symmetric_difference的定义应该是:
//如果某值在[first1, last1)出现n次，在[first2, last2)出现m次，
//那么它在result range中应该出现abs(n - m)次
//set是一种sorted range
//version_1
template <class Inputerator1, class Inputerator2, class OutputIterator>
OutputIterator set_symmetric_difference(Inputerator1 first1, Inputerator1 last1,
		Inputerator2 first2, Inputerator2 last2, OutputIterator result) {
	while (first1 != last1 && first2 != last2) {
		//在两区间内分别移动迭代器，当两区间内的元素相等，就让两区同时前进
		//当两区内的元素不等，就记录较小值于目标区，并令较小值所在区间前进
		if (*first1 < *first2) {
			*result = *first1;
			++first1;
			++result;
		}
		else if (*first2 < *first1) {
			*result = *first2;
			++first2;
			++result;
		}
		else {
			++first1;
			++first2;
		}
	}
	return copy(first2, last2, copy(first1, last1, result));
}
