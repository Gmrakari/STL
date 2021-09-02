

/*
 * Date:2021-09-02 21:17
 * filename:01_SGI_STL_Insertion_Sort.cpp
 *
 */

/*
 * Insertion Sort以双层循环的形式进行。
 * 外循环遍历整个序列，每次迭代决定出一个子区间;内循环遍历子区间，将子区间内的每一个"逆序对(iversion)"倒转过来
 * "逆序对"是指任何两个迭代器i,j,i < j 而 *i > *j,一旦不存在"逆序对"，序列即排序完毕
 *
 * 算法复杂度为O(N^2)，数据量很少时，却有不错的效果，原因是实现上有一些技巧,
 * 而且不像其它较为复杂的排序算法有着诸如递归调用等操作带来的额外负荷
 */

/*
 * STL的Insertion Sort有两个版本，版本一使用以渐增方式排序，也就是说以operator<为两个元素的比较函数
 * 版本二允许用户指定一个仿函数(functor),作为两元素的比较函数
 *
 */

//Version 1:
template <class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last) {
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i) 
		__linear_insert(first, i, value_type(first));
	//以上，[first, i)形成一个子区间
}

//版本一 辅助函数
template <class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*) {
	T value = *last;				//记录尾元素
	if (value < *first) {		//尾比头还小
		copy_backward(first, last, last + 1);//将整个区间向右递移一个位置
		*first = value;
	}
	else	//尾不小于头
		__unguarded_linear_insert(last, value);
}

//Version 1 辅助函数
template <class RandomAccessIterator, class T>
void __unguarded_linear_insert(RandomAccessIterator last, T value) {
	RandomAccessIterator next = last;
	--next;

	//insetion sort 的内循环
	while ( value < *next ) {				//逆序对(inversion)存在
		*last = *next;						//调整
		last = next;					//调整迭代器
		--next;				//左移一个位置
	}
	*last = value;		//value的正确落脚处
}
