

/*
 * Date:2021-08-19 14:00
 * filename:02_set_union.cpp
 *
 */

/*
 * 算法set_union可构造S1、S2之并集
 * 它能构造出集合S1 U S2,此集合内含S1或S2内的每一个元素
 * S1、S2及其并集都是以排序区间表示
 *
 * 由于S1和S2内的每个元素都不需要唯一，因此，如果某个值在S1出现n次，
 * 在S2出现m次，那么该值在输出区间中会出现max(m, n)次，其中n个来自S1，
 * 其余来自S2。在STL set容器内，m <= 1 i且 n <= 1
 *
 * set_union是一种稳定操作，意思是输入区间内的每个元素的相对顺序都不会改变
 *
 * set_union有两个版本，差别在于如何定义某个元素小于另一个元素
 * 第一版本使用operator<进行比较，第二版本采用仿函数comp进行比较
 *
 */

//并集，求存在于[first1, last1)或存在于[first2, last2)的所有元素
//set是一种sorted range
//version_1
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, OutputIterator result) {
	//当两个区间都尚未到达尾端时，执行以下操作
	while (first1 != last1 && first2 != last2) {
		//在两区间内分别移动迭代器。首先将元素值较小者(假设为A区)记录于目标区，
		//然后移动A区迭代器使之前进;同时间之另一个区迭代器不懂。然后进行新一次的比大小、记录小值
		//迭代器移动...直到两区中有一区到达尾端。如果元素相等，取S1者记录于目标区，并同时移动两个迭代器
		if (*first1 < *first2) {
			*result = *first1;
			++first1;
		}
		else if (*first2 < *first1) {
			*result = *first2;
			++first2;
		}
		else {
			//*first2 == *first1;
			*result = *first1;
			++first1;
			++first2;
		}
		++result;
	}
	//只要两区之中有一区到达尾端，就结束while循环
	//以下将尚未到达尾端的区间的所有剩余元素拷贝到目的端
	//此刻[first1, last1)和[first2, last2)之中至少有一个是空白区间
	return copy(first2, last2, copy(first1, last1, result));
} 
