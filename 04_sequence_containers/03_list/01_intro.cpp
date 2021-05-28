

/*
 * Date:2021-05-28 13:10
 * filename:01_intro
 *
 */

/*
 * 相较于vector连续性空间，list复杂许多，它的好处是每次插入或和删除一个元素
 * 就配置或释放一个元素空间
 * 对于任何位置的元素插入或删除移除,list永远是常熟时间
 *
 *
 * list和vector是两个最常被使用的容器
 *
 */

/*
 * list node
 */

template <class T>
struct __list_node {
	typedef void* void_pointer;
	void_pointer prev;
	void_pointer next;
	T data;
};

/*
 * list 的 iterator
 *
 * list不能再像vector一样以普通指针作为迭代器，因为其节点不保证再存储空间连续存在
 * list迭代器必须有能力指向list的节点，并有能力进行正确的递增、递减、取值、成员取值等操作
 *
 * 由于STL list是一个双向链表(double linked-list)，迭代器必须具备前移、后移的能力
 * 所以list提供的是Bidirectional Iterators
 *
 * list 有一个重要性质:插入操作(insert)和接合操作(splice)都不会造成原有list迭代器失效
 */

template <class T, class Ref, class Ptr>
struct __list_iterator {
	typedef __list_iterator<T, T&, T*>		iterator;
	typedef __list_iterator<T, Ref, Ptr>	self;

	typedef bidirectional_iterator_tag iterator_category;
	typedef T	value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef __list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	link_type node;

	//constructor
	__list_iterator(link_type x) : node(x) { }
	__list_iterator() {} 
	__list_iterator(const iterator& x) : node(x.node) {}

	bool operator==(const self& x) const { return node == x.node; }
	bool operator!=(const self& x) const { return node != x.node; }

	//以下迭代器取值(dereference)，取的是节点的数据值
	reference operator*() const {reutrn (*node).data;}

	//以下是迭代器的成员存取(member access) 运算子的标准做法
	pointer operator->() const { return & (operator*()); }

	//对迭代器累加1，就是前进一个节点
	self& operator++() {
		node = (link_type)((*node).next);
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	//对迭代器减少1,就是后退一个节点
	self& operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
};

/*
 * list data structure
 * STL list 不仅是一个双向链表，而且还是一个环状双向链表,
 * 所以它只需要一个指针,便开业i完整表现整个链表
 *
 */

template <class T, class Alloc = alloc>
class list {
protected:
	typedef __list_node<T> list_node;
public:
	typeid list_node* link_type;

protected:
	link_type node;
};

iterator begin() { return (link_type)((*node).next); }
iterator end() { return node; }

bool empty() const { return node->next == node; }

size_type size() const {
	size_type result = 0;
	destance(begin(), end(), result);
	return result;
}

reference front() { return *begin(); }
reference back() { return *(--end()); }

