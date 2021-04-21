
/*
 * 组态5:__STL_CLASS_PARTIAL_SPECIALIZATIION
 * filename:config_5.cpp
 * 测试class template partial specialization
 * 在class template的一般化设计之外，特别针对某些template参数做特殊设计
 * test __STL_CLASS_PARTIAL_SPECIALIZATION in <stl_config.h>
 */

#include <iostream>
using namespace std;

template <class I,class O>
struct testClass
{
	testClass() { cout << "I,O" << endl;}
};

template <class T>
struct testClass<T*,T*>
{
	testClass() { cout << "T*,T*" << endl;}
};

template <class T>
struct testClass<const T*,T*>
{
	testClass() { cout << "const T*,T*" << endl;}
};

int main()
{
	testClass<int,char> obj1;
	testClass<int *,int *> obj2;
	testClass<const int*,int *> obj3;
}

