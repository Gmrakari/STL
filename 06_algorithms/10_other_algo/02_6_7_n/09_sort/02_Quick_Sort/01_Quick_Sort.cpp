

/*
 * Date:2021-09-03 11:08
 * filename:01_Quick_Sort.cpp
 *
 */

/*
 * Quick Sort 平均复杂度为O(N log N),最坏情况下将达O(N^2)
 * 不过IntroSort(极类似median-of-three QuickSort的一种排序算法)可将最坏情况推进到O(N log N)
 */

/*
 * Quick Sort描述:
 * 假设S代表将被处理的序列
 * 1、如果S的元素各位为0或者1,结束
 * 2、取S中任何一个元素，当作枢轴(pivot)v
 * 3、将S分割为L,R两段，使L内的每一个元素都小于或等于v,R内的每一个元素都大于或等于v
 * 4、对L,R递归执行Quick Sort
 *
 * Quick Sort的精神在于将大区间分割为小区间，分段排序
 *
 * Median-of-Three(三点中值)
 * 任何一个元素都可以被选来当作枢轴(pivot),但是其合适与否却会影响Quick Sort的效率
 * 最理想最稳定的方式就是取整个序列的头、尾、中央三个位置的元素，以其中值(median)作为枢轴
 *
 */

//SGI STL三点中值决定函数
template <class T>
inline const T& __median(const T& a, const T& b, const T& c) {
	if (a < b) 
		if (b < c ) //a < b < c
			return b;
		else if (a < c) // a < b, b >= c, a < c
			return c;
		else
			return a;
	else if (a < c)
		return a;
	else if (b < c)
		return c;
	else
		return b;
}

//SGI STL Partitionining(分割)
//其返回值是为分割后的右段第一个位置
//Version 1

template <class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, T pivot) {
	while (true) {
		while (*first < pivot) ++first;//first 找到 >= pivot的元素就停下来
		--last;		//调整
		while (pivot < *last) --last;	//last找到 <= pivot的元素就停下来

		//注意，以下first < last 判断操作，只适用于random iterator
		if (!(first < last)) return first;	//交错 结束循环
		iter_swap(first, last);	//大小值交换
		++first;		//调整
	}
}
