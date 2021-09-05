

/*
 * Date:2021-09-05 16:19
 * filename:04_SGI_STL_sort.cpp
 *
 */

//Version 1
//sort()只适用于RandomAccessIterator
template <class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (first != last) {
		__introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
		__final_insertion_sort(first, last);
	}
}

//其中的__lg()用来控制分割恶化的情况

//找出2^k <= n的最大值k
//e.g. n = 7, get n = 20
template <class Size>
inline Size __lg(Size n) {
	Size k;
	for (k = 0; n > 1; n >>= 1) ++k;
	return k;
}

const int __stl_threshold = 16;

//当元素个数为40时，__introsoft_loop()的最后一个参数将是5 * 2,意思是最多允许分割10层
//IntroSort
//Version1
//只适用于RandomAccessIterator
template <class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*, Size depth_limit) {
	//以下,__stl_threshold是个全局常数，稍早定义为const int 16
	while (last - first > __stl_threshold) {
		if (depth_limit == 0) {										//至此分割恶化
			partial_sort(first, last, last);//改用heapsort
			return ;
		}
		--depth_limit;

		//以下是median-of-3 partition 选择一个够好的枢轴并决定分割点
		//分割点将落在迭代器cut身上
		RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first,
						*(first + (last - first) / 2), 
						*(last - 1))));

		//对右半段递归进行sort
		__intosort_loop(cut, last, value_type(first), depth_limit);
		last = cut;
		//现在回到while循环，准备对左半段递归进行sort
		//这种写法可读性较差，效率并没有比较好
	}
}
/*
 * __stl_threshold = 16
 * 通过元素个数检验之后，再检查分割层次。
 * 如果分割层次超过指定值，就改用partial_sort() (以heap sort完成)
 * 都通过这些检验之后，便进入与Quick Sort完全相同的程序
 * 以median-of-3方法确定枢轴位置，然后调用__unguarded_partition()找出分割点，然后针对左右段落递归进行IntroSort
 */

/*
 * 当__introsort_loop()结束，[first, last)内有多个"元素个数少于16"的子序列，
 * 每个子序列都有相当程度的排序，但尚未完全排序(因为元素个数一旦小于__stl_threshold,就被中止进一步的排序操作了)
 * 回到母函数sort(),再进入__final_insertion_sort():
 *
 * Verison 1:
 */
template <class RandomAccessIterator>
	 void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
		 if (last - first > __stl_threshold) { // > 16
			 __insertion_sort(first, first + __stl_threshold);
			 __unguarded_insertion_sort(first + __stl_threshold, last);
		 }
		 else
			 __insertion_sort(first, last);
	 }

/*
 * 此函数首先判断元素个数是否大于16
 * 如果答案为否，就调用__insertion_sort()加以处理
 * 如果是，就将[first, last)分割为长度16的一段子序列，和另一段剩余子序列，再针对两个子序列分别调用
 * __insertion_sort()和__unguarded_insertion_sort()
 *
 */

//Version 1:
template <class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
	__unguarded_insertion_sort_aux(first, last, value_type(first));
}

//Version 1:
template <class RandomAccessIterator, class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
	for (RandomAccessIterator i = first; i != last; ++i) 
		__unguarded_linear_insert(i, T(*i));//
}
