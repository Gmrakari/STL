

/*
 * Date:2021-08-25 16:19
 * filename:27_rotate_copy.cpp
 *
 */

/*
 * 行为类似rotate(),但产生出来的新序列会被置于result所指出的容器中
 * 返回值OutputIterator指向新产生的最后元素的下一位置。原序列没有任何改变。
 *
 * 由于它不需要就地(in-place)在原容器中调整内容，实现上也就简单得多。
 * 旋转操作其实只是两段元素彼此交换，所以只要先把后段复制到新容器的前端，再把前段接续复制到新容器，即可
 */

template <class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle,
		ForwardIterator last, OutputIterator result) {
	return copy(first, middle, copy(middle, last, result));
}
