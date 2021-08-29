

/*
 * Date:2021-08-29 11:42
 * filename:05_next_permutation.cpp
 *
 */

/*
 * STL提供了两个用来计算排列组合关系的算法，分别是next_permucation和prev_prermutation
 * "下一个排列组合"，什么是"前一个"排列组合。考虑三个字符所组成的序列{a, b, c}
 * 有{abc, acb, bac, bca, cab, cba},这些排列组合根据less-than操作符做字典顺序(lexicographical)的排序。
 * 也就是说,abc名列第一，因为每个元素都小于其后的元素。acb是次一个序列，因为它固定了a(序列内最小元素)
 * 之后所做的新组合。
 * 同样道理，那些固定b(序列内次小元素)而做的排列组合，在次序上将先于那些固定c而做的排列组合。
 * 以bac和bca为例，bac在bca之前，因为序列ac小于序列ca。
 *
 * 重点:
 * 面对bca,我们可以说前一个排列组合是bac,而其后一个排列组合是cab
 * 序列abc没有"前一个"排列组合，cba没有"后一个"排列组合
 *
 */

/*
 * next_permutation()会取得[first, last)所标示之序列的下一个序列组合。如果没有下一个排列组合，便返回false;否则返回true
 *
 */

/*
 * 版本一用less-than,版本二用comp
 */

/*
 * 实现过程:
 * 首先，从最尾端开始往前寻找两个相邻元素，令第一元素为*i,第二元素为**i,且满足*i < **i
 * 找到这样一组相邻元素后，再从最尾端开始往前检验，找出第一个大于*i的元素，令为*j,将i,j元素对调，
 * 再将ii之后的元素颠倒排列。此即所求之"下一个"排列组合。
 *
 * 比如,{0,1,2,3,4},*i = 3, *ii = 4; 
 */

//version 1:
template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
	if (first == last) return false;//空区间
	BidirectionalIterator i = first;
	++i;

	if (i == last) return false;
	i = last;										//i 指向尾端
	--i;

	for (;;) {
		BidirectionalIterator ii = i;
		--i;
		//以上，锁定一组(两个)相邻元素
		if (*i < *ii) {								//如果前一个元素小于后一个元素
			BidirectionalIterator j = last;		//令j指向尾端
			while (!(*i < *--j));					//由尾端往前找，直到遇上比*i大的元素
			iter_swap(i, j);
			reverse(ii, last);			//将ii之后的元素全部逆向重排
			return true;
		}
		if (i == first) {					//进行至最前面了
			reverse(first, last);		//全部逆向重排
			return false;
		}
	}
}
