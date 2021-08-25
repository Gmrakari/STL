

/*
 * Date:2021-08-25 16:33
 * filename:29_search_n.cpp
 *
 */

/*
 * 在序列[first, last)所涵盖的区间中，查找"连续count个符合条件之元素"所形成的子序列，
 * 并返回一个迭代器指向该子序列起始处。如果找不到这样的子序列，就返回迭代器last。
 * 上述所谓的"某条件"，在search_n版本一指的是相等条件"equality"，在search_n版本二指的是用户
 * 指定的某个二元运算(以仿函数呈现)
 */

//查找"连续两个8"所形成的子序列起点
//iter1 = search_n(iv.begin(), iv.end(), 2, 8);

//serach_n源码
//版本一
//查找"元素value连续出现count次"所形成的那个子序列，返回其发生位置
template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value) {
	if (count <= 0)
		return first;
	else {
		first = find(first, last, value);	//首先找出value第一出现点
		while (first != last) {						//继续查找余下元素
			Integer n = count - 1;					//value还应出现n次
			ForwardIterator i = first;			//从上次出现点接下去查找
			++i;
			while (i != last && n != 0 && *i == value) {
				//下个元素是value
				++i;
				--n;												//既然找到了,"value应再出现次数"便可减1
			}															//回到内循环内继续查找
			if (n == 0)										//n == 0表示确实找到了 "元素值出现n次"的子序列
				return first;
			else
				first = find(i, last, value);		//找value的下一个出现点，并准备回到外循环
		}
		return last;
	}
}

//版本二
//查找 "连续count个元素皆满足指定条件"所形成的那个子序列的起点，返回其发生位置
template <class ForwardIterator, class Integer, class T, class BinaayPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Integer count, const T& value,
		BinaayPredicate binary_pred) {
	if (count <= 0) return first;
	else {
		while (first != last) {
			if (binary_pred(*first, value)) break;	//首先找出第一个符合条件的元素
			++first;																//找到就离开
		}
		while (first != last) {									//继续查找余下元素
			Integer n = count - 1;								//还应有n个连续元素符合条件
			ForwardIterator i = first;					//从上次出现点接下去查找
			++i;
			//以下循环确定接下来count - 1个元素是否都符合条件
			while (i != last && n != 0 && binary_pred(*i, value)) {
				++i;
				--n;				//既然这个元素符合条件，"应符合条件的元素个数"便可减1
			}
			if (n == 0) //n == 0表示确实找到了count个符合条件的元素
				return first;
			else {
				while (i != last) {
					if (BinaayPredicate(*i, value)) break;	//查找下一个符合条件的元素
					++i;
				}
				first = i;			//准备回到外循环
			}
		}
		return last;
	}
}
