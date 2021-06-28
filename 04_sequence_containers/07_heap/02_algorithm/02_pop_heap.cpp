

/*
 * Date:2021-06-28 18:20
 * filename:02_pop_heap.cpp
 *
 */

/*
 * 既然身为max-heap，最大值必然在根节点
 * pop操作取走根节点(其实是设至底部容器vector的尾端节点)后，为了满足complete binary tree的条件
 * 必须割舍最下层右边的叶节点，并将其值重新安插至max-heap(因此有必要重新调整heap结构)
 *
 * 为了满足max-heap次序特性(每个节点的键值都大于或等于其子节点键值),我们执行所谓的percolate down(下溯)程序:
 * 将空间节点和其较大子节点"对调",并持续下放,直至叶节点为止。然后将前述被割舍之元素值设给这个"已到达叶层的空洞节点",
 * 再对它执行一次percolate up(上溯)程序,这便大功告成
 *
 * 下面是pop_heap算法的实现细节
 * 该函数接受两个迭代器，用来表现一个heap底部容器(vector)的头尾。如果不符合这个条件，pop_heap的执行结果未可预期
 *
 */

template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
	__pop_heap_aux(first, last, value_type(first));
}

template<class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*) {
	__pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
	//以上，根据implicit representation heap的次序特性,pop操作的结果应为底部容器的第一个元素
	//因此，首先设定欲调整值为尾值，然后将首值调至尾节点(所以以上迭代其result设为last - 1)。
	//然后重整[first, last - 1],使之重新成一个合格的heap
}

//以下这组__pop_heap() 不允许指定"大小比较标准"
template<class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator result, T value, Distance *) {
	*result = *first;//设定尾值为首值,于是尾值即为欲求结果，可由客户端稍后再以底层容器之pop_back()取出尾值
	__adjust_heap(first, Distance(0), Distance(last - first), value);
	//以上欲重新调整heap,洞号为0(亦即树根处),欲调整值为value(原尾值)
}

//以下这组__adjust_heap() 不允许指定"大小比较标准"
template<class RandomAccessIterator, class Distance, class T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value) {
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * holeIndex + 2; //洞结点之右子节点
	while (secondChild < len) {
		//比较洞节点之左右两个子值,然后以secondChild代表较大子节点
		if ( *(first + secondChild) < *(first + (secondChild - 1)) )
			secondChild--;
		//Percolate down:令较大子值为洞值，再令洞号下移至较大子节点处
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		//找出新洞节点的右子节点
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len) {
		*(first + holeIndex) = *(first = (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	//此时(可能)尚未满足次序特性。执行一次percolate up操作
	//reader report:不可如此,试套4.7.4 jjhou 测试的确不行
	__push_heap(first, holeIndex, topIndex, value);
}

/*
 * 注意,pop_heap之后，最大元素只是被至放于容器的最为端，尚未被取走。
 * 如果要取其值，可使用底部容器(vector)所提供的back()操作函数
 * 如果要移除它，可使用底部容器(vector)所提供的pop_back()操作函数
 */

