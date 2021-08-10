

/*
 * Date:2021-08-10 14:09
 * filename:03_RB-tree的数据结构.cpp
 *
 */

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree {
protected:
	typedef void* void_pointer;
	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
	typedef __rb_tree_color_type color_type;
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef const value_type& reference;
	typedef rb_tree_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
protected:
	link_type get_node() { return rb_tree_node_allocator::allocate(); }
	void put_node(link_type p) { rb_tree_node_allocator::deallocate(p); }

	link_type create_node(const value_type& x) {
		link_type tmp = get_node();
		__STL_TRY {
			construct(&tmp->value_field, x);
		}
		__STL_UNWIND(put_node(tmp));
		return tmp;
	}

	link_type clone_node(link_type x) {	//复制一个节点(的值和色)
		link_type tmp = create_node(x->Value_field);
		tmp->color = x->color;
		tmp->left = 0;
		tmp->right = 0;
		return tmp;
	}

	void destroy_node(link_type p) {
		destroy(&p->value_field);//析构内容
		put_node(p);//释放内存
	}

protected:
	//RB-tree 只以三笔数据表现
	size_type node_count;			//追踪记录树的大小(节点数量)
	link_type header;					//这是实现上的一个技巧
	Compare key_compare;			//节点间的键值大小比较准则

	//获取header的成员
	link_type& root() const { return (link_type&)header->parent; }
	link_type& leftmost() const { return (link_type&)header->left; }
	link_type& rightmost() const { retun (link_type&)header->right; }

	//方便获取节点x的成员
	static link_type& left(link_type x) { return (link_type&)(x->left); }
	static link_type& right(link_type x) { return (link_type&)(x->right); }
	static link_type& parent(link_type x) { return (link_type&)(x->parent); }
	static reference value(link_type x) { return x->value_field; }
	static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
	static color_type& color(link_type x) { return (color_type&)(x->color); }

	//方便获取节点x的成员
	static link_type& left(base_ptr x) { return (link_type&)(x->left); }
	static link_type& right(base_ptr x) { return (link_type&)(x->right); }
	static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
	static reference value(base_ptr x) { return x->value_field; }
	static const Key& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
	static color_type& color(base_ptr x) { return (color_type&)(link_type(x)->color); }

	//求取极大值和极小值.node class 有实现此功能，交给他们完成即可
	static link_type minimum(link_type x) {
		return (link_type) __rb_tree_node_base::minimum(x);
	}

	static link_type maximum(link_type x) {
		return (link_type) __rb_tree_node_base::maximum(x);
	}

public:
	typedef __rb_tree_iterator<value_type, reference, pointer> iterator;

private:
	iterator __insert(base_ptr x, base_ptr y, const value_type& v);
	link_type __copy(link_type x, link_type p);
	void __erase(link_type x);
	void init() {
		header = get_node();//产生一个节点空间,令header指向它
		color(header) = __rb_tree_red;//令header为红色，用来区分header和root,在iterator.opeator--之中
		root() = 0;
		leftmost() = header;	//令header的坐子节点为自己
		rightmost() = header; //令header的右子节点为自己
	}

public:
	rb_tree(const Compare& comp = Compare())
		: node_count(0), key_compare(comp) { init(); }

	~rb_tree() {
		clear();
		put_node(header);
	}

	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>&
		operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);

public:
	Compare key_comp() const { return key_compare; }
	iterator begin() { return leftmost(); }
	iterator end() {return header;}
	bool empty() const { return node_count == 0; }
	size_type size() const { return node_count; }
	size_type max_size() const { return size_type(-1); }

public:

	//__insert / erase
	//将x插入到RB-tree中
	pair<iterator, bool> insert_unique(const value_type& x);
	//将x插入到Rb-tree中
	iterator insert_equal(const value_type& x);
};



