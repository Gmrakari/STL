

/*
 * Date:2021-06-24 15:37
 * filename:07_deque_push_front.cpp
 *
 */

ideq.push_front(99);

push_front() 的操作如下

public:
void push_front(const value_type& t) {
	if (start.cur != start.first) {				//第一缓冲区尚有备用空间
		construct(start.cur - 1, t);				//直接在备用空间上构造元素
		--start.cur;												//调整第一缓冲区的使用状态
	}
	else																	//第一缓冲区已无备用空间
		push_front_aux(t);
}

//由于目前状态下，第一缓冲区并无备用空间，所以调用push_front_aux();


//只有当start.cur == start.first 时才会被调用
//也就是说，只有当第一个缓冲区没有任何备用元素时才会被调用

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_front_aux(const value_type& t) {
	value_type t_copy = t;
	reserve_map_at_front();								//若符合某种条件则必须重新更换一个map
	*(start.node - 1) = allocate_node();	//配置一个新节点(缓冲区)
	__STL_TRY {
		start.set_node(start.node - 1);			//改变start,令其指向新节点
		start.cur = start.last - 1;					//设定start的状态
		construct(start.cur, t_copy);				//针对标的元素设值
	}
	catch(...) {
		start.set_node(start.node + 1);
		start.cur = start.first;
		deallocate_node(*(start.node - 1));
		throw;
	}
}

