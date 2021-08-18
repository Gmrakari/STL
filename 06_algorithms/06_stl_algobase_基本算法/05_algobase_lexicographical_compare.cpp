

/*
 * Date:2021-08-18 12:54
 * filename:05_algobase_lexicographical_compare.cpp
 *
 */

/*
 * 以"字典排序方式"对两个序列[first1, last1)和[first2, last2)进行比较
 * 比较操作针对两序列中的对应位置上的元素进行，并持续直到(1)某一组对应元素彼此不相等;
 * (2)同时到达last1和last2(当两序列的大小相同);
 * (3)到达last1或last2(当两序列的大小不同)
 *
 * 当这个函数在对应位置上发现第一组不想等的元素时，有下列几种可能:
 * 如果第一序列的元素较小，返回true,否则返回false
 * 如果到达last1而尚未到达last2,返回true
 * 如果到达last2而尚未到达last1,返回false
 * 如果同时到达last1和last2(换句话说所有元素都匹配),返回false;
 *
 * 总得来说是:第一序列以字典排序方式(lexicographically)而言不小于第二序列
 *
 *
	string stra1[] = { "Jamie", "JJHou", "Jason" };
	string stra2[] = { "Jamie", "HHhou", "Jerry" };

	第一组元素对，其相等
	第二组元素对，其不等
	'H' < 'h' ('H'的ASCII码 < 'h'的ASCII码)
	不再对比第三组元素。比较结果是true

	*/

/*
 * 第二版本允许你指定一个仿函数comp作为比较操作之用，取代元素型别所提供的less-than(小于)操作符
 */
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2) {
	//以下，任何一个序列到达尾端，就结束。否则两序列就相应元素一一进行比对
	for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
		if (*first1 < *first2)	//第一序列元素值小于第二序列的相应元素值
			return true;
		if (*first2 < *first1 ) //第二序列元素值小于第一序列的相应元素值
			return false;
		//如果不符合以上两条件，表示两值相等，那就进行下一组相应元素值的比对
	}
	//进行到这里，如果第一序列到达尾端而第二序列尚有余额，那么第一序列小于第二序列
	return first1 == last && first2 != last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp) {
	for (; first1 != last1 && frist2 != last2; ++first1, ++first2) {
		if (comp(*first1, *first2)) 
			return true;
		if (comp(*first2, *first1))
			return false;
	}
	return first1 == last && first2 != last2;
} 

/*
 * 为了增加效率，SGI还设计了一个特化版本，用于原生指针const unsigned char*;
 */
inline bool
lexicographical_compare(const unsigned char* first1,
		const unsigned char* last1,
		const unsigned char* first2,
		const unsigned char* last2) {
	const size_t len1 = last1 - first1;//第一序列长度
	const size_t len2 = last2 - first2;

	//先比较相同长度一段,memcmp() 速度极快
	const int result = memcmp(first1, first2, min(len1, len2));
	//如果不相上下，则长度较长者视为比较大
	return result != 0 ? result < 0 : len1 < len2;
}

/*
 * memcmp()是C标准函数，正是以unsigned char的方式来比较两序列中一一对应的每一个butes.
 */
