

/*
 * Date:2021-08-20 15:25
 * filename:05_find.cpp
 *
 */

/*
 * 根据equality操作符，循序查找[first, last)内的所有元素，找出第一个匹配
 * "等同(equality)条件"者，如果找到，就返回一个Inputterator指向该元素，
 * 否则返回迭代器last
 *
 */
template <class Inputerator, class T>
Inputerator find(Inputerator first, Inputerator last, const T& value) {
	while (first != last && *first != value) ++first;
	return first;
}


