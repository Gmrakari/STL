

/*
 * Date:2021-08-17 17:14
 * filename:06_numeric_中的power.cpp
 *
 */

/*
 * 由SGI专属，并不在STL标准之列
 */

template <class T, class Integer>
inline T power(T x, Integer n) {
	return power(x, n, multiplies<T>());//指定运算型式为乘法
}

//版本2,如果指定为乘法运算，则当n >= 0时返回 x^n
template <class T, class Integer, class MonoidOperation>
T power(T x, Integer n, MonoidOperation op) {
	if (n == 0) 
		return identity_element(op);
	else {
		while ((n & 1) == 0) {
			n >>= 1;
			x = op(x, x);
		}
		T result = x;
		n >>= 1;
		while (n != 0) {
			x = op(x, x);
			if ((n & 1) != 0)
				result = op(result, x);
			n >>= 1;
		}
		return result;
	}
}
