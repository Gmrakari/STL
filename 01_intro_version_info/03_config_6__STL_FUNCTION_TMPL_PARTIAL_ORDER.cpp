
/*
 * 组态6:__STL_FUNCTION_TMPL_PARTIAL_ORDER
 *
 * filename:03_config_6.cpp
 * test __STL_FUNCTION_TMPL_PARTIAL_ORDER in <stl_config.h>
 */

#include <iostream>
using namespace std;
class alloc{};

template <class T,class Alloc = alloc>
class vector
{
public:
	void swap(vector<T,Alloc>&) { cout << "swap()" << endl;}
};

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T,class Alloc>
inline void swap(vector<T,Alloc>& x,vector<T,Alloc>& y)
{
	x.swap(y);
}
#endif

int main()
{
	vector<int> x,y;
	swap(x,y);
}

