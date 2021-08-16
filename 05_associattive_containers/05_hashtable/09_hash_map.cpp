

/*
 * Date:2021-08-16 17:19
 * filename:09_hash_map.cpp
 *
 */


template <class Key, class T, class HashFcn = hash<Key>, class EqualKey = equal_to<Key>, class Alloc = alloc>
class hash_map {
	private:
		typedef hashtable<pair<const Key, T>, Key, HashFcn, select1st<pair<const Key, T>>, EqualKey, Alloc> ht;
		ht rep;// 底层机制是以hash table完成
	public:
		typedef typename ht::key_type key_type;
		typedef T data_type;
		typedef T mapped_type;
		typedef typename ht::value_type value_type;
		typedef typename ht:hasher hasher;
		typedef typename ht::key_equal key_equal;

		typedef typename ht::size_type size_type;
		typedef typename ht::difference_type difference_type;
		typedef typename ht::pointer pointer;
		typedef typename ht::const_pointer const_pointer;
		typedef typename ht::reference reference;
		typedef typename ht::const_reference const_reference;

		typedef typename ht::iterator iterator;
		typedef typename ht::const_iterator const_iterator;

		hasher hash_funct() const { return rep.hash_funct(); }
		key_equal key_eq() const { return rep.key_eq(); }

	public:
		//缺省使用大小为100的表格。将被hash table调整为最接近且较大之质数
		hash_map() : rep(100, hasher(), key_equal()) {}
		explicit hash_map(size_type n) :rep(n ,hasher(), key_equal()) {}
		hash_map(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}
		hash_map(size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eql) {}

		//以下 插入操作全部使用insert_unique(),不允许键值重复
		template <class InputIterator>
		hash_map(InputIterator f, InputIterator l) 
			: rep(100, hasher(), key_equal()) { rep.insert_unique(f, l); }
		template <class InputIterator>
		hash_map(InputIterator f, InputIterator l, size_type n)
			: rep(n, hasher(), key_equal()) { rep.insert_unique(f, l) }
		template <class InputIterator>
		hash_map(InputIterator f, InputIterator l, size_type n, const hasher& hf)
			: rep(n, hf, key_equal()) { rep.insert_unique(f, l); }
		template <class InputIterator>
		hash_map(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql)
			: rep(n, hf, eqal) { rep.insert_unique(f, l); }

	public:
		//所有操作几乎都有hash table对应版本。传递调用就行
		size_type size() const { return rep.size(); }
		size_type max_size() const { return rep.max_size(); }
		bool empty() const { return rep.empty(); }
		void swap(hash_map& hm) { rep.swap(hm.rep); }
		friend bool operator==__STL_NULL_TMPL_ARGS(const hash_map&, const hash_map&);

		iterator begin() const { return rep.begin(); }
		iterator end() const { return rep.end(); }

	public:
		pair<iterator, bool> insert(const value_type& obj) {
			return rep.insert_unique(obj);
		}

		void insert(InputIterator f, InputIterator l) {
			rep.insert_unique(f, l);
		}
	
		T& operator[](const key_type& key) {
			return rep.find_or_insert(value_type(key, T())).second;
		}

		iterator find(const key_type& key) { return rep.find(key); }

		size_type count(const key_type& key) const { return rep.count(key); }

		pair<iterator, iterator> equal_range(const key_type& key) {
			return rep.equal_range(key);

		pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
			return rep.equal_range(key);
		}

		size_type erase(const key_type& key) {return rep.erase(key);}
		void erase(iterator it) { rep.rease(it); }
		void erase(iterator f, iterator l) { rep.rease(f, l); }
		void clear() { rep.clear(); }

	public:
		void resize(size_type hint) { rep.resize(hint); }
		size_type bucket_count() const { return rep.bucket_count(); }
		size_type max_bucket_count() const { return rep.max_bucket_count(); }

		size_type elems_in_buckets(size_type n) const {
			return rep.elems_in_buckets(n);
		}

		template <class Value, class HashFcn, class EqualKey, class Alloc>
			inline bool operator==(const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm1,
					const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm2) {
				return hm1.rep == hm2.rep;
			}
}
