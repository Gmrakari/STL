

/*
 * Date:2021-09-23 10:03
 * filename:09_adapter_function_objects_pointers_to_member_functions.cpp
 *
 */

//这个族群一共有8 = 2^3个function objects
//1、"无任何参数" vs "有一个参数"
//2、"通过pointer调用" vs "通过reference调用"
//3、"const成员函数" vs "non-const成员函数"

//所有的复杂都只存在于function objects内部，你可以忽略它们，直接使用
//更上层的辅助函数mem_fun和mem_fun_ref,它们会产生适当的配接器

// "无任何参数" "通过pointer调用" "non-const成员函数"
template <class S, class T>
class mem_fun_t : public unary_function<T*, S> {
public:
	explicit mem_fun_t(S (T::*pf)()) : f(pf) {} //记录下来
	S operator()(T* p) const { return (p->*f)(); }	//转调用
private:
	S (T::*f)();		//内部成员，pointer to member function
};

// "无任何参数" "通过pointer调用" "const成员函数"
template <class S, class T>
class const_mem_fun_t : public unary_function<const T* ,S> {
public:
	explicit const_mem_fun_t(S (T::*pf)() const) : f(pf) {}
	S operator()(const T* p) const { return (p->*f)(); }

private:
	S (T::*f)() const;//内部成员，pointer to const member function
};

// "无任何参数" "通过reference调用" "non-const成员函数"
template <class S, class T>
class mem_fun_ref_t : public unary_function<T, S> {
public:
	explicit mem_fun_ref_t(S (T::*pf)()) : f(pf) {}	//记录下来
	S operator()(T& r) const { return (r.*f)(); }
private:
	S (T::*f)();		//内部成员，pointer to member function
};

// "无任何参数" "通过reference调用" "const成员函数"
template <class S, class T>
class const_mem_fun_ref_t : public unary_function<T, S> {
public:
	explicit const_mem_fun_ref_t(S (T::*pf)() const ) : f(pf) {}	//记录下来
	S operator()(const T& r) const { return (r.*f)(); }	//转调用
private:
	S (T::*f)() const;	//内部成员，pointer to member funciton
};

//"有一个参数" "通过pointer调用" "non-const成员函数"
template <class S, class T, class A>
class mem_fun1_t : public binary_function<T*, A, S> {
public:
	explicit mem_fun1_t(S (T::*pf)(A)) : f(pf) {}					//记录下来
	S operator()(T* p, A x) const { return (p->*f)(x); }	//转调用

private:
	S (T::*f)(A);				//内部成员,pointer to member function
};

//"有一个参数" "通过pointer调用" "const成员函数"
template <class S, class T, class A>
class const_mem_fun1_t : public binary_function<T*, A, S> {
public:
	explicit const_mem_fun1_t(S (T::*pf)(A) const) : f(pf) {}
	S operator()(T* p, A x) const { return (p->*f)(x); }
private:
	S (T::*f)(A) const;
};

//"有一个参数" "通过reference调用" "non-const成员函数"
template <class S, class T, class A>
class mem_fun1_ref_t : public binary_function<T, A, S> {
public:
	explicit mem_fun1_ref_t(S (T::*pf)(A)) : f(pf) {}	//记录下来
	S operator()(T& r, A x) const { return (r.*f)(x); }	//转调用
private:
	S (T::*f)(A);
};

//"有一个参数" "通过reference调用" "const成员函数"
template <class S, class T, class A>
class const_mem_fun1_ref_t : public binary_function<T, A, S> {
public:
	explicit const_mem_fun1_ref_t(S (T::*pf)(A) const) : f(pf) {}
	S operator()(T& r, A x) const { return (r.*f)(x); }
private:
	S (T::*f)(A) const;
};	

//mem_fun adapter的辅助函数:mem_fun mem_fun_ref
template <class S, class T>
inline mem_fun_t<S, T> mem_fun(S (T::*f)()) {
	return mem_fun_t<S,T>(f);
}

template <class S, class T>
inline const_mem_fun_t<S, T> mem_fun(S (T::*f)() const) {
	return const_mem_fun_t<S, T>(f);
}

template <class S, class T>
inline mem_fun_ref_t<S, T> mem_fun_ref(S (T::*f)()) {
	return mem_fun_ref_t<S, T>(f);
}

template <class S, class T>
inline const_mem_fun_ref_t<S, T> mem_fun_ref(S (T::*f)() const) {
	return const_mem_fun_ref_t<S, T>(f);
}

//注意，以下四个函数，其实可以采用和先前(以上)四个函数相同的名称(函数重载）
//把mem_fun1()改为mem_fun()，把mem_fun1_ref()改为mem_fun_ref()
//即可符合C++ Standard SGI STL 3.3就是这么做的

template <class S, class T, class A>
inline mem_fun1_t<S, T, A> mem_fun1(S (T::*f)(A)) {
	return mem_fun1_t<S,T,A>(f);
}

template <class S, class T, class A>
inline const_mem_fun1_t<S, T, A> mem_fun1(S (T::*f)(A) const) {
	return const_mem_fun1_t<S, T, A>(f);
}

template <class S, class T, class A>
inline mem_fun1_ref_t<S, T, A> mem_fun1_ref(S (T::*f)(A)) {
	return mem_fun1_ref_t<S, T, A>(f);
}

template <class S, class T, class A>
inline const_mem_fun1_ref_t<S, T, A> mem_fun1_ref(S (T::*f)(A) const) {
	return const_mem_fun1_ref_t<S, T, A>(f);
}
