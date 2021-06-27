

/*
 * Date:2021-06-27 18:16
 * filename:01_intro_stack.cpp
 *
 */

/*
 * stack 是一种先进后出(First In Last Out,FILO)的数据结构.
 * 它只有一个出口,stack允许新增元素、移除元素、取得最顶端元素
 * 但除了最顶端外,没有任何其它方法可以存取stack的其它元素，意味着stack不允许有遍历行为
 * 将元素推入stack的操作称为push,将元素推出stack的操作称为pop
 *
 */

/*
 * stack定义完整列表
 *
 * 以某种既有容器作为底部结构，将其接口改变，使之符合"先进后出"的特性，
 * 形成一个stack,是很容易做到的.
 * deque是双向开口的数据结构，若以deque为底部结构并封闭其头端开口，便轻而易举形成了一个stack
 * 因此,SGI STL便以deque作为缺省情况下的stack底部结构,stack的实现因而非常简单
 *
 * 由于stack系以底部容器完成其所有工作，而具有这种"修改某物接口,形成另一种风貌"之性质者,称为adapter(适配器),
 * 因此,STL stack往往不被归类为container(容器),而被归类为container adapter.
 *
 */

template<class T, class Sequence = deque<T>>
class stack {
	//__STL_NULL_TMPL_ARGS 会开展为<> 见1.9.1
	friend bool operator== __STL_NULL_TMPL_ARGS(const stack&, const stack&);
	friend bool operator< __STL_NULL_TMPL_ARGS(const stack&, const stack&);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;

protected:
	Sequence c;	//底层容器
public:
	//以下完全利用Sequence c操作,完成stack操作
	bool empty() const {return c.empty();}
	size_type size() const {return c.size();}
	reference top() { return c.back(); }
	const_reference top() const {return c.back();}

	//deque 是两头可进出，stack是末端进，末端出
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
};

template<class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
	return x.c == y.c;
}

template<class T, class Sequence>
bool operator<(const stack<T, Sequence>& x, const stack<T, Sequence>& y) {
	return x.c < y.c;
}


