

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


/*
 * reverse_iterator源码
 *
 */
//这是一个迭代器配接器(iterator adapter)，用来将某个迭代器逆反前进方向，使前进为后退，后退为前进
template <class Iterator>
class reverse_iterator {
protected:
	Iterator current; //记录对应之正向迭代器

public:
	//逆向迭代器的5种相应型别(associated types)都和其对应的正向迭代器相同
	typedef typename iterator_traits<Iterator>::iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;
	typedef Iterator iterator_type;						//代表正向迭代器
	typedef reverse_iterator<Iterator> self;	//代表逆向迭代器

public:
	reverse_iterator() {}
	//下面这个ctor将reverse_iterator 与某个迭代器x系结起来
	explicit reverse_iterator(iterator_type x) : current(x) {}
	reverse_iterator(const self& x) : current(x.current) {}

	iterator_type base() const { return current; } //取出对应的正向迭代器
	reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
		//以上为关键所在。对逆向迭代器取值，就是将"对应之正向迭代器"后退一格而后取值
	}
	pointer operator->() const {
		return &(operator*());
	}

	//前进(++)变成后退(--)
	self& operator++() {
		--current;
		return *this;
	}

	self& operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}

	//后退(--)变成前进(++)
	self& operator--() {
		++current;
		return *this;
	}

	self operator--(int) {
		self tmp = *this;
		++current;
		return tmp;
	}

	//前进与后退方向完全逆转
	self operator+(difference_type n) const {
		return self(current - n);
	}
	
	self& operator+=(difference_type n) const {
		return self(current + n);
	}

	self& operator-=(difference_type n) {
		current += n;
		return *this;
	}

	//注意，下面第一个*和唯一一个+都会调用本类的operator*和operator+
	//第二个*则不会
	reference operator[](difference_type n) const {
		return *(*this + n);
	}
};
