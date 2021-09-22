

/*
 * Date:2021-09-22 20:59
 * filename:07_用于函数指针_ptr_fun.cpp
 *
 */

/*
 * 这种配接器使我们能够将一般函数当作仿函数使用。
 * 一般函数当作仿函数传给STL算法，就语言层面本来就是可以的，就好像原生指针可被当作迭代器传给STL算法样
 * 但如果你不使用这里所说的两个配接器先做一番包装，你所使用的那个一般函数将无陪接能力，也就无法和前
 * 数小节介绍过的其它配接器接轨
 *
 */

//以下配接器其实就是把一个一元函数指针包起来
//当仿函数被使用时，就调用该函数指针
template <class Arg, class Result>
class pointer_to_unary_function : public unary_function<Arg, Result> {

protected:
	Result (*ptr)(Arg);
public:
	pointer_to_unary_function() {}
	//以下 constructor将函数指针记录于内部成员之中
	explicit pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) {}

	//以下，通过函数指针执行函数
	Result operator()(Arg x) const { return ptr(x); }
};

//辅助函数，让我们得以方便运用pointer_to_unary_function
template <class Arg, class Result>
inline pointer_to_unary_function<Arg, Result>
ptr_fun(Result (*x)(Arg)) {
	return pointer_to_unary_function<Arg, Result>(x);
}

//以下配接器其实就是把一个二元函数指针包起来
//当仿函数被使用时，就调用该函数指针
template <class Arg1, class Arg2, class Result>
class pointer_to_unary_function
: public binary_function<Arg1, Arg2, Result> {

protected:
	Result (*ptr)(Arg1, Arg2);

public:
	pointer_to_unary_function() {}
	//以下 constructor将函数指针记录于内部成员之中
	explicit pointer_to_unary_function(Result (*x)(Arg1, Arg2)) : ptr(x) {}

	//以下，通过函数指针执行函数
	Result operator()(Arg1 x, Arg2 y) const {
		return ptr(x, y);
	}
};

//辅助函数，让我们得以方便使用pointer_to_binary_function
template <class Arg1, class Arg2, class Result>
inline pointer_to_unary_function<Arg1, Arg2, Result>
ptr_fun(Reuslt (*x)(Arg1, Arg2)) {
	return pointer_to_unary_function<Arg1, Arg2, Result>(x);
}
