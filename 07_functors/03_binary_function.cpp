

/*
 * Date:2021-09-08 20:55
 * filename:03_binary_function.cpp
 *
 */

/*
 * binary_function用来呈现二元函数的第一参数型别、第二参数型别，以及回返值型别
 */

//STL规定，每一个Adaptable Binary Function 都应该继承此类别
template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_arugment_type;

	typedef Result result_type;
};

/*
 * 一旦某个仿函数继承了binary_funciton，其用户便可以这样取得该仿函数的各种相应型别
 */

template <class T>
struct plus : public binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const { return x + y; }
};

//以下配接器(adapter)用来将某个二元仿函数转化为一元仿函数
template <class Operation>
class binder1st {
	...
protected:
		Operation op;
		typename Operation::first_argument_type value;
public:
		typename Operation::result_type
			operator() (const typename Operation::second_arugment_type& x) const {

			}
};
