

/*
 * Date:2021-09-09 11:23
 * filename:02_Insert_Iterators.cpp
 *
 */

/*
 * Insert Iterators 可以将一般迭代器的赋值(assign)操作转变为插入(insert)操作
 * 这样的迭代器包括专司尾端插入操作的back_insert_iterator,
 * 专司头端插入操作的front_insert_iterator,以及可从任意位置执行插入操作的insert_iterator
 * 由于这三个iterator adapters的使用接口不是十分直观，给一般用户带来困扰
 * STL就提供相应的函数:back_inserter()、front_inserter()、inserter()
 *
 * back_inserter(Container& x) -> back_insert_iterator<Container>(x);
 *
 * front_inserter(Container& x) -> front_insert_iterator<Container>(x);
 *
 * inserter(Container& x, Iterator i) -> insert_iterator<Container>(x, Container::iterator(i));
 *
 */

/*
 * 下面是insert iterators的完整实现列表
 * 其中的主要观念是，每一个insert iterators内部都维护一个容器（必须由用户指定）;
 * 容器当然有自己的迭代器，于是，当客户端对insert iterators做赋值(assign)操作时，
 * 就在insert iterators中转被转为对该容器的迭代器做插入(insert)操作，也就是说，在insert iterators
 * 的operator=操作符中调用底层容器的push_front()或push_back()或insert()操作函数
 *
 * operator++,operator++(int),operator*都被关闭功能，更没有提供operator--(int)或operator--或operator->
 * 以上类型被称为(output_iterator_tag)
 * 换句话说insert iterators的前进、后退、取值、成员取用等操作都是没有意义的，甚至是不允许的
 *
 */

//这是一个迭代器适配器(iterator adapter),用来将某个迭代器的赋值(assign)
//操作修改为插入(insert)操作——从容器的尾端插入进去(back_insert)
template <class Container>
class back_insert_iterator {
protected:
	Container* container;	//底层容器
public:
	typedef output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	//下面这个ctor使back_insert_iterator与容器绑定起来
	explicit back_insert_iterator(Container& x) : container(&x) {}
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_back(value);//关键 转调用push_back()
		return *this;
	}

	//以下操作符对back_insert_iterator不起作用(关闭功能)
	back_insert_iterator<Container>& operator*() {
		return *this;
	}
	back_insert_iterator<Container>& operator++() {
		return *this;
	}
	back_insert_iterator<Container>& operator++(int) {
		return *this;
	}
};

//这是一个辅助函数，帮助我们方便使用back_insert_iterator
template <class Container>
inline back_insert_iterator<Container> back_insert(Container& x) {
	return back_insert_iterator<Container>(x);
}


//---------------------------------------------------------------------
//这是一个迭代器适配器(iterator adapter),用来将某个迭代器的赋值(assign)
//操作修改为插入(insert)操作-从容器的头端插入进去(所以称为front_insert)
//该迭代器不适用于vector,因为vector没有提供push_front函数
template <class Container>
class front_insert_iterator {
protected:
	Container* container;													//底层容器
public:
	typedef output_iterator_tag iterator_category; //注意类型
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	explicit front_insert_iterator(Container& x) : container(&x) {}
	front_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_front(value);	//转调用push_front()
		return *this;
	}

	//关闭功能
	front_insert_iterator<Container>& operator*() {
		return *this;
	}
	front_insert_iterator<Container>& operator++() {
		return *this;
	}
	front_insert_iterator<Container>& operator++(int) {
		return *this;
	}
};

//这是一个辅助函数，帮我们方便使用front_insert_iterator
template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
	return front_insert_iterator<Container>(x);
}

//---------------------------------------------------------------------
//这是一个迭代器适配器(iterator adapter),用来将某个迭代器的赋值(assign)
//操作修改为插入(insert)操作，在指定的位置上进行，并将迭代器右移一个位置
//--如此便可方便地连续执行 "表面是赋值(覆写)而实际上是插入"的操作
template <class Container>
class insert_iterator {
protected:
	Container* container;
	typename Container::iterator iter;
public:
	typedef output_iterator_tag iterator_category;
	typedef void value_type;
	typedef void difference_type;
	typedef void pointer;
	typedef void reference;

	insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(i) {}
	insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		iter = container->insert(iter, value);//转调用insert()
		++iter;					// 使insert iterator永远随着目标贴身移动
		return *this;
	}
	//以下操作符对back_insert_iterator不起作用(关闭功能)
	 insert_iterator<Container>& operator*() {
		return *this;
	}
	 insert_iterator<Container>& operator++() {
		return *this;
	}
	 insert_iterator<Container>& operator++(int) {
		return *this;
	}
};

//这是一个辅助函数，帮我们方便使用front_insert_iterator
template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i) {
	return insert_iterator<Container>(x, iter(i));
}
