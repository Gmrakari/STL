

/*
 * Date:2021-08-21 15:58
 * filename:09_for_each.cpp
 *
 */

/*
 * 将仿函数f施行于[first, last)区间内的每一个元素身上。
 * f不可以改变元素内容，因为first和last都是InputIterator,不保证接受赋值行为(assignment)
 * 如果想要一一修改元素的内容，应该使用算法transform().f可返回一个值，但该值会被忽略
 */
template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
	for (; first != last; ++first)
		f(*first);
	return f;
}
