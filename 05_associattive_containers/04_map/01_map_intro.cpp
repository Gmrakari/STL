

/*
 * Date:2021-08-13 09:53
 * filename:01_map_intro.cpp
 *
 */

//map的特性是，所有元素都会根据元素的键值自动被排序
//map所有元素都是pair,同时拥有实值(value)和键值(key)
//pair的第一个元素被视为键值(key),第二个元素被视为实值(value)
//map不允许两个元素拥有相同的键值


template <class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;
	pair() :first(T1()), second(T2()) {}
	pair(const T1& a, const T2& b) : first(a), second(b) {}
};

// map拥有和list相同的某些性质：
// 当客户端对它进行元素新增操作（insert）或者删除操作（erase)时，操作之前的所有迭代器，在操作完成之后都依然有效
// 被删除的那个元素的迭代器必然是个例外

//由于RB-tree是一种平衡二叉搜索树，自动排序的效果很不错，所以标准的STLmap即以RB-tree为底层机制
//又由于map所开放的各种操作接口，RB-tree也都提供了，所以几乎所有的map操作行为，都只是转调用RB-tree的操作行为而已

template <class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map {
	public:
		//typedefs:
		typedef Key key_type;//键值类型
		typedef T data_type;//数据(实值)型别
		typedef T mapped_type;
		typedef pair<const Key, T> value_type;	//元素型别(键值/实值)
		typedef Compare key_compare;//键值比较函数

		//以下定义一个functor,其作用就是调用"元素比较函数"
		class value_compare
			: public binary_function<value_type, value_type, bool> {
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare comp;
					value_compare(Compare c) :comp(c) {}
				public:
					bool operator() (const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
				}
			};
		
	private:
		//以下定义表述型别(representation type).以map元素型别(一个pair)的第一型别，作为RB-tree节点的键值型别
		typedef rb_tree<key_type, value_type, select1st<value_type>, key_compare, Alloc> rep_type;
		rep_type t;//以红黑树(RB-tree) 表现map
	public:
		typedef typename rep_type::pointer pointer;
		typedef typename rep_type::const_pointer const_pointer;
		typedef typename rep_type::reference reference;
		typedef typename rep_type::const_reference const_reference;
		typedef typename rep_type::iterator iterator;
		//注意map与set的区别，允许用户通过其迭代器修改元素的实值(value) [map]
		typedef typename rep_type::const_iterator const_iterator;
		typedef typename rep_type::reverse_iterator reverse_iterator;
		typedef typename rep_type::const_reverse_iterator const_reverse_iterator;
		typedef typename rep_type::size_type size_type;
		typedef typename rep_type::difference_type difference_type;

		//allocation/deallocation
		//map一定使用Rb-tree底层的insert_unique而不是insert_equal()
		//因为map不允许相同键值的存在，multimap才允许相同键值存在

		map() :t(Compare()) {}
		explicit map(const Compare& comp) :t(comp) {}
		
		template <class InputIterator>
		map(InputIterator first, InputIterator last)
			: t(Compare()) { t.insert_unique(first, last); }

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp)
		 : t(comp) { t.insert_unique(first, last); }

		map(const map<Key, T, Compare, Alloc>& x) : t( x.t ) {}
		map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc>& x) {
			t = x.t;
			return *this;
		}

		//accessors:
		//所有的map操作行为，RB-tree都已提供，map只需调用即可

		key_compare key_comp() const { return t.key_comp(); }
		value_compare value_comp() const { return value_compare(t.key_comp()); }
		iterator begin() { return t.begin(); }
		const_iterator begin() const { return t.begin();}
		iterator end() { return t.end(); }
		const_iterator end() const { return t.end(); }
		reverse_iterator rbegin() { return t.rbegin(); }
		const_reverse_iterator rbegin() { return t.rbegin();}
		reverse_iterator rend() { return r.rend(); }
		const_reverse_iterator rend() { retun t.rend(); }
		bool empty() const { return t.empty();}
		size_type size() const { return t.max_size(); }

		//注意以下 下标(subscript)操作符
		T& operator[](const key_type& k) {
			return (*((insert(value_type(k, T()))).first)).second；
		}
		void swap(map<Key, T, Compare, Alloc>& x) { t.swap(x.t); }

		//insert/erase
		//注意以下insert操作返回的型别
		pair<iterator, bool> insert(const value_type& x) {
			return t.insert_unique(x);
		}

		iterator insert(iterator position, const value_type& x) {
			return t.insert_unique(position, x);
		}

		template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				t.insert_unique(first, last);
			}

		void erase(iterator position) { t.erase(position); }
		size_type erase(const key_type& x) { return t.erase(x); }
		void erase(iterator first, iterator last) { t.erase(first, last); }
		void clear() { t.clear(); }

		//map opeartions:
		iterator find(const key_type& x) { return t.find(x); }
		const_iterator find(const key_type& x) { return t.find(x); }
		size_type count(const key_type& x) const { return t.count(x); }
		iterator lower_bound(const key_type& x) { return t.lower_bound(x); }
		const_iterator lower_bound(const key_type x) const { return t.lower_bound(x); }
		iterator upper_bound(const key_type& x) { return t.upper_bound(x); }
		const_iterator upper_bound(const key_type& x) const {
			return t.upper_bound(x);
		}

		pair<iterator, iterator> equal_range(const key_type& x) {
			return t.equal_range(x);
		}
		pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
			return t.equal_range(x);
		}
		friend bool operator== __STL_NULL_TMPL_ARGS(const map&, const map&);
		friend bool operator< __STL_NULL_TMPL_ARGS(const map&, cont map&);
};

template <class Key, class T, class Compare, class Alloc>
inline bool operator==(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
	return x.t == y.t;
}

template <class Key, class T, class Compare, class Alloc>
inline bool operator<(const map<Key, T, Compare, Alloc>& x, const map<Key, T, Compare, Alloc>& y) {
	return x.t < y.t;
}

