

/*
 * Date:2021-09-12 11:08
 * filename:07_functor_adapter_intro.cpp
 *
 */

/*
 * functor adapters是所有配接器中数量最庞大的一个族群，其配接灵活度也是前二者所不能及，可以配接、配接、再陪接。
 * 这些配接操作包括系结(bind),否定(negate),组合(compose),以及对一般函数或成员函数的修饰
 * C++标准可以从<functional>获得配接器的使用
 *
 * function adapters的价值在于，通过它们之间的绑定、组合、修饰能力，几乎可以无限制地创造出各种可能的表达式(expression)
 * 例如:
 * 我们可能希望找出某个序列中所有不小于12的元素个数
 * "不小于"就是"大于或等于"，我们可以选择STL内建的仿函数greater_equal,但如果希望完全遵循题目语意，
 * 坚持找出不小于12的元素个数，可以这么做:
 * not1(bind2nd(less<int>(), 12))
 * 这个式子将less<int>()的第二参数系结(绑定)为12,再加上否定操作，便形成了"不小于12"的语意
 * 整个凑合成为一个表达式(express),可与任何"可就二手表达式为参数"之算法搭配
 */

/*
 * update:2021-09-16 10:55
 * function adapers 实现细节
 *
 * 容器是以class templates完成，算法是以funciton templates完成，仿函数是一种将operator()重载的class template
 * 迭代器则是一种将operator++和operator*等指针习惯常行为重载的class template
 *
 * container adapters内藏了一个container member一样，或是像reverse iterator(adapters)内藏了一个iterator member一样
 * 或是像stream iterator(adapters)内藏了一个pointer to stream一样，或是像insert iterator(adapters)内藏了一个
 * pointer to container(并因而得以取其iterator)一样，每一个function adapters也内藏了一个member object,其性别等同于它所
 * 要陪接的对象(那个对象当然是一个"可配接的仿函数",adaptable functor)
 * 当function adapter有了完全属于自己的一份修饰对象(的副本)在收，它就成了该修饰对象(的副本)的主人，也就有资格调用该
 * 修饰对象(一个仿函数)，并在参数和返回值上面动手脚了
 *
 * 见书P450
 *
 * count_if(iv.begin(), iv.end(), bin2nd(less<int>()< 12));
 * bin2nd会产生一个binder2nd<Operation>(...);对象，此将传给count_if()成为其pred参数
 *
 *
 */

template <class Operation>
class binder2nd : public unary_function<...> {
protected:
	Operation op;
	typename Operation::second_argument_type value;

public:
	binder2nd(const Operation& x, const typename Operation::second_argument_type& y) 
		: op(x), value(y) {}
	typename Operation::result_type operator()(const typename Operation::first_argument_type& x) const {
		return op(x, value);
	}
};





