

/*
 * Date:2021-08-21 17:37
 * filename:16_remove.cpp
 *
 */

/*
 * remove 移除(但不删除)
 *
 * 移除[first, last)之中所有与value相等的元素，这一算法并不真正从容器中删除那些元素
 * (换句话说容器大小并未改变)，而是将每一个不与value相等(也就是我们并不打算移除)的元素
 * 轮番赋值给first之后的空间。
 * 返回值ForwardIterator标示出重新整理后的最后元素的下一位置。例如序列{0,1,0,2,0,3,0,4}
 * 如果我们执行remove(),希望移除所有0值元素，执行结果将是{1,2,3,4,0,3,0,4}
 * 每一个与0不想等的元素，1,2,3,4分别被拷贝到第一、二、三、四个位置上。
 * 第四个位置以后不动，换句话说是第四个位置之后是这一算法留下的残余数据。
 * 返回值ForwardIterator指向第五个位置。如果要删除那些残余数据，可将返回的迭代器交给区间所在之容器
 * erase() member function.
 * 注意array不适合使用remove和remove_if,因为array无法缩小尺寸，导致残余数据永远存在。
 * 对array而言，用的是remove_copy和remove_copy_if
 */
template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value) {
	first = find(first, last, value);//利用循序查找法找出第一个相等元素
	ForwardIterator next = first;		//以next标示出来

	//利用"remove_copy()允许新旧容器重叠"的性质，进行移除操作
	//并将结果指定置于原容器中

	return first == last ? first : remove_copy(++next, last, first, value);
}
