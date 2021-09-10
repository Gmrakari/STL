

/*
 * Date:2021-09-10 15:08
 * filename:03_Reverse_Iterators.cpp
 *
 */

/*
 * 所谓reverse_iterators，可以将一般迭代器的行进方向逆转，使原本应该前进的operator++变成了后退操作，
 * 使原本应该后退的operator--变成了前进操作。
 *
 * 如果STL算法接受的不是一般正常的迭代器，而是这种逆向迭代器，它就会从尾到头的方向来处理序列中的元素
 *
 * 例如:
 *
 * 将所有元素逆向拷贝到ite所指的位置上
 * rbegin()和rend()与reverse_iterator有关
 * copy(id.rbegin(), id.rend(), ite)
 *
 */

//任何STL容器都提供有这俩个操作
template <class T, class Alloc = alloc>
class vector {
public:
	typedef T value_type;
	typedef value_type* iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
};

template <class T, class Alloc = alloc>
class list {
public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	reverse_iterator rend() { reutrn reverse_iterator(begin()); }
};

template <class T, class Alloc = alloc>
class deque {
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	iterator begin() { return start; }
	iterator end() { return finish; }
	reverse_iterator rbegin() { return reverse_iterator(finish); }
	reverse_iterator rend() { return reverse_iterator(start); }

	//上述两式相当于:
	//reverse_iterator rbegin() { return reverse_iterator(end()); }
	//reverse_iterator rend() { return reverse_iterator(begin()); }
};

/*
 * 没有例外，只要双向序列容器提供了begin(),end(),它的rbegin(),rend()就是上面那样的型式
 * 单向序列容器如slist不可使用reverse iterator
 * stack,queue,priority_queue不提供begin(),end()
 *
 */
