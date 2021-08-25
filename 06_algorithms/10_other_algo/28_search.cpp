

/*
 * Date:2021-08-25 16:22
 * filename:28_search.cpp
 *
 */

/*
 * 在序列一[frist1, last1)所涵盖的区间中，查找序列二[first2, last2)的首次出现点。
 * 如果序列一内不存在序列二完全匹配的子序列，便返回迭代器last1。
 * 版本一使用元素型别所提供的equality操作符，版本二允许用户指定某个二元运算(以仿函数呈现)，
 * 作为判断相等与否的依据。
 */
//查找子序列首次出现地点
//版本一

template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1,
		ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2) {
	return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
}

template <class ForwardIterator1, class ForwardIterator2, class Distance1, class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, Distance1*, Distance2*) {
	Distance1 d1 = 0;
	distance(first1, last1, d1);
	Distance2 d2 = 0;
	distance(first2, last2, d2);

	if (d1 < d2) return last1;//如果第二序列大于第一序列，不可能成为其子序列

	ForwardIterator1 current1 = first1;
	ForwardIterator2 current2 = first2;

	while (current2 != last2)					//遍历整个第二序列
		if (*current1 == *current2) {		//如果这个元素相同
			++current1;										//调整，以便比对下一个元素
			++current2;
		}
		else {													//如果这个元素不等
			if (d1 == d2)									//如果两序列一样长
				return last1;								//表示不可能成功了
			else {
				current1 = ++first1;				//两序列不一样长(至此肯定是序列1 > 序列2),调整第一序列的标兵，
				current2 = first2;					//准备在新起点上再找一次
				--d1;												//已经排除了序列一的一个元素，所以序列一的长度要减1
			}
		}
	return first1;
}
