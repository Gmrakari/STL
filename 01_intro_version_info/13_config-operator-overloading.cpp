
/*
 * Date:2021-04-21 11:03
 * file:13_config-operator-overloading.cpp
 *
 * increment/decrement/dereference 操作符
 *
 * increment/dereference 操作符在迭代器的实现上占有非常重要的地位
 * 因为任何一个迭代器都必须实现出前进(increment,operator++)和取值(dereference,operator*)功能
 * 前者还分为前置式(prefix)和后置式子(postfix)两种，有非常规律的写法
 * 有些迭代器具备双向移动功能，那么就必须提供decrement操作符
 */

#include <iostream>
using namespace std;

class INT
{
	friend ostream& operator<<(ostream& os,const INT& i);

public:
	INT(int i) : m_i(i) {};

	//prefix : increment and then fetch
	INT& operator++()
	{
		++(this->m_i);
		return *this;
	}

	//postfix : fetch and then increment
	const INT operator++(int)
	{
		INT temp = *this;
		++(*this);
		return temp;
	}

	//prefix : decrement and then fetch
	INT& operator--()
	{
		--(this->m_i);
		return *this;
	}

	//postfix : fetch and then decrement
	const INT operator--(int)
	{
		INT temp = *this;
		--(*this);
		return temp;
	}

	//dereference
	int& operator*() const
	{
		return (int&)m_i;
	}
private:
	int m_i;

};

ostream& operator<<(ostream& os,const INT& i)
{
	os <<'[' << i.m_i << ']';
	return os;
}

int main()
{
	INT I(5);
	cout << I++ << " ";
	cout << ++I << " ";
	cout << I-- << " ";
	cout << --I << " ";

	cout << *I << " ";
	cout << endl;
}
