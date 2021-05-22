
/*
 * Date:2021-05-22 15:57
 * filename:02_intro.cpp
 */

/*
 * vector的数据安排与array相似
 * 两者的唯一差别在于空间的应用的灵活性。
 * array是静态空间，一旦配置了就不能改变(一切琐细得又客户端自己来:
 * 首先配置一块新空间，然后将元素从旧址一一搬往新址，再把原来的空间释还给系统)
 * vector是动态空间，随着元素的加入，它的内部机制会自行扩充以容纳新元素
 *
 * vector的实现技术，关键在于其对大小的控制以及重新配置时的数据移动效率
 *
 */
#include <bits/stdc++.h>
#include <new>
#include <vector>

template <class T,class Alloc = alloc>
class vector {
public:
	typedef T						value_type;
	typedef value_type* pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t			size_type;
	typedef ptrdiff_t		difference_type;
protected:
	typedef simple_alloc<value_type,Alloc> data_allocator;
	iterator start;					//表示目前使用空间的头
	iterator finish;				//表示目前使用空间的尾
	iterator end_of_storage;//表示目前可用空间的尾

	void insert_aux(iterator position, const T& x);
	void deallocate() {
		if (start)
			 data_allocator::deallocate(start, end_of_storage - start);
	}

	void fill_initialize(size_type n, const T& value) {
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
public:
	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
	bool empty() const { return begin() == end(); }
	reference operator[] (size_type n) { return *(begin() + n); }

	vector() : start(0), finish(0), end_of_storage(0) { }
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value) { fill_initialize(n, value); }
	vector(long n, const T& value) { fill_initialize(n, value); }
	explicit vector(size_type n) { fill_initialize(n, T()); }

	~vector() {
		destroy(start, finish);									//全局函数
		deallocate();														//这是vector的一个member function
	}

	reference front() { return *begin(); }			//第一个元素
	reference back() { return *(end() - 1); }		//最后一个元素
	void push_back(const T& x) {								//将元素插入至最尾端
		if (finish != end_of_storage ) {
			construct(finish, x);
			++finish;
		}
		else
			insert_aux(end(),x);				//这个是vector的一个member function
	}

	void pop_back() {								//将最尾端元素取出
		--finish;
		destroy(finish);
	}

	iterator erase(iterator position) {				//清楚某位置上的元素
		if (position + 1 != end())
			copy(position + 1, finish, position);	//后续元素往前移动
		--finish;
		destroy(finish);
		return position;
	}

	void resize(size_type new_size, const T& x) {
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}

	void resize(size_type new_size) { resize(new_size, T()); }
	void clear() { erase(begin(), end()); }

protected:
	//配置空间并填满内容
	iterator allocate_and_fill(size_type n, const T& x) {
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);									//全局函数
		return result;
	}

};


