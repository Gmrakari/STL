

/*
 * Date:2021-06-05 15:15
 * filename:03_deque_data-structure.cpp
 *
 */

/*
 * deque除了维护一个指向map的指针外，也维护start,finish两个迭代器
 * 分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素(的下一位置)
 * 它也要记住目前map大小，一旦map所提供的节点不足，就必须重新配置更大的一块map
 *
 */

//__deque_buf_size()。BufSize 默认值为0的唯一理由是为了闪避某些
//编译器在处理常熟算式(constant expressions)时的臭虫缺省使用alloc为配置器
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef size_t size_type;

public:
	typedef __deque_iterator<T, T&, T* BufSiz> iterator;
protected:
	//元素的指针的指针(pointer of pointer of T)
	typedef pointer* map_pointer;

protected:
	iterator start;			//表现第一个节点
	iterator finish;		//表现最后一个节点

	map_pointer map;		//指向map,map是块连续空间，其每个元素都是指针，指向一个节点(缓冲区)
	size_type map_size; //map内有多少指针
}

public:
iterator begin() { return start; }
iterator end() { return finish; }

reference operator[] (size_type n) {
	return start[difference_type(n)];		//调用__deque_iterator<>::operator[]
}

reference front() { return *start; }	//调用__deque_iterator<>::operator*

reference back() {
	iterator tmp = finish;	
	--tmp;									//调用__deque_iterator<>::operator--
	return *tmp;						//调用__deque_iterator<>::operator*
}

//下行最后有两个';'，虽奇怪但合乎语法
size_type size() const { return finish - start;; }

//以上调用iterator::operator-
size_type max_size() const { return size_type(-1); }
bool empty() const { return finish == start; }

