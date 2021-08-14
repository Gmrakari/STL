

/*
 * Date:2021-08-14 15:56
 * filename:04_hashtable的数据结构.cpp
 *
 */

/*
 * hashtable的bucket聚合体是以vector完成
 */

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable;

//...

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>//先前声明时，已给予Alloc默认值alloc
class hashtable {
public:
	typedef HashFcn hasher;		
	typedef EqualKey key_equal;	//为template型别参数重新定义一个名称
	typedef size_t size_type;		//为template型别参数重新定义一个名称

private:
	//以下三者都是function objects
	//标准型别(int,c-style string)的hasher
	hasher hash;
	key_equal equals;
	ExtractKey get_key;

	typedef __hashtable_node<Value> node;
	typedef simple_alloc<node, Alloc> node_allocator;

	vector<node*, Alloc> buckets;// 以vector完成
	size_type num_elements;

public:
	//bucket个数即buckets vector的大小
	size_type bucket_count() const { return buckets.size(); }
};

//Value :节点的实质型别
//Key:节点的键值型别
//HashFcn:hash function的函数型别
//ExtractKey:从节点中取出键值的方法(函数或仿函数)
//EqualKey:判断键值相同与否的方法(函数或仿函数)
//Alloc:控制配置器,缺省使用 std::alloc

/*
 * 虽然开链法(separate chaining)并不要求表格大小必须为质数，但SGI STL仍然以质数来设计表格带笑傲，
 * 并且先将28个质数(逐渐呈现大约两倍的关系)计算好，以备随时访问，同时提供一个函数，用来查询在这28个质数之中，
 * "最接近某书并大于某数"的质数:
 */
static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
	53,			97,			193,		389,		769,
	1543,		3079,		6151,		12289,		24593,
	49157,		98317,		196613,		393241,		786433,
	1572869,	3145739,	6291469,	12582917,	25165843,
	50331653,	100663319,	201326611,	402653189,	805306457,
	1610612741,	3221225473ul, 4294967291ul
};

//以下找出上述28个质数之中，最接近并大于或等于n的那个质数
inline unsigned long __stl_next_prime(unsigned long n) {
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);

	//以上,lower_bound() 是泛型算法
	//使用lower_bound(),序列需先排序
	return pos == last ? *(last - 1) : *pos;
}

//总共可以有多少buckets,一下是hast_table的一个member function
size_type max_bucket_count() const {
	return __stl_prime_list[__stl_num_primes - 1];
}//4294967291
