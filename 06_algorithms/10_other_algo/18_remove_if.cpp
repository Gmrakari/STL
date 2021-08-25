

/*
 * Date:2021-08-25 11:28
 * filename:18_remove_if.cpp
 *
 */

/*
 * 移除[first, last)区间捏的所有被仿函数pred核定为true的元素。它并不真正从容器中删除那些元素
 * 每一个不符合pred条件的元素都会被轮番赋值给first之后的空间。返回值ForwardIterator标示出重新整理后的最后
 * 元素的下一位置。此算法会留有一些残余数据，如果要删除那些残余数据，可将返回的迭代器交给区间所在之容器的
 * erase() member function
 *
 */

template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred) {
	first = find_if(first, last, pred);	//利用循序查找法找出第一个匹配者
	ForwardIterator next = first;				//以next标记出来

	//"利用remove_copy_if()允许新旧容器重叠"的性质，做删除操作
	//并将结果放到原容器中
	return first == last ? first : remove_copy_if(++next, last, first, pred);
}
