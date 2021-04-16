
/*
 * Date:2021-04-14 14:25
 * file:by "The Annotated STL Sources" Page 233
 */

/*
 * set的特性是，所有的元素都会根据元素的键值自动被排序
 * set 底层是RB-tree实现
 */

template <class Key,class Compare = less<Key>,class Alloc = alloc>
class set
{
public:
	//typedefs:
	typedef Key key_type;
	typedef Key value_type;

	typedef Compare key_compare;
	typedef Compare value_compare;
private:
	/*
	template <class T>
			struct identity : public unary_function<T,T>
	{
		const T& operator() (const T& x) const { return x;}
	};
	*/

	typedef rb_tree<key_type,value_type,identity<value_type>,key_compare,Alloc> rep_type;
	rep_type t;//采用红黑树(Rb-tree)来实现set

public:
	typedef typename rep_type::const_pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::const_reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::const_iterator iterator;

	//iterator 由于const_iterator 迭代器无法执行写入操作。这是因为set的元素有一定的次序安排，不允许用户在任何处进行写入操作
	typedef typename rep_type::const_iterator const_iterator;
	typedef typename  rep_type::const_reverse_iterator reverse_iterator;
	typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
	typedef typename rep_type::size_type size_type;
	typedef typename rep_type::difference_type difference_type;

	//allocation/deallocation
	//set一定使用RB-tree的insert_unique()而非insert_equal()
	//multiset才使用RB-tree的insert_equal()
	//因为set不允许相同键值存在，multiset才允许相同键值存在
	
	set() : t(Compare()) {}
	explicit set(const Compare& comp) : t(comp) { }

	template <class InputIterator>
	set(InputIterator first,InputIterator last) : t(Compare()) { t.insert_unique(first,last);}

	template <class InputIterator>
	set(InputIterator first,InputIterator last,const Compare& comp) : t(comp) { t.insert_unique(first,last);}

	set(const set<Key,Compare,Alloc>& x) : t(x.t) {}
	set<Key,Compare,Alloc>& operator=(const set<Key,Compare,Alloc>& x) { t = x.t; return *this;}

}

//set操作行为，RB-tree都已经提供，set只要传递调用就可以

//accessors:
key_compare key_comp() const { return t.key_comp();}

//set的value_comp() 事实上为RB-tree的key_comp()
value_compare value_comp() const { return t.key_compare();}
iterator begin() const { return t.begin();}
iterator end() const { return t.end();}
reverse_iterator rbegin() const { return t.rbegin();}
reverse_iterator rend() const { return t.rend();}
bool empty() const { return t.empty();}
size_type size() const { return t.size();}
size_type max_size const { return t.max_size();}
void swap(set<Key,Compare,Alloc>& x) { t.swap(x.t);}

//insert/erase
typedef pair<iterator,bool> pair_iterator_bool;
pair<iterator,bool> insert(const value_type& x)
{
	pair<typename rep_type::iterator,bool> p = t.insert_unique(x);
	return pair<iterator,bool(p.first,p.second);
}

iterator insert(iterator position,const value_type& x)
{
	typedef typename rep_type::iterator rep_iterator;
	return t.insert_unique((rep_iterator&)position,x);
}

template <class InputIterator>
void insert(InputIterator first,InputIterator last)
{
	t.insert_unique(first,last);
}

void erase(iterator position)
{
	typedef typename rep_type::iterator rep_iterator;
	t.erase((rep_iterator&)position);
}

size_type erase(const key_type& x)
{
	return t.erase(x);
}

void erase(iterator first,iterator last)
{
	typedef typename rep_type::iterator rep_iterator;
	t.erase((rep_iterator&)first,(rep_iterator&)last);
}

void clear() { t.clear();}

//set operations
iterator find(const key_type& x) const { return t.find(x);}
size_type count(const key_type& x) const { return t.count(x);}
iterator lower_bound(const key_type& x) const { return t.lower_bound(x);}
iterator upper_bound(const key_type& x) const { return t.upper_bound(x);}
pair<iterator,iterator> equal_range(const key_type& x) const { return t.equal_range(x);}

//以下的__STL_NULL_TMPL_ARGS 被定义为<>
friend bool operator== __STL_NULL_TMPL_ARGS (const set&,const set&);
friend bool operator< __STL_NULL_TMPL_ARGS (const set&,const set&);

};

template <class Key,class Compare,class Alloc>
inline bool operator==(const set<key,Compare,Alloc>& x,const set<Key,Compare,Alloc>& y)
{
	return x.t == y.t;
}

template <class Key,class Compare,class Alloc>
intline bool operator<(const set<Key,Compare,Alloc>& x,const set<Key,Compare,Alloc>& y)
{
	return x.t < y.t;
}

