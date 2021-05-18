

/*
 * Date:2021-05-18 20:28
 * filename:06_mylist.h
 *
 */

#include <iostream>

template <typename T>
class List
{
	void insert_front(T value);
	void insert_end(T value);
	void display(std::ostream &os = std::cout) const;

private:
	ListItem<T>* _end;
	ListItem<T>* _front;
	long _size;
};
template <typename T>
class ListItem
{
public:
	T value() const { return _value; }
	ListItem* next() const { return _next; }

private:
	T _value;
	ListItem* _next;
};

//我们要设计一个iterator
//当我们提领(dereference)这以迭代器时,传回的应该是个ListItem对象;当我们递增该迭代器时,它应该指向下一个ListItem对象.
//为了让该迭代器适用于任何型态的节点,而不只限于ListItem,我们可以将它设计为一个class template:06.cpp
