

/*
 * Date:2021-09-06 20:39
 * filename:06_equal_range_应用于有序区间.cpp
 *
 */

/*
 * 算法equal_range_是二分查找法的一个版本
 * 试图在已排序的[first, last)中寻找value
 * 它返回一对迭代器i和j，其中i是在不破坏次序的前提下，value可插入的第一个位置(亦即lower_bound)
 * j则在不破坏次序的前提下，value可插入的最后一个位置(亦即upper_bound)
 * 因此，[i, j)内的每个元素都等同于value,而且[i, j)是[first, last)之中符合此一性质的最大子区间
 *
 */


/*
 * equal_range是[first, last)内"与value等同"之所有元素所形成的区间A。
 * 由于[first, last)有序,所以我们知道"与value等同"之元素一起都相邻
 * 于是，算法lower_bound返回区间A的第一个迭代器，算法upper_bound返回区间A的最后元素的下一位置，
 * 算法equal_range则是以pair的形式将两者都返回
 *
 */

/*
 * 即使[first, last)并未含有"与value等同"之任何元素，以上叙述仍然合理。
 * 这种情况下，"与value等同"之所有元素所形成的，其实是个空区间。
 *
 * 在不破坏次序的前提下，只有一个位置可以插入value,而equal_range所返回的pair，其第一和第二元素
 * (都是迭代器)皆指向该位置
 *
 */

//Version 1
template <class ForwardIterator, class T>
inline pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
	//根据迭代器的种类型(category)，采用不同的策略
	return __equal_range(first, last, value, distance_type(first), iterator_category(first));
}


//Version 1 的random_access_iterator 版本
template <class RandomAccessIterator, class T, class Distance>
pair<RandomAccessIterator, RandomAccessIterator>
__equal_range(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag) {
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle, left, right;

	while (len > 0) {			//整个区间尚未遍历完毕
		half = len >> 1;		//找出中央位置
		middle = first + half;		//设定中央迭代器
		if (*middle < value) { //如果中央位置 < 指定值
			first = middle + 1;		//将运作区间缩小(移至后半段)，以提高效率
			len = len - half - 1;
		}
		else if (value < *middle)		//如果中央元素 > 指定值
			len = half;							//将运作区间缩小(移至前半段) 以提高效率
		else {				//如果中央元素 == 指定值
			//在前半段找lower_bound
			left = lower_bound(first, middle, value);
			//在后半段找upper_bound
			right = upper_bound(++middle, first + len, value);
			return pair<RandomAccessIterator, RandomAccessIterator>(left, right);
		}
	}

	//整个区间内都没有匹配的值，那么应该返回一对迭代器,指向第一个大于value的元素
	return pair<RandomAccessIterator, RandomAccessIterator>(first, first);
}

//Version 1 的 forward_iterator版本
template <class ForwardIterator, class T, class Distance>
pair<ForwardIterator, ForwardIterator>
__equal_range(ForwardIterator first, ForwardIterator last, const T& value,
		Distance*, forward_iterator_tag) {
	Distance len = 0;
	distance(first, last, len);

	Distance half;
	ForwardIterator middle, left, right;

	while (len > 0) {
		half = len >> 1;
		middle = first;	 //此行及下一行，相当于RandomAccessIterator的
		advance(middle, half); // middle = first + half; // first == 0;
		if (*middle < value) {
			first = middle;
			++first;
			len = len - half - 1;
		}
		else if (value < *middle) 
			len = half;
		else {
			left = lower_bound(first, middle, value);
			//以下这行相当于RandomAccessIterator的first += len;
			advance(first, len);
			right = upper_bound(++middle, first, value);
			return pair<ForwardIterator, ForwardIterator>(left, right);
		}
	}
	return pair<ForwardIterator, ForwardIterator>(first, first);
}



