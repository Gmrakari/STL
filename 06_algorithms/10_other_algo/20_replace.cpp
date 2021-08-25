

/*
 * Date:2021-08-25 11:46
 * filename:20_replace.cpp
 *
 */

/*
 * 将[first, last)区间内的所有old_value都以new_value取代
 */

template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value) {
	for (; first != last; ++first)
		if (*first == old_value)
			*first = new_value;
}
