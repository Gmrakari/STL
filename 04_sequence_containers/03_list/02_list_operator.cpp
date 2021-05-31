

/*
 * Date:2021-05-31 20:11
 * filename:02_list_operator.cpp
 *
 */

/*
 * push_front,push_back,erase,pop_front,pop_back,
 * clear,remove,unique,splice,merge,reverse,sort
 */

/*
 * insert,remove
 */

//插入一个节点，作为头结点
void push_front(const T& x) { insert(begin(),x); }

//插入一个节点，作为尾节点
void push_back(const T& x) { insert(end(),x); }

//移除迭代器position所指节点
iterator erase(iterator position) {
	link_type next_node = link_type(position.node->next);
	link_type prev_node = link_type(position.node->prev);
	prev_node->next = next_node;
	next_node->prev = prev_node;
	destroy_node(position.node);
	return iterator(next_node);
}

//移除头结点
void pop_front() { erase(begin()); }

//移除尾节点
void pop_back() {
	iterator tmp = end();
	erase(--tmp);
}

//清除所有节点(整个链表)
template <class T, class Alloc>
void list<T, Alloc>::clear() {
	link_type cur = (link_type) node->next;//begin()
	while( cur != node ) {	//遍历每一个节点
		link_type tmp = cur;
		cur = (link_type) cur->next;	
		destroy_node(tmp);		//销毁(析构并释放)一个节点
	}

	//恢复node原始状态
	node->next = node;
	node->prev = node;
}

//将数值为value之所有元素移除
template <class T, class Alloc>
void list<T, Alloc>::remove(const T& value) {
	iterator first = begin();
	iterator last = end();

	while (first != last) { //遍历每一个节点
		iterator next = first;
		++next;
		if (*first == value) erase(first);	//找到相同的就移除
		first = next;
	}
} 

//移除数值相同的连续元素,"连续 && 相同"
template <class T, class Alloc>
void list<T, Alloc>::unique() {
	iterator first = begin();
	iterator last = end();
	if (first == last) return ;				//空链表，什么都不操作
	iterator next = first;
	while (++next != last) {	//遍历每一个节点
		if (*first == *next)		//如果在此区段中有相同的元素
			erase(next);					//移除
		else
			first = next;					//调整指针
		next = first;						//修正区段范围
	}
}

//list内部提供了一个所谓的迁移操作(transfer):
//将某连续范围的元素迁移到某个特定位置之前。
//这个操作为splice,sort,merge等奠定基础

protected:
//将[first,last]内的所有元素移动到position之前
void transfer(iterator position, iterator first, iterator last) {
	if (position != last) {
		(*(link_type((*last.node).prev))).next = poistion.node;				//1
		(*(link_type((*first.node).prev))).next = last.node;					//2
		(*(link_type((*position.node).prev))).next = first.node;			//3
		link_type tmp = link_type((*last.node).prev);									//4
		(*position.node).prev = (*last.node).prev;										//5
		(*last.node).prev = (*first.node).prev;												//6
		(*first.node).prev = tmp;																			//7
	}
}

//transfer并非公开接口。
//list公开提供的是所谓的接合操作(splice):
//将某连续范围的元素从一个list移动到另一个(或同一个)list的某个定点



