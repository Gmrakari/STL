

/*
 * Date:2021-08-21 17:47
 * filename:17_remove_copy.cpp
 *
 */


/*
 *移除[first, last)之中所有与value相等的元素.
 这一算法并不真正从容器中删除那些元素
 * (换句话说容器大小并未改变)，而是将结果复制到一个以result标示起始位置的容器身上。
 * 新容器可以和原容器重叠，但如果对新容器实际给值时，超越了旧容器的大小，会产生无法预期的结果。
 * 返回值Outputterator指出被父值的最后元素的位置
 */
template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value) {
	for ( ; first != last; ++first )
		if (*first != value) {
			*result = *first;
			++result;
		}
	return result;
}
