

/*
 * Date:2021-09-08 21:02
 * filename:04_Arithmetic_functors.cpp
 *
 */

/*
 * 算术类(Arithmetic)仿函数
 * 支持加法、减法、乘法、除法、模数(余数，modulus)和否定(negation)运算
 *
 * 加法:puls<T>
 * 减法:minus<T>
 * 乘法:multiplies<T>
 * 除法:divides<T>
 * 模取(modulus):modulus<T>
 * 否定(negation):negate<T>
 *
 */
#include <functional>
#include <iostream>
using namespace std;


/*
 * 这里因为库里已经有binary_function
 * 如果再定义就重复定义了 
 * 我就改成__unary_function
 * 下面的仿函数就继承__unary_funtion
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
struct __plus : public __binary_function<T, T, T> {
	T operator()(const T& x, const T& y) const {
		return x + y;
	}
};

template <class T>
struct __minus : public __binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const {
		return x - y;
	}
};

template <class T>
struct __multiplies : public __binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const {
		return x * y;
	}
};

template <class T>
struct __divides : public __binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const {
		return x / y;
	}
};

template <class T>
struct __modulus : public __binary_function<T, T, T> {
	T operator() (const T& x, const T& y) const {
		return x % y;
	}
};

template <class T>
struct __negate : public __unary_function<T, T> {
	T operator() (const T& x) const {
		return -x;
	}
};

int main() {
	__plus<int> plusobj;
	__minus<int> minusobj;
	__multiplies<int> multipliesobj;
	__divides<int> dividesobj;
	__modulus<int> modulusobj;
	__negate<int> negateobj;

	//用上述对象，履行函数功能
	cout << "plusobj(3, 5) : ";
	cout << plusobj(3, 5) << endl;

	cout << "minusobj(3, 5) : ";
	cout << minusobj(3, 5) << endl;

	cout << "multipliesobj(3, 5) : ";
	cout << multipliesobj(3, 5) << endl;

	cout << "dividesobj(3, 5) : ";
	cout << dividesobj(3, 5) << endl;

	cout << "modulusobj(3, 5) : ";
	cout << modulusobj(3, 5) << endl;

	cout << "negateobj(3) : ";
	cout << negateobj(3) << endl;

	//以下直接以放函数的临时对象履行函数功能
	//functor<t>() 是一个临时对象，后面再接一对小括号
	//意指调用funtion call operator
	cout << "---------------------------------------" << endl;
	cout << "__plus<int>()(3, 5):";
	cout << __plus<int>()(3, 5)  << endl;

	cout << "__minus<int>()(3, 5) : ";
	cout << __minus<int>()(3, 5) << endl;

	cout << "__multiplies<int>()(3, 5) : ";
	cout << __multiplies<int>()(3, 5) << endl; 

	cout << "__divides<int>()(3, 5) : ";
	cout << __divides<int>()(3, 5) << endl;

	cout << "__modulus<int>()(3, 5) : ";
	cout << __modulus<int>()(3, 5) << endl; 

	cout << "__negate<int>()(3) : ";
	cout << __negate<int>()(3) << endl;

	/*
	 * 仿函数的主要用途是为了搭配STL算法，例如
	 */

	/*
	 * vector iv
	 * accumlate(iv.begin(), iv.end(), 1, __multiplies<int>());
	 */
}
