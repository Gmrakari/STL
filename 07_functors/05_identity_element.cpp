

/*
 * Date:2021-09-08 21:28
 * filename:05_identity_element.cpp
 *
 */

/*
 * 证同元素(identiy element)
 * 所谓"运算op的证同元素(identity element)"意思是数值A若与该元素做op运算，会得到A自己
 * 加法的证同元素为0,因为任何元素加上0仍为自己
 * 乘法的证同元素为1,一inwei任何元素乘以1仍为自己
 *
 */

template <class T>
inline T identity_element(plus<T>) {
	return T(0);
}

template <class T>
inline T identity_element(multiplies<T>) {
	return T(1);
}

//见<stl_numerics.h>的power()
