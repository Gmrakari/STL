
/*
 * data:2021-04-20 20:50
 * file:config_null-template-arguments.cpp
 * test __STL_NULL_TMPL_ARGS in <stl_config.h>
 * ref. C++ Primer 3/e,p.834 bound friend function template
 *
 */

#include <iostream>
#include <cstddef>
using namespace std;

class alloc{

};

template <class T,class Alloc = alloc,size_t BufSiz = 0>
class deque
{
public:
	deuqe() { cout << "deque" << ' '; }

};

//前置声明


template <class T,class Sequence>
class stack;

template <class T,class Sequence>
bool operator==(const stack<T,Sequence>& x,const stack<T,Sequence>& y);

template <class T,class Sequence>
bool operator<(const stack<T,Sequence>& x,const stack<T,Sequence>& y);



template <class T,class Sequence = deque<T> >
class stack
{
	//ok
	friend bool operator== <T>(const stack<T>&,const stack<T>&);
	friend bool operator< <T>(const stack<T>&,const stack<T>&);

	//ok
	friend bool operator== <T>(const stack&,const stack&);
	friend bool operator< <T>(const stack&,const stack&);

	//ok
	friend bool operator== <> (const stack&,const stack&);
	friend bool operator< <> (const stack&,const stack&);

	//un ok
	
	/*
	friend bool operator== (const stack&,const stack&);
	friend bool operator< (const stack&,const stack&);
	*/

public:
	stack() { cout <<"stack" << endl; }
private:
	Sequence c;
};

template <class T,class Sequence>
bool operator==(const stack<T,Sequence>& x,const stack<T,Sequence>& y)
{
	return cout <<"operator==" << '\t';
}

template <class T,class Sequence>
bool operator<(const stack<T,Sequence>& x,const stack<T,Sequence>& y)
{
	return cout <<"operator<" << '\t';
}

int main()
{
	stack<int> x;
	stack<int> y;

	cout <<(x == y) << endl;
	cout << (x < y) << endl;

	stack<char> y1;

}
