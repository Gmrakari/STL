

/*
 * Date:2021-07-21 16:01
 * filename:03_slist_iterator.cpp
 *
 */


//单向链表的迭代器基本结构
struct __slist_iterator_base {
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef forward_iterator_tag iterator_category;

	__slist_node_base* node;
	__slist_iterator_base(__slist_node_base* x) : node(x) {}

	void incr() { node = node->next; }

	bool operator==(const __slist_iterator_base& x) const {
		return node == x.node;
	}
	
	bool operator!=(const __slist_iterator_base& x) const {
		return node != x.node;
	}
};


//单向链表的迭代器结构
template<class T, class Ref, class Ptr>
struct __slist_iterator : public __slist_iterator_base {
	typedef __slist_iterator<T, T&, T*> iterator;
	typedef __slist_iterator<T, const T&, const T*> const_iterator;
	typedef __slist_iterator<T, Ref, Ptr> self;

	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __slist_node<T> list_node;

	__slist_iterator(list_node* x) : __slist_iterator_base(x) {}

	//调用slist<T>::end() 时会造成__slist_iterator(0),于是调用上述函数
	__slist_iterator() : __slist_iterator_base(0) {}
	__slist_iterator(const iterator& x) : __slist_iterator_base(x.node) {}

	reference operator*() const {return ((list_node *)node)->data;}
	pointer operator->() const {return &(operator*());}

	self& operator++() {
		incr();//前进一个节点
		return *this;
	}

	self operator++(int) {
		self tmp = *this;
		incr();
		return tmp;
	}

	//没有实现operator--,因为这是一个forward iterator
};

//注意
//比较两个slist迭代器是否等同时(比较某个迭代器是否等同于slist.end()),由于__slist_iterator并未对operator==实施重载
//所以会调用__slist_iterator_base::operator==。
//根据其中之定义，我们知道，两个slist迭代器是否等同，视其__slist_node_base* node是否等同而定
