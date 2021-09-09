

/*
 * Date:2021-09-09 10:38
 * filename:07_Logical_functors.cpp
 *
 */

/*
 * And 和Or 为二元运算，Not为一元运算
 *
 * 逻辑运算And : logical_and<T>
 * 逻辑运算Or: logical_or<T>
 * 逻辑运算Not: logical_not<T>
 *
 */


#include <iostream>
#include <functional>
using namespace std;

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
struct __logical_and : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x && y;
	}
};

template <class T>
struct __logical_or : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x || y;
	}
};

template <class T>
struct __logical_not : public __unary_function<T, bool> {
	bool operator() (const T& x) const {
		return !x;
	}
};

int main() {
	//以下产生一些仿函数实体(对象)
	__logical_and<int> and_obj;
	__logical_or<int> or_obj;
	__logical_not<int> not_obj;

	cout << "and_obj(true, true):";
	cout << and_obj(true, true) << endl;

	cout << "or_obj(true, true):";
	cout << or_obj(true, true) << endl;

	cout << "not_obj(true): ";
	cout << not_obj(true) << endl;

	//临时对象
	cout << endl << "------------------------------------------" << endl;
	cout << "__logical_and<int>()(true, true): ";
	cout << __logical_and<int>()(true, true) << endl;

	cout << "__logical_or<int>()(true, true): ";
	cout << __logical_or<int>()(true, true) << endl;

	cout << "__logical_not<int>()(true): ";
	cout << __logical_not<int>()(true) << endl;
}
