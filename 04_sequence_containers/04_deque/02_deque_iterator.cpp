

/*
 * Date:2021-06-04 20:08
 * filename:02_deque_iterator.cpp
 *
 */

/*
 * deque是分段连续空间。
 * 维持其"整体连续"假象的任务，落在了迭代器的operator++和operator--两个运算子身上
 *
 * 迭代器具备的结构:
 * 1-必须能够指出分段连续空间(亦即缓冲区)在哪里，
 * 2-它必须能够判断自己是否已经处于其所在缓冲区的边缘，如果是，一旦前进或后退就必须跳跃至下一个或上一个缓冲区
 * 3-为了能够正确跳跃，deque必须随时掌握管控中心(map)
 *
 */

template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator {
	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSiz> const_iterator;
	static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }

	//未继承std::iterator,必须自己写
	typedef random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T** map_pointer;

	typedef __deque_iterator self;

	//保持与容器的联结
	T* cur;						//此迭代器所指之缓冲区的现行(current)元素
	T* first;					//此迭代器所指之缓冲区的头
	T* last;					//此迭代器所指之缓冲区的尾(含备用空间)
	map_pointer node;	//指向管控中心
	...
};

//如果n不为0,传回n，表示buffer size由用户自定义
//如果n不为0,表示buffer size使用默认值,那么
//  如果sz(元素大小,sizeof(value_type))小于512,传回512/sz,
//  如果sz不小于512,传回1

inline size_t __deque_buf_size(size_t n, size_t sz) {
	return n != 0 ? n : (sz < 512 > size_t(512 / sz) : size_t(1));
}

/*
 * 假设现在我们产生一个型态为int,缓冲区大小为8(个元素)的deque
 * (语法形式为deuqe<int, alloc, 8>).经过某些操作之后，deque拥有20个元素，
 * 那么其begin()和end()所传回的两个迭代器应该如图(见ipad)
 * 这两个迭代器事实上一直保持在deque内，名为start和finish
 *
 * 20个元素需要20 / 8 = 3个缓冲区，所以map之内运用了三个节点。
 * 迭代器start内的cur指针当然指向缓冲区的第一个元素，迭代器finish内的
 * cur指针当然指向缓冲区的最后元素(的下一位置)
 * 注意，最后一个缓冲区尚有备用空间。
 * 稍后如果有新元素要插入尾端，可直接拿此备用空间来使用
 *
 */

/*
 * deuqe迭代器的几个关键行为
 * 由于迭代器内部对各种指针运算都进行了重载操作，所以各种指针运算
 * 如加、减、前进、后退都不能直观视之。
 * 其中最关键的就是:
 * 一旦行进时遇到缓冲区边缘，要特别小心，视前进或后退而定，可能需要
 * 调用set_node()跳一个缓冲区
 *
 */

void set_node(map_pointer new_node) {
	node = new_node;
	first = *new_node;
	last = first + difference_type(buffer_size());
}

reference operator*() const { return *cur; }
pointer operator->() const { return &(operator*()); }
difference_type operator-(const self& x) const {
	return difference_type(buffer_size()) * (node - x.node -1) + 
		(cur - first) + (x.last - x.cur);
}

//Distinguish between prefix and postfix forms of increment and decrement operators
self& operator++() {
	++cur;									//切换至下一个元素
	if (cur == last) {			//如果已达所在缓冲区的尾端
		set_node(node + 1);		//就切换至下一节点(亦即缓冲区)的第一个元素
		cur = first;
	}
	return *this;
}

self operator++(int) {		//后置式 标准写法
	self tmp = *this;	
	++*this;
	return tmp;
}

self& operator--() {
	if (cur == first) {			//如果已达所在缓冲区的头端
		set_node(node - 1);		//就切换至前一节点(即缓冲区)的最后一个元素(的下一位置)
		cur = last;
	}
	--cur;									//切换至前一个元素
	return *this;
}

self operator--(int) {		//后置式 标准写法
	self tmp = *this;
	--*this;
	return tmp;
}

//以下实现随机存取。迭代器可以直接跳跃n个距离
self& operator+=(difference_type n) {
	difference_type offset = n + (cur - first);
	if (offset >= 0 && offset < difference_type(buffer_size()))
		//目标位置在同一缓冲区内
		cur += n;
	else {
		//标的位置不在同一缓冲区内
		difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size())
																					 : -difference_type((-offset - 1) / buffer_size()) - 1;
		//切换至正确的节点(亦即缓冲区)
		set_node(node + node_offset);
		
		//切换至正确的元素
		cur = first + (offset - node_offset * difference_type(buffer_size()));
	}
	return *this;
}

//Consider using op= insterd of stand-alone op
self operator+(difference_type n ) const {
	self tmp = *this;
	return tmp += n;			//call operator+=
}

self& operator-=(difference_type n) { return *this += -n;}
//以上利用operator+=来完成operator-=

//Consider using op= instead of stand-alone op
self operator-(difference_type n) const {
	self tmp = *this;
	return tmp -= n; //call operator-=
}

//以下实现随机存取，迭代器可以直接跳跃n个距离
reference operator[] (difference_type n) const { return *(*this + n); }

bool operator==(const self& x) const { return cur == x.cur; }
bool operator!=(const self& x) const { return !(*this == x); }
bool operator<(const self& x) const  {
	return (node == x.node) ? (cur < x.cur) : (node < x.node);
}


