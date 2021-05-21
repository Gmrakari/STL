

/*
 * Date:2021-05-21 14:33
 * filename:04_pointer_type.cpp
 *
 */

/*
 * pointers和references在C++中有非常密切的关联
 * 如果"传回一个左值，令它代表p所指之物"是可能的，那么"传回一个左值，令它代表p所指之物的地址"也是可以的
 * 也就是说，我们能够传回一个pointer,指向迭代器所指之物
 */

Item& operator*() const { return *ptr; }
Item* operator->() const { return ptr; }

/*
 * Item& 便是ListIter的reference type,而Item* 便是其pointer type
 * 将reference type 和 pointer type 这两个相应型别加入traits内
 */

template <class T>
struct iterator_traits {
	...
	typedef typename I::pointer 	pointer;
	typedef typename I::reference reference;
};

/*
 * partial specialization
 */

template <class T>
struct iterator_traits<T*> {
	...
	typedef T* pointer;
	typedef T& reference;
};

template <class T>
struct iterator_traits<const T*> {
	...
	typedef const T* pointer;
	typedef const T& reference;
};


