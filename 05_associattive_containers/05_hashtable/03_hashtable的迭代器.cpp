

/*
 * Date:2021-08-14 15:39
 * filename:03_hashtable的迭代器.cpp
 *
 */

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator {
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
	typedef ____hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
	typedef __hashtable_node<value> node;

	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;//迭代器目前所指之节点
	hashtable* ht;//保持对容器的连结关系(因为可能需要从bucket跳到bucket)

	__hashtable_iterator(node* n, hashtable* tab) :cur(n), ht(tab) {}
	__hashtable_iterator() {}
	reference operator*() const { return cur->val; }
	pointer operator->() const { return &(operator*()); }
	iterator& operator++();
	iterator operator++(int);
	bool operator==(const iterator& it) const { return cur == it.cur; }
	bool operator!=(const iterator& it) const { return cur != it.cur; }
}

/*
 * hashtable迭代器必须永远维系着与整个"buckets vector"的关系，并记录目前所指的节点
 * 其前进操作是首先尝试从目前所指的节点出发，前进一个位置(节点)，
 * 由于节点被安置于list内，所以利用节点的next指针即可轻易达成前进操作。
 * 如果目前节点正巧是list的尾端，就调至下一个bucket身上，那正是指向下一个list的头部节点
 */

template <class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>&
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++() {
	const node* old = cur;
	cur = cur->next;//如果存在，就是它，否则进入一下if流程
	if (!cur) {
		//根据元素值，定位出下一个bucket。其起头处就是我们的目的地
		size_type bucket = ht->bkt_num(old->val);
		while (!cur && ++bucket < ht->buckets.size()) 
			cur = ht->buckets[bucket];
	}
	return *this;
}

template <class V, class K, class HF, class ExK, class EqK, class A>
inline __hashtable_iterator<V, K, HF, ExK, EqK, A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int) {
	iterator tmp = *this;
	++*this;//调用operator++()
	return tmp;
}

/*
 * hashtable的迭代器没有后退操作(operator--()),hash table也没有定义所谓的逆向迭代器(reverse iterator)
 */

