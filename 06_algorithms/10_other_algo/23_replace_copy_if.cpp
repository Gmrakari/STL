

/*
 * Date:2021-08-25 11:54
 * filename:23_replace_copy_if.cpp
 *
 */

/*
 * 行为与replace_if类似
 * 但是新序列会被复制到result所指的区间内
 * 返回值OutputIterator指向被复制的最后一个元素的下一位置。原序列无任何改变
 *
 */

template <class Iterator, class OutputIterator, class Predicate, class T>
OutputIterator replace_copy_if(Iterator first, Iterator last,
		OutputIterator result, Predicate pred, const T& new_value) {
	for (; first != last; ++first, ++result)
		//如果旧序列上的元素被pred评估为true,就放new_value到新序列中
		//否则就将元素拷贝一份放到新序列中
		*result = pred(*first) ? new_value : *first;
	return result;
}
