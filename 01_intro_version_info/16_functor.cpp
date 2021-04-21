
/*
 * Date:2021-04-21 13:10
 * file:16_functor.cpp
 *
 * 所谓仿函数(functor)就是使用起来像函数一样的东西
 *
 * 如果你针对某个class进行operator()重载，他就成为一个仿函数。
 */

#include <iostream>
using namespace std;

//由于将operator()重载了，因此plus成了一个仿函数
template <class T>
struct plus{
	T operator() (const T& x,const T& y) const { return x + y; }
};

template <class T>
struct minus{
	T operator() (const T& x,const T& y) const { return x - y; }
};

int main()
{
	//产生仿函数对象
	plus<int> plusobj;
	minus<int> minusobj;

	//使用仿函数，就像使用一般函数一样
	cout << plusobj(3,5) << endl;
	cout << minusobj(3,5) << endl;

	//直接产生仿函数的临时对象(第一对小括号),并调用之(第二队小括号)
	
	cout << plus<int>() (43,50) << endl;
	cout << minus<int>() (43,50) << endl;
}
