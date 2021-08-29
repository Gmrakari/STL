

/*
 * Date:2021-08-29 14:27
 * filename:06_prev_permutation.cpp
 *
 */

/*
 * "前一个"排列组合。
 * 具体做法:
 * 首先，从最尾端开始往前寻找两个相邻元素，令第一元素为*i,第二元素为*ii,且满足*i > *ii。
 * 找到这样一组相邻元素后，再从最尾端开始往前检验，找出第一个小于*i元素，令为*j,将i,j元素对调，
 * 再将ii之后的所有元素颠倒排列。
 *
 */

//Version 1
template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
	if (first == last) return false;		//空区间
	BidirectionalIterator i = first;
	++i;
	if (i == last) return false;
	i = last;
	--i;

	for (;;) {
		BidirectionalIterator ii = i;
		--i;

		//以上，锁定一组(两个)相邻元素
		if (*ii < *i) { //如果前一个元素大于后一个元素
			BidirectionalIterator j = last;				//令j指向尾端
			while (!(*--j < *i));			//由尾端往前找，直到遇上比*i小的元素
			iter_swap(i, j);				//交换i, j
			reverse(ii, last);			//将ii之后的元素全部逆向重排	
			return true;
		}
		if (i == first) {					//进行至最前排
			reverse(first, last);		//全部逆向重排 ??
			return false;
		}
	}
}
