

/*
 * Date:2021-08-29 10:59
 * filename:03_upper_bound.cpp
 *
 */

/*
 * 算法upper_bound是二分查找法的一个版本
 * 它试图在已排序的[first, last)中寻找value。
 * 它会返回"在不破坏顺序的情况下，可插入value的最后一个合适位置"
 *
 * STL规范"区间圈定"时的起头和结尾并不对称([first, last)包含first, 不包含last)，所以
 * upper_bound和lower_bound的返回值意义大有不同。如果你查找某值，而它的确出现在区间之内，则lower_bound
 * 返回的是一个指向该元素的迭代器。然而upper_bound不这么做。
 * 因为upper_bound所返回的是在不破坏排序状态的情况下，value可被插入的"最后一个"合适位置。如果value存在，
 * 那么它返回的迭代器将指向value的下一位置，而非指向value本身
 *
 */

//Version 1:
template <class ForwardIterator, class T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value) {
	return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
}

//Version 2:
template <class ForwardIterator, class T, class Compare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp) {
	return __upper_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

//版本一的forward_iterator版
template <class ForwardIterator, class T, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);//求取整个区间的长度len
	Distance half;
	ForwardIterator middle;

	while (len > 0) {
		half = len >> 1;		//除以2
		middle = first;			//这两行令middle指向中间位置
		if (value < *middle)
			len = half;
		else {
			first = middle;					//这两行令first指向middle的下一位置
			++first;
			len = len - half - 1;		//修正len,回头测试循环的结束条件
		}
	}
	return first;
}


//版本一的random_access_iterator版
template <class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*,
		random_access_iterator_tag) {
	Distance len = last - first;		//求取整个区间的长度len
	Distance half;

	RandomAccessIterator middle;
	while (len > 0) {
		half = len >> 1;	
		middle = first  + half;
		if (value < *middle) 
			len = half;
		else {
			first = middle + 1;
			len = len - half - 1;
		}
	}
	return first;
}
