

/*
 * Date:2021-08-28 09:38
 * filename:32_unique.cpp
 *
 */

/*
 * 算法unique能够移除(remove)重复的元素。每当在[first, last]内遇有重复元素群，它便移除该元素群中第一个
 * 以后的所有元素。注意，unique之移除相邻的重复元素，如果你想要移除所有(包括不相邻的)重复元素，必须先将
 * 序列排序，使所有重复元素都相邻。
 *
 * unique会返回一个迭代器指向新区间的尾端，新区间之内不含相邻的重复元素。
 * 这个算法是稳定的,亦即所有保留下来的元素，其原始相对次序不变。
 * 
 * 事实上unique并不会改变[first, last)的元素个数，有一些残余数据会留下来
 *
 * unique有两个版本
 * 第一版本使用简单的相等(equality)测试，第二版本使用一个Binary Predicate binary_pred做为测试准则。
 * 其中所有操作其实是借助unique_copy完成
 */

//Version 1:
template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
	first = adjacent_find(first, last);					//首先找到相邻重复元素的起点
	return unique_copy(first, last, first);			//利用unique_copy完成
}

/*
 * unique_copy
 * 
 * 算法unique_copy可从[first, last)中将元素复制到以result开头的区间上;
 * 如果面对相邻重复元素群，只会复制其中第一个元素。返回的迭代器指向以result开头的区间的尾端
 *
 * 与其它名为*_copy的算法一样，unique_copy乃是unique的一个复制式版本，所以它的特性与unique完成相同
 * 只不过是将结果输出到另一个区间而已
 *
 */

//Verison 1
template <class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result) {
	if (first == last) return result;
	//以下,根据result的iterator category,做不同的处理
	return __unique_copy(first, last, result, iterator_category(result));
}

//版本一辅助函数,forward_iterator_tag版
template <class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last, ForwardIterator result, forward_iterator_tag) {
	*result = *first;//记录第一个元素
	while (++first != last)		//遍历整个区间
		//以下，元素不同，就记录，否则(元素相同)，就跳过
		if (*result != *first) *++result = *first;
	return ++result;
}

//版本一辅助函数,output_iterator_tag版
template <class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, output_iterator_tag) {
	//以下，output iterator有一些功能限制，所以必须先知道其value type
	return __unique_copy(first, last, result, value_type(first));
}

//由于output iterator为write only,无法像forward iterator 那般可以读取
//所以不能有类似 *result != *first这样的判断操作，所以才需要设计这一版本
//例如ostream_iterator就是一个output iterator
template <class InputIterator, class OutputIterator, class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
	//T为output iterator的value type
	T value = *first;
	*result = value;
	while (++first != last) 
		if (value != *first) {
			value = *first;
			*++result = value;
		}
	return ++result;
}

