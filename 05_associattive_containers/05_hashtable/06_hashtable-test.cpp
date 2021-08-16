

/*
 * Date:2021-08-16 14:43
 * filename:06_hashtable-test.cpp
 *
 */

#include <hash_set>
#include <hash_map>
#include <iostream>

using namespace std;

int main() {
	//hash table
	//<value, key, hash-func, extract-key, equal-key, allocator>
	//node:hash-table has no default ctor
	hashtable<int, int, hash<int>, identity<int>, equal_to<int>, alloc>
		iht(50, hash<int>(), equal_to<int>());//指定保留50个buckets
	cout << iht.size() << endl;
	cout << iht.bucket_count() << endl;
	cout << iht.max_bucket_count() << endl;

	iht.insert_unique(59);
	iht.insert_unique(63);
	iht.insert_unique(108);
	iht.insert_unique(2);
	iht.insert_unique(53);
	iht.insert_unique(55);
	cout << iht.size() << endl;

	//hashtable iterator
	hashtable<int, int, hash<int> identity<int>, equal_to<int>, alloc>::iterator ite = iht.begin();

	for (int i = 0; i < iht.size();++i, ++ite) {
		cout << *ite << ' ';
	}
	cout << endl;

	//遍历所有buckets,如果其节点个数不为0,就打印出节点个数
	for (int i = 0; i < iht.bucket_count(); ++i) {
		int n = iht.elems_in_bucket(i);
		if (n != 0) 
			cout << "bucket[" << i << "]has" << n << "elems." << endl;
	}

	//bucket[0] has 1 elems;
	//bucket[2] has 3 elems;
	//bucket[6] has 1 elems;
	//bucket[10] has 1 elems;
	
	/*
	 * 为了验证"bucket(list)的容量就是buckets vector的大小"(就是从hashtable<T>::resize() 得知的结果),
	 * 我刻意将元素增加到54个，看看是否发生"表格重建(re-hashing)"
	 */
	for (int i = 0; i <= 47; i++)
		iht.insert_equal(i);
	cout << iht.size() << endl;					//54.元素(节点)个数
	cout << iht.bucket_count() << endl; //97 buckets个数

	//遍历所有buckets，如果其节点个数不为0,就打印出节点个数
	for (int i = 0;i < iht.bucket_count(); ++i) {
		int n = iht.elems_in_bucket(i);
		if (n != 0) 
			cout << "bucket[" << i << "]has" << n << "elems." << endl;
	}

	//print:
	//bucket[2] 和 bucket[11]的节点个数为2,其余的bucket[0] ~ bucket[47]的节点个数均为1
	//此外,bucket[53], [55], [59], [63]的节点个数均为1
	
	//以迭代器遍历hashtable,将所有节点的值打印出来
	ite = iht.begin();
	for (int i = 0; i < iht.size(); ++i, ++ite) 
		cout << *ite << ' ';
	cout << endl;

	//0 1 2 2 3 4 5 6 7 8 9 10 11 108 12 13 14 15 16 17 18 19 20
	//21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 
	//41 42 43 44 45 46 47 53 55 59 63
	
	cout << *(iht.find(2)) << endl;//2
	cout << iht.count(2) << endl;//2
}

//hash table find() & count() function
iterator find(const key_type& key) {
	size_type n = bkt_num_key(key);//首先寻找落在哪一个bucket内
	node* first;
	//以下，从bucket list的头开始，一一对比每个元素的键值。对比成功就跳出
	for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next) {}
	return iterator(first, this);
}

size_type count(const key_type& key) const {
	const size_type n = bkt_num_key(key);//首先寻找落在哪一个bucket内
	size_type result = 0;
	//以下,从bucket list的头开始，一一对比每个元素的键值。对比成功就累加1
	for (const node* cur = buckets[n]; cur; cur = cur->next)
		if (equals(get_key(cur->val), key))
			++result;
	return result;
}
