

/*
 * Date:2021-09-05 16:40
 * filename:05_RW_STL_sort.cpp
 *
 */

template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (!(first == last)) {
		__quick_sort_loop(first, last);
		__final_insertion_sort(first, last);//其内操作与SGI STL完全相同
	}
}

template <class RandomAccessIterator>
inline void __quick_sort_loop(RandomAccessIterator first, RandomAccessIterator last) {
	__quick_sort_loop_aux(first, last, _RWSTD_VALUE_TYPE(first));
}

template <class RandomAccessIterator, class T>
void __quick_sort_loop_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
	while (last - first > __stl_threshold) {
		//median-of-3 partitioning
		RandomAccessIterator cut = __unguarded_partition
			(first, last T(__median(*first, *(first + (last - first) / 2), *(last - 1))));

		if (cut - first >= last - cut) {
			__quick_sort_loop(cut, last);		//较短段以递归方式处理
			last = cut;
		}
		else {
			__quick_sort_loop(first, cut); //较短段以递归方式处理
			first = cut;
		}
	}
}
