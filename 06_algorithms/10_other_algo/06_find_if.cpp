

/*
 * Date:2021-08-20 16:19
 * filename:06_find_if.cpp
 *
 */

/*
 * 根据指定的pred运算条件(以仿函数表示)，循序查找[first, last)内的所有元素，
 * 找出第一个令pred运算结果为true者。如果找到就返回一个Inputterator指向该元素
 * 否则返回迭代器last
 *
 */

template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
	while (first != last && !pred(*first)) ++first;
	return first;
}
