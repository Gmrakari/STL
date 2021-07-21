

/*
 * Date:2021-07-21 15:23
 * filename:02_priority_queue_定义完整列表.cpp
 *
 */

/*
 * 由于priority_queue完全以底部容器为根据，再加上heap处理规则，所以其实现非常简单
 *
 * queue以底部容器完成其所有工作。具有这种"修改某物接口，形成另一种风貌"之性质者，称为adapter(配接器)
 * 因此,STL priority_queue往往不被归类为container(容器),而被归类为container adapter
 *
 */

template<class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type>>
class priority_queue {
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
	Compare comp;

public:
	priority_queue() : c() {}
	explicit priority_queue(const Compare& x) : c(), comp(x) {}

	//以下用到make_heap(), push_heap(), pop_heap() 都是泛型算法
	//注意，任一个构造函数都立刻于底层容器内产生一个implicit representation heap
	template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last, const Compare& x)
		: c(first, last), comp(x) { make_heap(c.begin(), c.end(), comp); }

	template<class InputIterator>
	priority_queue(InputIterator first, InputIterator last)
		: c(first, last) {make_heap(c.begin(), c.end(), comp);}

	bool empty() const { return c.empty(); }
	size_type size() const { return c.size(); }
	const_reference top() const { return c.front(); }
	void push(const value_type& x) {
		__STL_TRY {
			//push_heap 是泛型算法，先利用底层容器的push_back() 将新元素推入末端，再重排heap
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		__STL_UNWIND(c.clear());
	}

	void pop() {
		__STL_TRY {
			//pop_heap是泛型算法，从heap内取出一个元素。它并不是真正将元素弹出，而是重排heap,
			//然后再以底层容器的pop_back()取得被弹出的元素
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
		__STL_UNWIND(c.clear());
	}
};
