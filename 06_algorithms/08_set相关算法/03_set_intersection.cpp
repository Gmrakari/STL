

/*
 * Date:2021-08-19 15:23
 * filename:03_set_intersection.cpp
 *
 */

/*
 * set_intersection可构造S1、S2之交集，
 * S1 ∩ S2,此集合内含同时出现于S1和S2内的每个元素
 * S1、S2及其交集都是以排列区间表示。
 * 返回值为一个迭代器，指向输出区间的尾端
 *
 * 由于S1和S2内的每个元素都不需唯一，因此，如果某个值在S1出现n次，在S2出现m次，那么该值在输出区间
 * 会出现min(m, n)次，并且全部来自S1。在STL set容器内，m <= 1 且 n <= 1
 *
 *
 * set_intersection有两个版本，差别在于如何定义某个元素小于另一个元素
 * 第一版本使用operator<进行比较，第二版本采用仿函数comp进行比较
 *
 *
 */

//交集，求存在于[first1, last1)且存在于[first2, last2)的所有元素
//set是一种sorted range
//version_1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
	//当两个区间都尚未到达尾端时，执行以下操作
	while (first1 != last1 && first2 != last2) {
		//在两区间内分别移动迭代器，直到遇有元素值相同，暂停，将该值记录于目标区
		//再继续移动迭代器...直到两区之中有一区到达尾端
		if (*first1 < *first2) {
			first1++;
		}
		else if (*first2 < *first1)
			++first2;
		else {
			*result = *first1;
			++first1;
			++first2;
			++result;
		}
	}
	return result;
}
