

/*
 * Date:2021-05-21 16:20
 * filename:10_std-iterator.cpp
 *
 */

/*
 * STL提供了一个iterators class如下 如果每个新设计的迭代器都继承自它，就可保证符合STL所需之规范
 */

template <class Category,
				  class T,
					class Distance = ptrdiff_t,
					class Pointer = T*,
					class Reference = T&>
struct iterator {
	typedef Category	 iterator_category;
	typedef T					 value_type;
	typedef Distance	 difference_type;
	typedef Pointer		 pointer;
	typedef Reference	 reference;
};

/*
 * iterator class 不含任何成员，纯粹只是型别定义，所以继承它并不会招致任何额外负担
 * 由于后三个参数皆有默认值，故新的迭代器只需提供前两个参数即可
 */
template <class Item>
struct ListIter :
	public std::iterator<std::forward_iterator_tag, Item>
{ ...  };


/*
 * 总结:
 * 设计适当的相应型别(associated types)，是迭代器的责任。
 * 容器本身，才知道该设计出怎样的迭代器来遍历自己，并执行迭代器该有的各种行为(前进、后退、取值、取用成员...)
 * 至于算法，完全可以独立于容器和迭代器之外自行发展，只要设计时迭代器为对外接口就行
 *
 * traits编程技法大量运用于实现品中
 * 它利用"内嵌型别"的编程技巧，与编译器的template参数推导功能，增强C++未能提供的关于型别认证方面的能力
 * 弥补C++不为强型别(strong typed)语言的遗憾。
 */

