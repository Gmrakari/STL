

/*
 * Date:2021-08-25 11:51
 * filename:22_replace_if.cpp
 *
 */

/*
 * 将[frist, last)区间内所有"被pred评估为true"的元素，都以new_value取而代之
 *
 */

template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value) {
	for (; first != last; ++first)
		if (pred(*first))
			*first = new_value;
}
