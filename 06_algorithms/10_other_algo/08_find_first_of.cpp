

/*
 * Date:2021-08-20 17:49
 * filename:08_find_first_of.cpp
 *
 */

/*
 * 以[frist2, last2)区间内的某些元素作为查找目标，寻找它们在[first1, last1)区间内的第一次出现地点
 * 假设我们希望找出字符序列synesthesia的第一个元音，我们可以定义第二序列为aeiou
 * 此算法会返回一个ForwardIterator,指向元音序列中任一元素首次出现于第一序列的地点，此例将指向字符序列的第一个e
 * 如果第一序列并未内含第二序列的任何元素，返回的将是last1.
 * 本算法第一个版本使用元素型别所提供的equality操作符，第二个版本允许用户指定一个二元运算pred
 *
 */

//版本1
template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2) {
	for (; first1 != last1; ++first1)
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (*first1 == *iter)
				return first1;
	return last1;
}

//version 2
template <class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1,
		ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp) {
	for (; first1 != last1; ++first1)
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (comp(*first1, *iter))
				return first1;
	return last1;
} 


