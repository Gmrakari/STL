

/*
 * Date:2021-08-17 16:00
 * filename:04_numeric_中的inner_product.cpp
 *
 */

//版本1
template <class InputIterator1, class InputIterator2, class T>
T inner_product(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, T init) {
	//以第一序列之元素个数为据，将两个序列都走一遍
	for (; first1 != last1; ++first1, ++ first2)
		init = init + (*first1 * *first2);//执行两个序列的一般内积
	return init;
}

//版本2
template <class InputIterator1, class InputIterator2, class T,
				 class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1,
						 InputIterator2 first2, T init, BinaryOperation1 binary_op1,
						 BinaryOperation2 binary_op2) {
	//以第一序列之元素个数为据，将两个序列都走一遍
	for (; first1 != last1; ++first1, ++first2)
		//以外界提供的仿函数来取代第一版本中的operator* 和 operator+
		init = binary_op1(init, binary_op2(*first1, *first2));
	return init;
}

/*
 * inner_product能够计算[first1, last1)和[first2, first2 + (last1 - first1))的一般内积(generalized inner product)
 * 你一定得提供初值init
 * 当[first, last)为空时，仍可获得一个明确定义的结果
 *
 * 版本1
 * result = result + (*i) * *(first2 + (i - first1));
 *
 * 第二版本与第一版本的唯一差异是以外界提供之仿函数来取代operator+和operator*
 * 也就是说，首先将结果初始化为init,然后针对[first1, last1)的每一个迭代器i,
 * 由头至尾依序执行result = binary_op1(result, binary_op2(*i, *(first2 + (i - first1))))
 *
 */
