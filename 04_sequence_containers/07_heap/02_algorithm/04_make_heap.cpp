

/*
 * Date:2021-07-16 17:17
 * filename:04_make_heap.cpp
 *
 */

/*
 * 这个算法用来将一段现有的数据转化为一个heap
 * 其主要依据就是4.7.1complete binary tree的隐式表述(implicit representation)
 *
 */

//将[first, last]排列为一个heap
template <class RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last) {
	__make_heap(first, last, value_type(first), distance_type(first));
}

//以下这组make_heap() 不允许指定"大小比较标准"
template <class RandomAccessIterator, class T, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance *) {
	if (last - first < 2) return;
	Distance len = last - first;
	//找出第一个需要重排的子树头部，以parent标示出。由于任何叶子节点都不需要执行
	//perlocate down, 所以有以下计算。parent 命名不佳，名为holeIndex更好
	Distance parent = (len - 2) / 2;

	while(true) {
		//重排以parent为首的子树,len是为了让__adjust_heap()判断操作范围
		__adjust_heap(first, parent, len, T(*(first + parent)));
		if (parent == 0 ) return ;
		parent--;
	}
}


