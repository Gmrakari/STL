

/*
 * Date:2021-09-22 20:37
 * filename:05_对参数进行绑定_bind1st_bind2nd.cpp
 *
 */

/*
 * 以下配接器用来将某个Adaptable Binary function转换为Unary Function
 */
template <class Operation>
class binder1st
	: public unary_function<typename Operation::second_argument_type, typename Operation::result_type> {

protected:
	Operation op;//内部成员
	typename Operation::first_argument_type value;//内部成员

public:
	//constructor
	binder1st(const Operation& x, const typename Operation::first_argument_type& y) 
		: op(x), value(y) {}	//将表达式和第一参数记录于内部成员

	typename Operation::result_type
		operator()(const typename Operation::second_argument_type& x) const {
			return op(value, x);
		}
};

//辅助函数，让我们得以方便使用binder1st<Op>
template <class Operation, class T>
inline binder1st<Operation> binder1st(const Operation& op, const T& x) {
	typedef typename Operation::first_argument_type arg1_type;
	return binder1st<Operation>(op, arg1_type(x));
	//先把x转型为op的第一个参数型别
}

//以下配接器用来将某个Adaptable Binary function 转换为Unary Function
template <class Operation>
class binder2nd
	: public unary_function<typename Operation::first_argument_type,
	typename Operation::result_type> {

protected:
	Operation op;
	typename Operation::second_argument_type value;
public:
	//constructor
	binder2nd(const Operation& x, const typename Operation::second_argument_type& y) 
		: op(x), value(y) {}

	typename Operation::result_type
		operator()(const typename Operation::first_argument_type& x) const {
			return op(x, value);
		}
};

//辅助函数，让我们得以方便使用binder2nd<Op>
template <class Operation, class T>
inline binder2nd<Operation> bind2nd(const Operation& op, const T& x) {
	typedef typename Operation::second_argument_type arg2_type;
	return binder2nd<Operation>(op, arg2_type(x));
	//先把x转型为op的第二参数型别
}


