

/*
 * Date:2021-09-07 10:49
 * filename:08_nth_element.cpp
 *
 */

/*
 * 这个算法会重新排列[first, last)，使迭代器nth所指的元素，与"整个[first, last)完整排序后，
 * 同一位置的元素"同值。此外并保证[nth, last)内没有任何一个元素小于(更精确地说是不大于)[first, nth)内的元素，
 * 但对于[first, nth)和[nth, last)两个子区间内的元素次序则无任何保证--这一点也是它与partial_sort很大的不同处
 * nth_element比较近似partition而非sort或partial_sort
 *
 */

/*
 * e.g. {22, 30, 30, 17, 33, 40, 17, 23, 22, 12, 20} 经以下操作
 * nth_element(iv.begin(), iv.begin() + 5, iv.end());		
 *
 * 将小于*(iv.begin() + 5) [= 40]的元素置于该元素之左，其余置于该元素之右
 * 并且不保证维持原有的相对位置。获得的结果是{20, 12, 22, 17, 17, 22, 23, 30 ,30, 33, 40}
 * 与整个序列完整排序后{12, 17, 17, 20, 22, 22, 23, 30, 30, 33, 40}的元素值相同
 *
 * {20, 12, 22, 17, 17, 22, 23, 30, 30, 33, 40}为根据，再执行以下操作
 * nth_element(iv.begin(), iv.begin() + 5, iv.end(), greater<int>());
 *
 * 将大于*(iv.begin() + 5){本例为22}的元素置于该元素之左，其余置于该元素之右
 * 结果为{40, 33, 30, 30, 23, 22, 17, 17, 22, 20}
 *
 * nth_element不保证两个子序列的任何次序，比partial_sort较快
 *
 */

/*
 * nth_element不断地以median-of-3 partitioning(以首、尾、中央三点中值为枢轴之分割法)将整个序列分割为更小的左右序列
 * 如果nth迭代器落于左子序列，就再对左子序列进行分割，否则就再对右子序列进行分割
 * 一次类推，直到分割后的子序列长度不大于3(够小了)，便对最后这个待分割的子序列做Insertion Sort
 *
 */

//Version 1
template <class RandomAccessIterator>
inline void nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last) {
	__nth_element(first, nth, last, value_type(first));
}

//Version 1 辅助函数
template <class RandomAccessIterator, class T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, T*) {
	while (last - first > 3) {
		//median-of-3 partitioning Args:(first, last, pivot)
		//返回一个迭代器，指向分割后的右段第一个元素
		RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first,
						*(first + (last - first) / 2),
						*(last - 1))));
		if (cut <= nth)							//如果右段起点 <= 指定位置(nth落于右段)
			first = cut;							//再对右段实施分割(partitioning)
		else												//否则(nth落于左段)
			last = cut;								//对坐段实施分割(partitioning)
	}
	__insertion_sort(first, last);
}
