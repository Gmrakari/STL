

/*
 * Date:2021-06-26 16:15
 * filename:09_deque_pop_back_and_pop_front.cpp
 *
 */

/*
 * pop,将元素拿掉，无论从deque的最前端或最尾端取元素，都需要考虑在某种条件下，将缓冲区释放掉
 */

void pop_back() {
	if (finish.cur != finish.first) {
		// 最后缓冲区有一个(或更多)元素
		--finish.cur;										//调整指针，相当于排除了最后元素
		destroy(finish.cur);						//将最后元素析构
	}
	else
		// 最后缓冲区没有任何元素
		pop_back_aux();									//这里将进行缓冲区的释放工作
}

//只有当finish.cur == finish.first才会被调用
template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_back_aux() {
	deallocate_node(finish.first);							//释放最后一个缓冲区
	finish.set_node(finish.node - 1);						//调整finish的状态，使指向上一个缓冲区的最后一个元素
	finish.cur = finish.last - 1;
	destroy(finish.cur);												//将该元素析构
}

void pop_front() {
	if (start.cur != start.last - 1) {
		//第一缓冲区有两个(或更多) 元素
		destroy(start.cur);							//将第一元素析构
		++start.cur;										//调整指针，相当于排除了第一元素
	}
	else
		//第一缓冲区仅有一个元素
		pop_front_aux();							//这里将进行缓冲区的释放工作
}

//只有当start.cur == start.last - 1时才会被调用
template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::pop_front_aux() {
	destroy(start.cur);													//将第一个缓冲区的第一个(也是最后一个、唯一一个)元素析构
	deallocate_node(start.first);								//释放第一个缓冲区
	start.set_node(start.node + 1);							//调整start的状态，使指向
	start.cur = start.first;										//下一个缓冲区的地一个元素
}


