

/*
 * Date:2021-06-28 16:37
 * filename:01_push_heap.cpp
 *
 */

/*
 * 新元素是否合适于现有位置呢?
 * 为满足max-heap的条件(每个节点的键值都大于或等于其子节点键值)，我们执行一个所谓的percolate up(上溯)程序:
 * 将新节点拿来与其父结点比较，如果其键值(key)比父结点大，就父子对换位置。
 * 如此一直上溯，直到不需对换或直接根节点为止
 *
 * 下面是push_heap算法的实现细节，该函数接受两个迭代器,用来表现一个heap底部容器(vector)的头尾
 * 并且新元素已经插入到底部容器的最尾端
 *
 * 如果不符合这两个条件，push_heap的执行结果未可预期
 *
 */

template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
	//注意，此函数被调用时，新元素已置于底部容器的最尾端
	__push_heap_aux(first, last, distance_type(first), value_type(first));
}

template<class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*) {
	__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));

	//以上系根据implicit representation heap的结构特性:新值必置于底部
	//容器的最尾端,此即第一个洞号(last - first) -  1
}

//以下这组push_back() 不允许指定"大小比较标准"
template<class RandomAccessIterator, class Distance, class T>
void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value) {
	Distance parent = (holeIndex - 1) / 2;//找出父节点
	while (holeIndex > topIndex && *(first + parent) < value) {
		//当尚未达到顶端,且父结点小于新值(于是不符合heap的次序特性)
		////由于以上使用operator<,可知STL heap是一种max-heap(大者为父)
		*(first + holeIndex) = *(first + parent);//令洞值为父值
		holeIndex = parent;										//percolate up:调整洞号，向上提升至父结点
		parent = (holeIndex - 1) / 2;					//新洞的父结点
	}	//持续至顶端，或满足heap的次序特性为止
	*(first + holeIndex) = value;	//令洞值为新值，完成插入操作
}
