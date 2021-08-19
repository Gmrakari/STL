

/*
 * Date:2021-08-19 15:36
 * filename:04_set_difference.cpp
 *
 */

/*
 * set_difference可构造S1,S2之差集
 * 它能构造出集合S1 - S2，此集合内含"出现于S1但不出现于S2"的每一个元素
 * S1、S2及其交集都是以排序区间表示。返回值为一个迭代器，指向输出区间的尾端
 *
 * 由于S1和S2内的每个元素都不需要唯一，因此如果某个值在S1出现n次，在S2出现m次，
 * 那么该值在输出区间会出现max(n - m, 0)次，并且全部来自S1
 * 在STL set容器内, m <= 1 且 n <= 1
 *
 *
 * set_difference有两个版本，差别在于如何定义某个元素小于另一个元素
 * 第一版本使用operator<进行比较，第二版本采用仿函数comp进行比较
 *
 */

//差集，求存在于[first1, last1)且不存在于[first2, last2)的所有元素
//set是一种sorted range
//version_1

template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
	//当两个区间都尚未到达尾端时，执行以下操作...
	while (first1 != last1 && first2 != last2) {
		//在两区内分别移动迭代器。
		//当第一区间的元素等于第二区间的元素(表示此值同时存在于两区间),
		//就让两区间同时前进;
		//当第一区间的元素大于第二区间的元素，就让第二区间的元素前进;
		//有了这两种处理，就保证当第一区间的元素小于第二区间的元素时，
		//第一区间的元素只存在于第一区间中，不存在第二区间，于是将它记录于目标区
		if (*first1 < *first2) {
			*result = *first1;
			++first1;
			++result;
		}
		else if (*first2 < *first1)
			++first2;
		else {
			//*first2 == *first1
			++first1;
			++first2;
		}
	}
	return copy(first1, last1, result);
}
