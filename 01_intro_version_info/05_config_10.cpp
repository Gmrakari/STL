
/*
 * Date:2021-04-20 16:42
 * filename:05_config_10.cpp
 * test __STL_LIMITED_DEFAULT_TEMPLATES
 * ref C++ Primer 3/e,p.816
 *
 */

#include <iostream>
#include <cstddef>	//for size_t
using namespace std;

class alloc{

};

template <class T,class Alloc = alloc,size_t BufSiz = 0>
class deque
{
public:
	deque() { cout << "deque" << endl; }
};

//根据前一个参数值T，设定下一个参数Sequence的默认值deque<T>
template <class T,class Sequence = deque<T>>
class stack
{
public:
	stack() { cout << "stack" << endl; }
private:
	Sequence c;
};

int main()
{
	stack<int> x;
}

