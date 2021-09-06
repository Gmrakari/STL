

/*
 * Date:2021-09-06 21:14
 * filename:07_inplace_merge_应用于有序区间.cpp
 *
 */

/*
 * 如果两个连接在一起的序列[first, middle)和[middle, last)都已排序，那么inplace_merge可将它们结合成
 * 单一一个序列，并仍保有序性(sorted)。如果原先两个序列是递增排序，执行结果也会使递增排序，如果原先
 * 两个序列是递减排序，执行结果也会是递减排序。
 *
 * 和merge一样,inplace_merge也是一种稳定操作，每个作为数据来源的子序列中的元素相对次序都不会变动
 * 如果两个子序列有等同的元素，第一序列的元素会被排在第二序列元素之前
 *
 * Version 1 用operator < 比较，第二版本用仿函数(functor)comp比较
 *
 */

//Version 1
template <class BidirectionalIterator>
inline void inplace_merge(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last) {
	//只要有任何一个序列为空，就什么都不做
	if (first == middle || middle == last) return ;
	__inplace_merge_aux(first, middle, last, value_type(first), distance_type(first));
}

//辅助函数
template <class BidirectionalIterator, class T, class Distance>
inline void __inplace_merge_aux(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last, T*, Distance*) {
	Distance len1 = 0;
	distance(first, middle, len1);//len1表示序列一的长度
	Distance len2 = 0;
	distance(middle, last, len2);

	//注意，本算法会使用额外的内存空间(暂时缓冲区)
	temporary_buffer<BidirectionalIterator, T> buf(first, last);
	if (buf.begin() == 0)  //分配内存失败
		__merge_without_buffer(first, middle, last, len1, len2);
	else //在有暂时缓冲区的情况下进行
		__merge_adaptive(first, middle, last, len1, len2,buf.begin(), Distance(buf.size()));
}


//辅助函数,有缓冲区的情况下
template <class BidirectionalIterator, class Distance, class Pointer>
void __merge_adaptive(BidirectionalIterator first, BidirectionalIterator middle,
		BidirectionalIterator last, Distance len1, Distance len2, Pointer buffer, Distance buffer_size) {
	if (len1 <= len2 && len1 <= buffer_size) {
		//case1 缓冲区足够安置序列1
		Pointer end_buffer = copy(first, middle, buffer);
		merge(buffer, end_buffer, middle, last, first);
	}
	else if ( len2 <= buffer_size ) {
		//case2 缓冲区足够安置序列2
		Pointer end_buffer = copy(middle, last, buffer);
		__merge_backward(first, middle, buffer, end_buffer, last);
	}
	else {
		//case3 缓冲区空间不足安置任何一个序列
		BidirectionalIterator first_cut = first;
		BidirectionalIterator second_cut = middle;
		Distance len11 = 0;
		Distance len22 = 0;
		if (len1 > len2) {
			//序列1 比较长
			len11 = len1;
			advance(first_cut, len11);
			second_cut = lower_bound(middle, last, *first_cut);
			distance(middle, second_cut, len22);
		}
		else {
			//序列二比较长
			len22 = len2;
			advance(second_cut, len22);
			first_cut = upper_bound(first, middle, *second_cut);
			distance(first, first_cut, len11);
		}
		BidirectionalIterator new_middle = __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
				len22, buffer, buffer_size);

		//针对左段，递归调用
		__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);

		//针对右段，递归调用
		__merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size);
	}
}

/*
 * 总的来说就是
 * 先将len1 和 len2 区别开来
 * 然后对len1 或者 len2 其中的一份copy到缓冲区
 * 然后对缓冲区和未copy的区间进行merge
 * 这样就得到最后的结果了
 *
 *
 * 当缓冲区足够容纳[first, middle),就将[first, middle)复制到缓冲区，再以merge将缓冲区和第二序列[middle, last)合并
 * 当缓冲区足够容纳[middle, last),就将[middle, last)复制到缓冲区，再以_merge_backward将第二序列[first, middle)和缓冲区合并
 *
 */

/*
 * 但在case3处，当缓冲区不足以容纳任何一个序列时，以递归分割(recursive partitioning)的方式
 * 让处理长度减半，看看能不能容纳于缓冲区中(如果能，才能进行处理)
 *
 */

/*
 * 比如缓冲区大小为3,小于序列一的长度4和序列二的长度5
 * 于是，拿较长的序列二开到，计算出first_cut和second_cut
 *
 */

/*
 * 实现
 */
BidirectionalIterator first_cut = first;
BidirectionalIterator second_cut = middle;

Distance len11 = 0;
Distance len22 = 0;

len22 = len2 / 2;
advance(second_cut, len22);
first_cut = upper_bound(first, middle, *second_cut);
distance(first, fist_cut, len11);

//然后进行旋转操作
BidirectionalIterator new_middle = __rotate_adaptive(first_cut, middle, second_cut, len1 - len11,
		len22, buffer, buffer_size);

//__rotate_adaptive 实现
template <class BidirectionalIterator1, class BidirectionalIterator2, class Distance>
BidirectionalIterator1 __rotate_adaptive(BidirectionalIterator1 first, BidirectionalIterator middle,
		BidirectionalIterator1 last, Distance len1, Distance len2, BidirectionalIterator2 buffer, Distance buffer_size) {
	BidirectionalIterator2 buffer_end;
	if (len1 > len2 && len2 <= buffer_size) {
		//缓冲区足够安置序列二(较短)
		buffer_end = copy(middle, last, buffer);
		copy_backward(first, middle, last);
		return copy(buffer, buffer_end, first);
	}
	else if (len1 <= buffer_size) {
		//缓冲区足够安置序列1
		buffer_end = copy(first, middle, buffer);
		copy(middle, last, first);
		return copy_backward(buffer, buffer_end, last);
	}
	else {
		//缓冲区仍然不足，改用rotate算法
		rotate(first, middle, last);
		advance(first, len2);
		return first;
	}
}

