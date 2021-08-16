

/*
 * Date:2021-08-16 10:29
 * filename:05_hashtable的构造与内存管理.cpp
 *
 */

//hash table 定义一个专属的节点配置器
typedef simple_alloc<node, Alloc> node_allocator;

node* new_node(const value_type& obj) {
	node* n = node_allocator::allocate();
	n->next = 0;
	__STL_TRY {
		construct(&n->val, obj);
		return n;
	}

	__STL_UNWIND(node_allocator::deallocate(n));
}

void delete_node(node* n) {
	destroy(&n->val);
	node_allocator::deallocate(n);
}

//<value, key, hash-func, extract-key, equal-key, allocator>
//注意 hash table 没有供应default constructor
hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>
iht(50, hash<int>(), equal_to<int>());

cout << iht.size() << endl;
cout << iht.bucket_count() << endl;//STL 提供的第一个质数

//构造函数
hashtable(size_type n, const HashFcn& hf, const EqualKey& eql) 
	: hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0) {
		initialize_buckets(n);
}

void initialize_buckets(size_type n) {
	const size_type n_buckets = next_size(n);
	//举例子:传入50,返回53
	//以下首先保存53个元素空间，然后将其全部填0
	buckets.reserve(n_buckets);
	buckets.insert(buckets.end(), n_buckets, (node*)0);
	num_elements = 0;
}

//next_size() 返回最接近n并大于或等于n的质数
size_type next_size(size_type n) const { return __stl_next_prime(n); }

//然后为buckets vector 保留空间，设定所有buckets的初值为0(null 指针)


//插入操作(insert)与表格重整(resize)

iht.insert_unique(59);
iht.insert_unique(63);
iht.insert_unique(108);

//hash table内将会进行以下操作
//插入元素 不允许重复
pair<iterator, bool> insert_unique(const value_type& obj) {
	reseize(num_elements + 1);//判断是否需要重建表格，如需要就扩充
	return insert_unique_noresize(obj);
}

//以下函数判断是否需要重建表格。如果不需要，立即回返。如果需要，重建
template <class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::resize(size_type num_elements_hint) {
	//以下,"表格重建与否"的判断原则是拿元素个数(把新增元素计入后)和bucket vector的大小来比
	//如果前者大于后者，就重建表格,由此可判知，每个bucket(list)的最大容量和buckets vector的大小相同
	const size_type old_n = buckets.size();
	if (num_elements_hint > old_n) {
		const size_type n = next_size(num_elements_hint);//找出下一个质数
		if (n > old_n) {
			vector<node*, A> tmp(n, (node*)0);//设立新的buckets
			__STL_TRY {
				//以下处理每一个旧的bucket
				for (size_type bucket = 0; bucket < old_n; ++bucket) {
					node* first = buckets[bucket];//指向节点对应之串行的起始节点
					//一下处理每一个旧bucket 所含(串行)的每一个节点
					while (first) {
						//串行还没结束
						//以下找出节点落在哪一个新bucket内
						size_type new_bucket = bkt_num(first->val, n);

						//4个奇妙操作
						//1、令旧bucket指向其对应之串行的下一个节点(以便迭代处理)
						buckets[bucket] = first->next;
						//2,3、 将当前节点插入到新bucket内，成为其对应串行的第一个节点
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						//4、回到旧bucket所指的待处理串行，准备处理下一节点
						first = buckets[bucket];
					}
				}
				buckets.swap(tmp);//vector::swap 新旧两个buckets对调
				//注意，对调两方如果大小不同，大的会变小，小的会变大
				//离开时释放local tmp的内存
			}
		}
	}
}

//在不需重建表格的情况下插入新节点。键值不允许重复
template <class V, class K, class HF, class Ex, class Eq, class A>
pair<typename hashtable<V, K, HF, Ex, Eq, A>::iterator, bool>
hashtable<V, K, HF, Ex, Eq, A>::insert_unique_noresize(const value_type& obj) {
	const size_type n = bkt_num(obj);//决定obj应位于#n bucket
	node* first = buckets[n]; //令first指向bucket对应之串行头部

	//如果buckets[n]已被占用，此时first将不为0,于是进入以下循环，走过bucket所对应的整个链表
	for (node* cur = first, cur; cur = cur->next)
		if (equals(get_key(cur->val), get_key(obj)))
			//如果发现与链表中的某键值相同,就不插入，立即返回
			return pair<iterator, bool>(iterator(cur, this), false);

	//离开以上循环(或根本未进入循环)时，first指向bucket所指链表的头部节点
	node* tmp = new_node(obj);//产生新节点
	tmp->next = first;
	buckets[n] = tmp;//令新节点成为链表的第一个节点
	++num_elements;//节点个数累加1
	return pair<iterator, bool>(iterator(tmp, this), true);
}

