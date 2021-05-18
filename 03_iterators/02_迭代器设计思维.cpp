

/*
 * Date:2021-05-17 20:00
 * filename:02_迭代器设计思维.cpp
 *
 */

/*
STL的中心思想在于:将数据容器(containers)和算法(algorithms)分开,彼此独立设计
最后再以一粘胶合剂将它们撮合再一起

容器、算法、迭代器(iterator)的合作展示
*/

//SGI <stl_algo.h>
template <clas InputIterator,class T>
InputIterator find(InputIterator first,InputIterator last,const T& value)
{
	while(first != last && *first != value)
		++first;
	return first;
}
