

/*
 * Date:2021-05-18 20:35
 * filename:06_mylist-iter.h
 *
 */

#include "06_mylist.h"

template <class Item>		//Item可以是单向链表节点或双向链表节点
struct ListIter				//这个迭代器特定只为链表服务,因为其独特的operator++之故
{
	Item* ptr;				//保持与容器之间的一个联系(keep a reference to Container)
	
	ListIter(Item* p = 0):ptr(p) {  } 	//default ctor

	Item& operator*() const { return *ptr; }
	Item* operator->() const { return ptr; }

	//以下两个operator++遵循标准做法
	//1- pre-increment operator
	ListIter& operator++()
	{
		ptr = ptr->next();
		return *this;
	}

	//2- post-increment operator
	ListIter operator++(int)
	{
		ListIter tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const ListIter& i) const { return ptr == i.ptr; }

	bool operator!=(const ListIter& i) const { return ptr != i.ptr; }
};



