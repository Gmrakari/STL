

/*
 * Date:2021-09-09 10:18
 * filename:06_Relational_functors.cpp
 *
 */

/*
 * 二元运算
 *
 * 等于(equality):equal_to<T>
 * 不等于(inequality):not_equal_to<T>
 * 大于(greater than) : greater<T>
 * 大于或等于(greater than or equal) : greater_equal<T>
 * 小于(less than) : less<T>
 * 小于或等于(less than or equal) : less_equal<T>
 *
 */

#include <iostream>
#include <functional>
using namespace std;

template <class Arg1, class Arg2, class Result>
struct __binary_function {
	typedef Arg1 first_argument_type;
	typedef Arg2 second_arugment_type;

	typedef Result result_type;
};

//Realational functors
template <class T>
struct __equal_to : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const { 
		return x == y;
	}
};

template <class T>
struct __not_equal_to : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x != y;
	}
};

template <class T>
struct __greater : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x > y;
	}
};

template <class T>
struct __less : public __binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x < y;
	}
};

template <class T>
struct __greater_equal : public __binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const {
		return x >= y;
	}
};

template <class T>
struct __less_equal : public __binary_function<T, T, bool> {
	bool operator() (const T& x, const T& y) const {
		return x <= y;
	}
};

int main() {
	//以下产生一些仿函数实体(对象)
	__equal_to<int> equal_to_obj;
	__not_equal_to<int> not_equal_to_obj;
	__greater<int> greater_obj;
	__greater_equal<int> greater_equal_obj;
	__less<int> less_obj;
	__less_equal<int> less_equal_obj;

	cout << "equal_to_obj(3, 5): ";
	cout << equal_to_obj(3, 5) << endl;

	cout << "not_equal_to_obj(3, 5): ";
	cout << not_equal_to_obj(3, 5) << endl;

	cout << "greater_obj(3, 5): ";
	cout << greater_obj(3, 5) << endl;

	cout << "greater_equal_obj(3, 5): ";
	cout << greater_equal_obj(3, 5) << endl;

	cout << "less_obj(3, 5): ";
	cout << less_obj(3, 5) << endl;

	cout << "less_equal_obj(3, 5): ";
	cout << less_equal_obj(3, 5) << endl;

	cout << endl << "-------------------------------------" << endl;
	//以仿函数的临时对象履行函数功能
	cout << "__equal_to<int>()(3, 5):";
	cout << __equal_to<int>()(3, 5) << endl;

	cout << "__not_equal_to<int>()(3, 5): ";
	cout << __not_equal_to<int>()(3, 5) << endl;

	cout << "__greater<int>()(3, 5): ";
	cout << __greater<int>()(3, 5) << endl;

	cout << "__greater_equal<int>()(3, 5): ";
	cout << __greater_equal<int>()(3, 5) << endl;

	cout << "__less<int>()(3, 5): ";
	cout << __less<int>()(3, 5) << endl;

	cout << "__less_equal<int>()(3, 5): ";
	cout << __less_equal<int>()(3, 5) << endl << endl;

}
