

/*
 * Date:2021-09-16 11:15
 * filename:04_对返回值进行逻辑否定_not1_not2.cpp
 *
 */

/*
 * 源代码中出现的pred一词，是predicate的缩写，意指会返回真假值(bool)的表达式
 *
 */
//以下配接器用来表示某个Adaptable Predicate的逻辑负值(logical negation)
template <class Predicate>
class unary_negate
: public unary_function<typename Predicate::argument_type, bool> {
protected:
	Predicate pred;//内部成员
public:
	explicit unary_negate(const Predicate& x) : pred(x) {}
	bool operator()(const typename Predicate::argument_type& x) const {
		return !pred(x);//将pred的运算结果加上否定(negate)运算
	}
};

//辅助函数，使我们得以方便使用unary_negate<Pred>
template <class Predicate>
inline unary_negate<Predicate> not1(const Predicate& pred) {
	return unary_negate<Predicate>(pred);
}

//------------------------------------------------------------------------
//以下配接器 用来表示某个Adaptable Binary Predicate的逻辑父值
template <class Predicate>
class binary_negate
	: public binary_negate<typename Predicate::first_argument_type,
	typename Predicate::second_argument_type,
	bool> {
protected:
	Predicate pred;
public:
	explicit binary_negate(const Predicate& x) : pred(x) {}
	bool operator()(const typename Predicate::first_argument_type& x,
			const Predicate::second_argument_type& y) const {
		return !pred(x, y);
	}
};

//辅助函数,使得我们方便使用binary_negate
template <class Predicate>
inline binary_negate<Predicate> not2(const Predicate& pred) {
	return binary_negate<Predicate>(pred);
}
