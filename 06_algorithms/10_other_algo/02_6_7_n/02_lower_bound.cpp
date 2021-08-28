

/*
 * Date:2021-08-28 14:59
 * filename:02_lower_bound.cpp
 *
 */

/*
 * 这是二分查找(binary search)的一种版本，试图在已排序的[first, last)中寻找元素value
 * 如果[first, last)具有与value相等的元素(s),便返回一个迭代器，指向其中第一个元素。
 * 如果没有这样的元素存在，便返回"假设这样的元素存在时应该出现的位置"。
 * 也就是说，它会返回一个迭代器，指向第一个"不小于value"的元素。
 * 如果value大于[first, last)内的任何一个元素，则返回last。以稍许不同的观点来看lower_bound,其返回值是
 * "在不破坏排序状态的原则下，可插入value的第一个位置"
 *
 */

/*
 * 这个算法有两个版本，版本一采用operator<进行比较，版本二采用仿函数comp。
 * 版本一返回[first, last)中最远的迭代器i,使得[first, i)中的每个迭代器j都满足*j < value
 * 版本二返回[first, last)中最远的迭代器i,使[first, i)中的每个迭代器j都满足"comp(*j, value)为真"
 *
 */

//Version 1:
template <class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value) {
	return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
}

//Version 2:
template <class ForwardIterator, class T, class Compare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
	return __lower_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

//version 1 forward_iterator
template <class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);
	Distance half;
	ForwardIterator middle;

	while (len > 0) {
		half = len >> 1;
		middle = first;
		advance(middle, half);
		if (*middle < value) {
			first = middle;
			++first;
			len = len - half - 1;
		}
		else 
			len = half;
	}
	return first;
}

//Version 1 的 random_access_iterator 版本
template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*,
		random_access_iterator_tag) {
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle;

	while (len > 0) {
		half = len >> 1;					//除以2
		middle = first + half;		//令middle指向中间位置(r - a - i才能如此)
		if (*middle < value) {		//如果中间位置的元素值 < 目标值
			first = middle + 1;			//令first指向middle的下一位置
			len = len - half - 1;		//修正len,回头测试循环的结束条件
		}
		else
			len = half;							//修正len,回头测试循环的结束条件
	}
	return first;
}
