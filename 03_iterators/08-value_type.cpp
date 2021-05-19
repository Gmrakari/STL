

/*
 * Date:2021-05-19 16:57
 * filename:08-value_type.cpp
 *
 */

/*
 * 迭代器所指对象的型别,称为该迭代器的value type.
 * 07-associated types.cpp的参数型别推导技巧虽然可用于value type
 * 却非全面可用:万一 value type必须用于函数的传回值，就束手无策了
 * 毕竟函数的"template 参数推导机制"推而导之的只是参数，无法推导函数的返回值型别
 *
 */

template <class T>
struct MyIter{
	typedef T value_type;
	T* ptr;
	MyIter(T* p = 0) : ptr(p) {}
	T& operator*() const { return *ptr; }
};

template <class I>
typename I::value_type;
func(I ite) { return *ite; }

MyIter<int> ite(new int(8));
cout << func(ite); // line 27

/*
 * 注意,func()的回返型别必须加上关键词typename,因为T是一个template参数,在它被编译器具有现化之前，
 * 编译器对T一无所悉，换句话说，编译器此时并不知道MyIter<T>::value_type代表的是一个型别或是一个
 * member function 或是一个data member.关键词typename的用意在于告诉编译器这是一个型别,如此才能顺利
 * 通过编译
 */

/*
 * Partial Specialization(偏特化)的意义
 * 
 * 如果class template拥有一个以上的template参数,我们可以针对其中某个(或数个,但非全部)template参数进行特化工作
 * 换句话说，我们可以在泛化设计中提供一个特化版本(也就是将泛化版本中的某些template参数赋予明确的指定)
 */

template <typename U,typename V,typename T>
class C { ... };

/*
 * 所谓partial specialization的意思是提供另一份template定义式,而其本身仍为templatized
 * 《泛型思维》对partial specializeion的定义是:"针对(任何)template参数更进一步的条件限制所设计出来的一个特化版本"
 */
template <typename T>
class C{ ... }; 		//允许(接收)T为任何型别

//partial soecialization:
template <typename T>
class C<T*> { ... };	//这个特化版本仅适用于"T为原生指针"的情况
						//"T"为原生指针便是"T为任何型别"的一个更进一步的条件限制

//针对"迭代器之template参数为指针"者,设计特化版的迭代器
//value_type正是迭代器的特性之一:
template <class T>
struct iterator_traits {
	typedef typename I::value_type value_type;
};

//这个traits的意义是,如果I定义有自己的value type，那么通过traits的作用，萃取出来的value_type
//就是I::value_type.换句话说,如果I定义有自己的value type,先前那个func()可以改写成这样:
template <class T>
typename iterator_traits<I>::value_type				//这一整行是函数回返型别
func(T ite)
{
	return *ite;
}

//除了多一层间接性,又带来什么好处?
//traits可以拥有特化版本,令iterator_traites拥有一个partial specializations:

template <class T>
struct iterator_traits<T*>{
	typedef T value_type;
};

/*
 * 针对"指向常数对象的指针(pointer-to-const)"
 */
iterator_traits<const int*>::value_type

/*
 * 获得的是const int而非int
 * 我们希望利用这种机制来声明一个暂时变量，使其型别与迭代器value type相同
 * 而现在,声明一个无法赋值(const)的暂时变量,没什么用
 * 因此,如果迭代器是一个pointer-to-const,我们一共设法令value type为一个
 * non-const型别
 */
template <class T>
struct iterator_traits<const T*>{			//偏特化版 --当迭代器是个pointer-to-const时
	typedef T value_type;					//萃取出来的型别应该是T 而非const T
};

//traits萃取机

template <class T>
struct iterator_traits{
	typedef typename I::iterator_category iterator_category;
	typedef typename I::value_type value_type;
	typedef typename I::difference_type difference_type;
	typedef typename I::pointer pointer;
	typedef typename I::reference reference;
};


