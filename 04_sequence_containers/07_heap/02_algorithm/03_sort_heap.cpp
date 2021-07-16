

/*
 * Date:2021-07-16 16:58
 * filename:03_sort_heap.cpp
 *
 */

/*
 * 每次pop_heap可获得heap中键值最大的元素,如果持续对整个heap做pop_heap操作,每次将操作范围从后向前缩减一个元素
 * (因为pop_heap会把键值最大的元素放在底部容器的最尾端),当整个程序执行完毕时，我们便有了一个递增序列
 */

template <class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
	//每执行一次pop_heap(),极致(STL heap中为极大值)即被放在尾端
	//扣除尾端再执行一次pop_heap(),次极值又被放在新尾端。
	//一直下去，最后即得排序结果
	while (last - first > 1)
		pop_heap(first, last--);
}

/* 不断对heap进行pop操作,便可达到排序效果 */

