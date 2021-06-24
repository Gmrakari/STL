

/*
 * Date:2021-06-24 15:09
 * filename:06_deque_push_back.cpp
 *
 */

public:
void push_back(const value_type& t) {
	if (finish.cur != finish.last - 1) {
		//最后缓冲区尚有两个(含)以上的元素备用空间
		construct(finish.cur, t);//直接在备用空间上构造元素
		++finish.cur;
	}
	else	//最后缓冲区只剩下一个元素备用空间
		push_back_aux(t);
	
}

//现在，如果再新增一个新元素于尾端 见ipad-deque.push_back图
ideq.push_back(3);

//由于尾端只剩下一个元素备用空间，于是push_back()调用push_back_aux(),
//先配置一整块新的缓冲区，再设妥新元素内容，然后更改迭代器finish的状态


//只有当finish.cur == finish.last - 1时才会被调用
//也就是说，只有当最后一个缓冲区只剩下一个备用元素空间时才会被调用

template<class T, class Alloc, size_t BufSize>
void deque<T, Alloc, BufSize>::push_back_aux(const value_type& t) {
	value_type t_copy = t;
	reserve_map_at_back();														//若符合某种条件则必须更换一个map
	*(finish.node + 1) = allocate_node();							//配置一个新节点(缓冲区)
	__STL_TRY {
		construct(finish.cur, t_copy);									//针对标的元素设值
		finish.set_node(finish.node + 1);								//改变finish,令其指向新节点
		finish.cur = finish.first;											//设定finish的状态
	}
	__STL_UNWIND(deallocate_node(*(finish.node + 1)));
}

/*
 * 在尾端增加一个元素的时候，会引发新缓冲区的配置
 * 同时也导致迭代器finish的状态改变
 * 见ipad deuqe.push_back图
 */

