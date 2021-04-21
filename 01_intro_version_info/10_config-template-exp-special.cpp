
/*
 * Date:2021-04-21 10:47
 * file:10_config-template-exp-special.cpp
 * test:class template explicit specialization
 * ref C++ Primer 3/e p.858
 */

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define __STL_TEMPLATE_NULL template<>

template <class Key>
struct hash
{
	void operator() (){cout << "hash<T>" << endl; }
};

//explicit specialization
__STL_TEMPLATE_NULL struct hash<char>{
	void operator() () { cout << "hash<char>" << endl; }
};

__STL_TEMPLATE_NULL struct hash<unsigned char>{
	ovid operator() () { cout << "hash<unsigned char>" << endl; }
};

int main()
{
	hash<long> t1;
	hash<char> t2;
	hash<unsigned char> t3;

}

