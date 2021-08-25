

/*
 * Date:2021-08-25 11:48
 * filename:21_replace_copy.cpp
 *
 */

/*
 * 行为与replace()类似，唯一不同的新序列会被复制到result所指容器中
 * 返回值OutputIterator指向被复制的最后一个元素的下一位置。原序列没有任何改变
 *
 */

template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last,
		OutputIterator result, const T& old_value, const T& new_value) {
	for (; first != last; ++first, ++result)
		//如果旧序列上的元素等于old_value,就放new_value到新序列中
		//否则就将元素拷贝一份放到新序列中
		*result = *first == old_value ? new_value : *first;
	return result;
}