//如果客户端执行的是另一种节点插入行为(不再是insert_unique，而是insert_equal)
iht.insert_equal(59);
iht.insert_equal(59);

//进行的操作如下:
//插入元素，允许重复
iterator insert_equal(const value_type& obj) {
	resize(num_elements + 1);//判断是否重建表格
	return insert_equal_noresize(obj);
}

//在不需要重建表格的情况下插入新节点.键值允许重复
template<class V, class K, class HF, class Ex, class Eq, class A>
typename hashtable<V, K, HF, Ex, Eq, A>::iterator
hashtable<V, K, HF, Ex, Eq, A>::insert_equal_noresize(const value_type& obj) {
	const size_type n = bkt_num(obj);//决定obj应为于#n bucket
	node* first = bucket[n];//令first指向bucket对应之链表头部

	//如果bucket[n]已被占用，此时first将不为0,于是进入以下循环，走过bucket所对应的整个链表
	for (node* cur = first; cur; cur = cur->next) 
		if (equals(get_key(cur->val), get_key(obj))) {
			//如果发现与链表中的某键值相同，就马上插入，然后返回
			node* tmp = new_node(obj);
			tmp->next = cur->next;//将新节点插入于目前位置之后
			cur->next = tmp;
			++num_elemennts;//节点个数累加1
			return iterator(tmp, this);//返回一个迭代器，指向新增节点
		}

	//进行到此，表示没有发现重复的键值
	node* tmp = new_node(obj);//产生新节点
	tmp->next = first;//将新节点插入于链表头部
	buckets[n] = tmp;
	++num_elements;//节点个数累加1
	return iterator(tmp, this);//返回一个迭代器，指向新增节点
}

//判知元素的落脚处(bkt_num)
//version1:接受实值(value)和buckets个数
size_type bkt_num(const value_type& obj, size_t n) const {
	return bkt_num_key(get_key((obj), n);// call version:4
}

//version2:只接受实值(value)
size_type bkt_num(const value_type& obj) const {
	return bkt_num_key(get_key(obj));//call version:3
}

//version3:只接受键值
size_type bkt_num_key(const key_type& key) const {
	return bkt_num_key(key, buckets.size());//call version4
}

//version4:接受键值和buckets个数
size_type bkt_num_key(const key_type& key, size_t n) const {
	return hash(key) % n;//SIG的所有内建的hash 列于5.7.7 hash functions
}

//复制(copy_from)和整体删除(clear)
//	由于整个hash table由vector和linked-list组合而成，因此，复制和整体删除，都特别需要注意内存的释放问题
template <class V, class K, class HF, class Ex, class Eq, class A>
	void hashtable<V, K, HF, Ex, Eq, A>::clear() {
		//针对每一个bucket.
		for (size_type i = 0; i < buckets.size(); ++i) {
			node* cur = buckets[i];
			//将bucket list中的每一个节点删除掉
			while (cur != 0) {
				node* next = cur->next;
				delete_node(cur);
				cur = next;
			}
			buckets[i] = 0;//令bucket内容为null指针
		}
		num_elements = 0;//令总节点个数为0

		//注意,buckets vector并未释放掉空间，仍保有原来大小
	}

template <class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::copy_from(const hashtable& ht) {
	//先清除己方的buckets vector.这操作是调用vector::clear.
	//将整个容器清空buckets.clear();
	buckets.clear();
	//为己方的buckets vector保留空间，使与对方相同
	//如果己方空间大于对方，就不动，如果己方空间小于对方，就会增大
	buckets.reserve(ht.buckets.size());
	//从己方的buckets vector尾端开始，插入n个元素，其值为null指针
	//注意,此时buckets vector为空，所以所谓尾端，就是起头处
	buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
	__STL_TRY {
		//针对buckets vector
		for (size_type i = 0; i < ht.buckets.size(); ++i) {
			//复制vector的每一个元素(是个指针，指向hashtable节点)
			if (const node* cur = ht.buckets[i]) {
				node* copy = new_node(cur->val);
				buckets[i] = copy;

				//针对同一个bucket list,复制每一个节点
				for (node* next = cur->next; next; cur = next, next = cur->next) {
					copy->next = new_node(next->val);
					copy = copy->next;
				}
			}
		}
		num_elements = ht.num_elements;//重新登录节点个数(hashtable的大小)
	}
	__STL_UNWIND(clear());
}





