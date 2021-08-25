

/*
 * Date:2021-08-25 11:34
 * filename:19_remove_copy_if.cpp
 *
 */

/*
 * 移除[first, last)区间内所有被仿函数pred评估为true的元素。
 * 它并不真正从容器中删除那些元素(换句话说原容器没有任何改变),而是将结果复制到一个以result
 * 标示起始位置的容器身上。新容器可以和原容器重叠，但如果针对新容器实际给值时，超越了旧容器的大小，
 * 会产生无法预期的结果。返回值OutputIterator指出被复制的最后元素的下一位置
 *
 */

template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred) {
	for (; first != last; ++first)
		if (!pred(*first)) {	//如果pred核定为false
			*result = *first;		//就赋值给新容器(保留，不删除)
			++result;						//新容器前进一个位置
		}
	return result;
}
