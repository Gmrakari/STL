

/*
 * Date:2021-08-21 16:06
 * filename:11_includes.cpp
 *
 */

/*
 * includes(应用于有序区间)
 * 判断序列二S2是否"涵盖于"序列一S1。
 * S1和S2都必须是有序集合，其中的元素都可重复(不必唯一)
 * 所谓涵盖，意思是"S2的每一个元素都出现于S1"
 * 由于判断两个元素是否相等，必须以less或greater运算为依据
 * (当S1元素不小于S2元素且S2元素不小于S1元素，两者即相等;
 * 或说当S1元素不大于S2元素且S2元素不大于S1元素，两者即相等),
 * 因此配合着两个序列S1和S2的排序方式(递增或递减)，用less or greater
 */

/*
 * 如果S1和S2是递增排序(以operator<执行比较操作),includes使用方法:
 */
includes(S1.begin(), S1.end(), S2.begin(), S2.end());
//相同
includes(S1.begin(), S1.end(), S2.begin(), S2.end(), less<int>());

//如果S1和S2是递减排序(以operator>执行比较操作):

includes(S1.begin(), S1.end(), S2.begin(), S2.end(), greater<int>());

//Version_1 判断区间二的每个元素是否都存在于区间一
//前提:区间一和区间二都是sorted ranges
template <class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2) {
	while (first1 != last1 && first2 != last2) //两个区间尚未走完
		if (*first2 < *first1)	//序列二的元素小于序列一的元素
			return false;
		else if (*first1 < *first2)	//序列而的元素大于序列一的元素
			++first1;									//序列一前进1
		else												//*first1 == *first2
			++first1, ++first2;				//两序列各自前进1
	return first2 == last2;				//有一个序列走完了，判断最后一关
}

//Version_2
//判断序列一内是否有个子序列，其与序列而的每个对应元素都满足二元运算comp
//前提:序列一和序列二都是sorted ranges

template <class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp) {
	while (first1 != last1 && first2 != last2) //两个区间都尚未走完
		if (comp(*first2, *first1))
			return false;
		else if (comp(*first1, *first2))
			++first1;
		else
			++first1, ++first2;
	return first2 == last2;
}
