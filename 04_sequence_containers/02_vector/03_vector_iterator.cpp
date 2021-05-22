

/*
 * Date:2021-05-22 16:31
 * filename:03_vector_iterator.cpp
 *
 */

/*
 * vector 维护的是一个连续线性空间，所以不论其元素型别如何，普通指针都可以作为vector的迭代器而满足所有必要条件
 * 因为vector迭代器所需要的操作行为,如:
 * operator*,operator->,operator++,operator--,operator+,operator-,operator+=,operator-=,
 * 普通指针天生就具备。vector支持随机存取,而普通指针正有着这样的能力
 */

template <class T, class Alloc = alloc>
class vector {
public:
	typedef T						value_type;
	typedef value_type* iterator;
};

vector<int>::iterator ivite;
vector<Shape>::iterator svite;

/*
 * ivite 的型别起始就是int*
 * svite的型别起始就是Shapte*
 */


