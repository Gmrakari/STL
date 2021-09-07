

/*
 * Date:2021-09-07 11:07
 * filename:merge_sort.cpp
 *
 */

/*
 * Merge Sort:
 * 将两个有序(sorted)区间归并成一个有序区间，效果不错，那么我们可以利用"分而治之"(devide and conquer)的概念，
 * 以各个击破的方式来对一个区间进行排序。首先，将区间对半分割，左右两段各自排序，再利用inplace_merge重新组合
 * 为一个完整的有序序列。对半分割的操作可以递归进行，直到每一小段的长度为0或1
 *
 */

template <class BidirectionalIter>
void mergesort(BidirectionalIter first, BidirectionalIter last) {
	typename iterator_traits<BidirectionalIter>::difference_type n = distance(first, last);
	if (n == 0 || n == 1) 
		return ;
	else {
		BidirectionalIter mid = first + n / 2;
		megesort(first, mid);
		mergesort(mid, last);
		inplace_merge(first, mid, last);
	}
}

//复杂度为O(N logN) 虽然和Quick Sort是一样的
//因为Merge Sort需借用额外的内存，而且在内存之间移动(复制)数据也会耗费不少时间，
//所以Merge Sort的效率比不上Quick Sort
//
//优点是 实现简单、概念简单
