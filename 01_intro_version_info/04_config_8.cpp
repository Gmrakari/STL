
/*
 * Date:2021-04-20 16:38
 * 组态8:__STL_MEMBER_TEMPLATES
 * 
 * filename:04_config_8.cpp
 * test __STL_MEMBER_TEMPLATES in <stl_config.h>
 * ref . C++ Primer 3/e,p.844
 *
 */
#include <iostream>
using namespace std;

class alloc
{

};

template <class T,class Alloc = alloc>
class vector
{
public:
	typedef T value_type;
	typedef value_type* iterator;

	template <class I>
	void insert(iterator position,I first, I last)
	{
		cout << "insert()" << endl;
	}
};

int main()
{
	int ia[5] = {0,1,2,3,4};

	vector<int> x;
	vector<int>::iterator ite;
	x.insert(ite,ia,ia + 5);
}
