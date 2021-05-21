

/*
 * Date:2021-05-21 14:42
 * filename:05_iterator_category.cpp
 *
 */

/*
 * 根据移动特性与实行操作，迭代器被分为5类:
 * Input Iterator:这种迭代器所指的对象，不允许外界改变。只读(read only)
 * Output Iterator:唯写(write only)
 * Forward Iterator:允许"写入型"算法(例如replace())在此种迭代器所形成的区间上进行读写操作
 * Bidiectional Iterator:可双向移动。
 * 某些算法需要逆向走访某个迭代器区间(例如逆向拷贝某范围内的元素)，可以用Bidiectional Iterator
 * Random Access Iterator:前四种迭代器都只供应一部分指针算术能力(前三种支持operator++,第四种再加上operator--)
 * 第五种则涵盖所有指针算术能力,包括p + n,p - n,p[n], p1 - p2, p1 < p2;
 *
 * Input Iterator 		Output Iterator
 * 			\										/
 * 				Forward Iterator
 *							|
 *			Bidiectional Iterator
 *							|
 *			Random Access Iterator
 *
 */

/*
 * advance()
 * 该函数有两个参数，迭代器p和数值n;函数内部将p累进n次(前进n距离)
 */

/*
 * Input Iterator
 */
template <class InputIterator,class Distance>
void advance_II(InputIterator& i,Distance n) {
	//单向，逐一前进
	while (n--) ++i;	//== for (; n > 0; --n, ++i)
}

template <class BidirectionalIterator,class Distance>
void advance_BI(BidirectionalIterator& i, Distance n) {
	//双向，逐一前进
	if (n >= 0) 
		while (n--) ++i;
	else
		while (n++) --i;
}

template <class RandomAccessIterator, class Distance> 
void advance_RAI(RandomAccessIterator& i, Distance n) {
	//双向,跳跃前进
	i += n;
}

/*
 * 如果程序调用advance()时，应该选用哪一份函数定义呢
 * 如果选择advance_II(),对Random Access Iterator而言极度缺乏效率
 * 原本O(1)变成O(N)。如果选择advance_RAI()，则无法接受Input Iterator
 * 三者合一的做法:
 */
template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n) {
	if (is_random_access_iterator(i))
		advance_RAI(i, n);
	else if (is_bidirectional_iterator(i))
		advance_BI(i, n);
	else
		advance_II(i, n);
}

/*
 * 上面的在执行时期才能决定使用哪一个版本，会影响程序效率
 * 最好能够在编译期就选择正确的版本，重载函数机制可以达成这个目标
 *
 * 前述三个advance_xx()都有两个函数参数，型别都未定(因为都是template 参数)
 * 为了令其同名，形成重载函数，我们必须加上一个型别已确定的函数参数，使函数重载机制得以有效运作起来
 */

/*
 * 设计:
 * 如果traits有能力萃取出迭代器的种类，我们便可利用这个"迭代器类型"相应型别作为advance()的第三个参数
 * 这个相应性别一定必须是一个class type,不能只是数值号码类的东西，因为编译器需依赖它(一个型别)
 * 来进行重载决议(overloaded resolution)
 */

//五个作为标记用的型别(tag types)
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

/*
 * 这些classes只作为标记用，所以不需要任何成员
 * 现在重新设计__advance()，并加上第三参数，使它们形成重载:
 */
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
	while (n--) ++i;
}

//这是一个单纯的传递调用的函数(trivial forwarding function)
template <class ForwardIterator, class Distance>
inline void __advance(ForwardIterator& i, Distance n, forward_iterator_tag)
{
	//单纯地进行传递调用(forwarding)
	_advance(i, n, input_iterator_tag());
}

template <class BidiectionalIterator, class Distance>
inline void __advance(BidiectionalIterator& i, Distance n, bidirectional_iterator_tag) {
	//双向，逐一前进
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
	i += n;
}

/*
 * 以上每个__advance()的最后一个参数都只声明型别，并未指定参数名称，因为它纯粹只是用来激活重载机制
 * 函数之中根本不使用该函数
 */

/*
 * 到这里，还需要一个对外开放的上层控制接口，调用上述各个重载的__advance()
 * 这一上层接口只需要两个参数，当它准备将工作转给上述的__advance()时，才自行加上第三个参数:迭代器类型
 * 因此 这个上层函数必须有能力从它所获得的迭代器中推导出其类型--这份工作自然交给traits机制:
 */

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
	__advance(i, n, iterator_traits<InputIterator>::iterator_category());
}

// iterator_traits<InputIterator>::iterator_category() 将产生一个暂时对象，其型别应该隶属前述四个迭代器类型(I,F,B,R)之一
// 然后根据这个型别，编译器才决定调用哪一个__advance()重载函数

/*
 * 因此traits必须再增加一个相应的型别:
 */
template <class I>
struct iterator_traits {
	...
	typedef typename I::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	...
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T*> {
	...
	typedef random_access_iterator_tag iterator_category;
};

/*
 * 任何一个迭代器，其类型永远落在"该迭代器所隶属之各种类型中，最强化的那个"
 * 例如,int*即时Random Access Iterator,又是Bidirectional Iterator,同时也是Forward Iterator,也是Input Iterator
 * 那么，其类型应该归属于random_access_iterator_tag
 */



