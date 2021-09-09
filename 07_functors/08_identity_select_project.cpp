

/*
 * Date:2021-09-09 11:05
 * filename:08_identity_select_project.cpp
 *
 */

/*
 * 仿函数，都只是将其参数原封不动地传回。其中某些仿函数对传回的参数有刻意的选择，或是刻意的忽略
 * 这种就是为了间接性-间接性是抽象化的重要工具
 *
 * SGI STL 
 * 证同函数(identity function) 任何数值通过此函数后，不会有任何改变
 * 此式运用于<stl_set.h> 用来指定RB-tree所需的KeyOfValue op
 * 那是因为set元素的键值即实值，所以采用identity
 */

/*
 * 为了与库函数自带的区别开来
 * 对binary_function 加__binary_function 处理
 * 对logical_and 加 __logical_and 处理
 *
 * 对unary_function 加__unary_function 处理
 * 下同
 */

template <class Arg, class Result>
struct __unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};

template <class Arg1, class Arg2, class Result>
struct __binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_arugment_type;

	typedef Result result_type;
};
template <class T>
struct identity : public __unary_function<T, T> {
	const T& operator()(const T& x) const {
		return x;
	}
};

/*
 * 选择函数(selection function) 接受一个pair,传回其第一元素
 * 此式运用于<stl_map.h> 用来指定RB-tree所需的KeyOfValue op
 * 由于map系以pair元素的第一元素为其键值，所以采用select1st
 */

template <class Pair>
struct select1st : public __unary_function<Pair, typename Pair::first_type> {
	const typename Pair::first_type& operator()(const Pair& x) const {
		return x.first;
	}
};


//选择函数:接受一个pair，传回其第二元素
//SGI STL 并未运用此式
template <class Pair>
struct select2nd : public __unary_function<Pair, typename Pair::second_type> {
	const typename Pair::second_type& operator()(const Pair& x) const {
		return x.second;
	}
};


//投射函数：传回第一参数，忽略第二参数
//SGI STL 并未运用此式
template <class Arg1, class Arg2>
struct project1st : public __binary_function<Arg1, Arg2, Arg1> {
	Arg1 operator()(const Arg1& x, const Arg2&) const {
		return x;
	}
};

//投射函数：传回第二参数，忽略第一参数
//SGI STL 并未运用此式
template <class Arg1, class Arg2>
struct project2nd : public __binary_function<Arg1, Arg2, Arg2> {
	Arg2 operator()(const Arg1&, const Arg2& y) const {
		return y;
	}
};
