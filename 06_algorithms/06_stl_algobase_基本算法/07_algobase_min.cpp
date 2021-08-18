

/*
 * Date:2021-08-18 14:06
 * filename:07_algobase_min.cpp
 *
 */

/*
 * 取两个对象中的较大值。
 * 有两个版本，版本一使用对象型别T所提供的greater-than操作符来判断大小，版本二使用仿函数comp来判断大小
 */
template <class T>
inline const T& min(const T& a, const T& b) {
	return b < a ? b : a;
}

template <class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp) {
	return comp(b, a) ? b : a;//由comp决定"大小比较"标准
}


