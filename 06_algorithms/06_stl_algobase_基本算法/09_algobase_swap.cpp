

/*
 * Date:2021-08-18 14:19
 * filename:09_algobase_swap.cpp
 *
 */

/*
 * 交换(对调)两个对象的内容
 */
template <class T>
inline void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}
