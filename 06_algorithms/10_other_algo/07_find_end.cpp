

/*
 * Date:2021-08-20 16:21
 * filename:07_find_end.cpp
 *
 */

/*
 * 在序列一[first, last1)所涵盖的区间中，查找序列二[first2, last2)的最后一次出现点。
 * 如果序列一之内不存在"完全匹配序列二"的子序列，便返回迭代器last1
 * 版本一使用元素型别提供的equality操作符，
 * 版本二允许用户指定某个二元运算(以仿函数呈现)，作为判断元素相等与否的依据
 */

/*
 * 由于这个算法查找的是"最后一次出现地点"，如果我们有能力逆向查找，题目就变成了"首次出现地点"
 * 逆向查找的关键在于迭代器的双向移动能力，因此，SGI将算法设计为双层架构，一般称呼此种上层
 * 函数为dispatch function(分派函数、派送函数):
 *
 */

//version:1
template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2) {
	typedef typename iterator_traits<ForwardIterator1>::iterator_category category1;
	typedef typename iterator_traits<ForwardIterator2>::iterator_category category2;

	//以下根据两个区间的类属，调用不同的下层函数
	return __find_end(first1, last1, first2, last2, category1(), category2());
}

/*
 * 这是一种常见的技巧，令函数传递调用过程中产生迭代器类型(iterator category)的临时对象
 * 再利用编译器的参数推导机制(argument deduction),自动调用某个对应函数
 *
 */

//forward iterators
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1,
		ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag) {
	if (first2 == last2) //如果查找目标为空
		return last1;	//返回last1,表示该"空子序列"的最后出现点
	else {
		ForwardIterator1 result = last1;
		while (1) {
			//以下利用search()查找某个子序列的首次出现点。找不到的话返回last1
			ForwardIterator1 new_result = search(first1, last1, first2, last2);
			if (new_result == last1)	//Not found
				return result;
			else {
				result = new_result;//调动一下标兵，准备下一个查找行动
				first1 = new_result;
				++first1;
			}
		}
	}
}

//bidirectional iterators(可以逆向查找)
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
		BidirectionalIterator2 first2, BidirectionalIterator2 last2,
		bidirectional_iterator_tag, bidirectional_iterator_tag) {
	//由于查找的是"最后出现地点"，因此反向查找比较快。利用reverse_iterator.
	typedef reverse_iterator<BidirectionalIterator1> reviter1;
	typedef reverse_iterator<BidirectionalIterator2> reviter2;

	reviter1 rlast1(first1);
	reviter2 rlast2(first2);

	//查找时，将序列一和序列二统统逆转方向
	reviter1 rresult = search(reviter1(last1), rlast1, reviter2(last2), rlast2);

	if (rresult == rlast1) // Not found
		return last1;
	else {//找到了
		BidirectionalIterator1 result = rresult.base();//转回正常(非逆向)迭代器
		advance(result, -distance(first2, last2));//调整回到子序列的起头处
		return result;
	}
}


