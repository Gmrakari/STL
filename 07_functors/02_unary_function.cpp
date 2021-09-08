

/*
 * Date:2021-09-08 20:51
 * filename:02_unary_function.cpp
 *
 */

/*
 * unary_function用来呈现一元函数的参数型别和返回值型别
 * 定义:
 */
template <class Arg, class Result>
struct unary_function {
	typedef Arg argument_type;
	typedef Result result_type;
};

/*
 * 一旦某个仿函数继承了unary_function，其用户便可以这样取得该仿函数的参数型别，并以相同手法取得其返回值型别
 *
 */

//继承unary_function
template <class T>
struct negate : public unary_function<T, T> {
	T operator() (const T& x) const {
		return -x;
	}
};

//以下配接器(adapter)用来表示某个仿函数的逻辑负值(logical negation)
template <class Predicate>
class unary_negate {
	...
public:
		bool operator() (const typename Predicate::argument_type& x) const {

		}
};
