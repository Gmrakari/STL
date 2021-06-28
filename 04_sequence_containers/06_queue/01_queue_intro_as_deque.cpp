

/*
 * Date:2021-06-28 15:28
 * filename:01_queue_intro_as_deque.cpp
 *
 */

/*
 * queue是一种先进先出(First In First Out, FIFO)的数据结构
 * 他有两个出口，queue允许新增元素、移除元素、从最低端加入元素、取得最顶端元素
 * 但除了最低端可以加入、最顶端可以取出外，没有任何其他方法可以存取queue的其他元素
 * 换言之,queue也不允许有遍历行为
 * 将元素推入queue的操作称为push，将元素推出queue的操作称为pop
 *
 */

/*
 * queue定义完整列表
 * 以某种既有容器为底部结构，将其接口改变，使其符合"先进先出"的特性，形成一个queue,是很容易做到的。
 * deque是双向开口的数据结构，若以deque为底部结构并封闭其底端的出口和前端的入口，便轻易而举地形成了一个queue.
 *
 * 跟stack类似，queue系以底部容器完成其所有工作，而具有这种"修改某物接口，形成另一种风貌"的性质者，称为adapter
 * queue被归类为container adapter
 *
 */

template<class T, class Sequence = deque<T>>
class queue {
	//__STL_NULL_TMPL__ARGS 见1.9.1
	friend bool operator==__STL_NULL_TMPL__ARGS(const queue& x, const queue& y);
	friend bool operator<__STL_NULL_TMPL__ARGS(const queue& x, const queue& y);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;

public:
	bool empty() const {return c.empty();}
	size_type size() const { return c.size(); }
	reference front() {return c.front();}
	const_reference front() const { return c.front(); }
	reference back() {return c.back();}
	const_reference back() const { return c.back();}

	//deuqe是两头可进出，queue是末端进、前端出(所以先进者先出)
	void push(const value_type& x) { c.push_back(x); }
	void pop() {c.pop_front();}
};

template<class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y) {
	return x.c == y.c;
}

template<class T, class Sequence>
bool operator<(const queue<T, Sequence>& x, const queue<T, Sequence>& y) {
	return x.c < y.c;
}
