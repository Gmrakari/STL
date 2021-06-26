

/*
 * Date:2021-06-26 16:34
 * filename:10_deque_clear_and_erase.cpp
 *
 */

/*
 * deque::clear 用来清除整个deque,deque的最初状态(无任何元素时)保有一个缓冲区
 * 因此,clear()完成之后恢复初始状态，也一样要保留一个缓冲区
 *
 */

//注意 最终需要保留一个缓冲区。这是deque的策略，也是deque的初始状态
template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::clear() {
	//以下针对头尾以外的每一个缓冲区(它们一定都是饱满的)
	for (map_pointer node = start.node + 1; node < finish.node; ++node) {
		//将缓冲区内的所有元素析构。调用的是destroy()
		destroy(*node, *node + buffer_size());
		//释放缓冲区内存
		data_allocator::deallocate(*node, buffer_size());
	}

	if (start.node != finish.node) {												//至少有头尾两个缓冲区
		destroy(start.cur, start.last);												//将头缓冲区的目前所有元素析构
		destroy(finish.first, finish.cur);										//将尾缓冲区的目前所有元素析构
		//以下释放尾缓冲区。注意,头缓冲区保留
		data_allocator::deallocate(finish.first, buffer_size());
	}
	else //只有一个缓冲区
		destroy(start.cur, finish.cur);
	//注意，并不释放缓冲区空间。这是唯一的缓冲区将保留

	finish = start;//调整状态
}

/*
 * erase(),用来清除某个元素
 * 
 */

//清除pos所指的元素。pos为清除点
iterator erase(iterator pos) {
	iterator next = pos;
	++next;
	difference_type index = pos - start;//清除点之前的元素个数
	if (index < (size() >> 1)) {				//如果清除点之前的元素比较少
		copy_backward(start, pos, next);	//就移动清除点之前的元素
		pop_front();											//移动完毕，最前一个元素冗余，去除之
	}
	else {											//清除点之后的元素比较少
		copy(next, finish, pos);	//就移动清除点之后的元素
		pop_back();								//移动完毕,最后一个元素冗余，去除之
	}
	return start + index;	
}

/*
 * erase(),用来清除[first, last]区间内的所有元素
 *
 */

template<class T, class Alloc, size_t BufSize>
deque<T, Alloc, BufSize>::iterator
deque<T, Alloc, BufSize>::erase(iterator first, iterator last) {
	if (first == start && last == finish) {				//如果清除区间就是整个deque
		clear();													//直接调用clear()即可
		return finish;
	}
	else {																					//清除区间的长度 
		difference_type n = last - first;
		difference_type elems_before = first - start; //清除区间前方的元素个数
		if (elems_before < (size() - n) / 2) {				//如果前方的元素比较少
			copy_backward(start, first, last);					//向后移动前方元素(覆盖清除区间)
			iterator new_start = start + n;							//标记deuqe的新起点
			destroy(start, new_start);									//移动完毕，将冗余的元素析构

			//以下将冗余的缓冲区释放
			for (map_pointer cur = start.node; cur < new_start.node;++cur)
				data_allocator::deallocate(*cur, buffer_size());
		start = new_start;														//设定deque的新起点
		}
		else {																				//如果清除区间后方的元素比较少
			copy(last, finish, first);									//向前移动后方元素(覆盖清除区间)
			iterator new_finish = finish - n;						//标记deque的新尾点
			destroy(new_finish, finish);								//移动完毕，将冗余的元素析构
			
			//以下将冗余的缓冲区释放
			for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur) 
				data_allocator::deallocate(*cur, buffer_size());
			finish = new_finish;												//设定deque的新起点
		}
		return start + elems_before;
	}
}
