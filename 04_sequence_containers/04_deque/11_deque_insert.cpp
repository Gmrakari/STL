

/*
 * Date:2021-06-26 17:00
 * filename:11_deque_insert.cpp
 *
 */

/* insert
 * deque为这个功能提供了许多版本，最基础最重要的是以下版本
 * 允许在某个点(之前)插入一个元素，并设定其值
 */

//position处插入一个元素，其值为x
iterator insert(iterator position ,const value_type& x) {
	if (position.cur == start.cur) {
		push_front(x);
		return start;
	}
	else if(position.cur == finish.cur) {
		push_back(x);
		iterator tmp = finish;
		--tmp;
		return tmp;
	} else {
		return insert_aux(position, x);
	}
}


template<class T, class Alloc, size_t BufSize>
typename deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::insert_aux(iterator pos, const value_type& x) {
	difference_type index = pos - start;		//插入点之前的元素个数
	value_type x_copy = x;
	if (index < size() / 2) {								//如果插入点之前的元素个数比较少
		push_front(front());									//在最前端加入与第一个元素同值的元素
		iterator front1 = start;							//以下标示记号，然后进行元素移动
		++front1;
		iterator front2 = front1;
		++front2;
		pos = start + index;
		iterator pos1 = pos;
		++pos1;
		copy(front2, pos1, front1);						//元素移动
	}
	else {																	//插入点之后的元素个数比较少
		push_back(back());										//在最尾端加入与最后元素同值的元素
		iterator back1 = finish;							//以下标示记号，然后进行元素移动
		--back1;
		iterator back2 = back1;
		--back2;
		pos = start + index;
		copy_backward(pos, back2, back1);			//元素移动
	}
	*pos = x_copy;													//在插入点上设定新值
	return pos;
}
