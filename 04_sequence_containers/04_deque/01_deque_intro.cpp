

/*
 * Date:2021-06-02 15:14
 * filename:01_deque_intro.cpp
 *
 */

/*
 * vector 是单向开口的连续性空间
 * deque 则是一种双向开口的连续线性空间
 * 所谓双向开口，意思是可以在头尾两端分别做元素的插入和删除操作
 * vector 当然也可以在头尾两端进行操作,但是其头部操作效率奇差，无法被接受
 *
 * deque和vector的最大差异，
 * 一是在于deque允许于常数时间内对起头端进行元素的插入或移除操作
 * 二是在于deque没有所谓的容量(capacity)观念，因为它是动态地以分段连续空间组合而成
 * 随时可以增加一段新的空间并链接起来。
 *
 * 像vector那样"因旧空间不足而重新配置一块更大空间，然后复制元素，再释放旧空间"
 * 这样的事情在deque是不会发送的，也因此,deque没有必要提供所谓的空间保留(reserve)功能
 *
 * 虽然deque也提供Ramdon Access Iterator,但它的迭代器并不是普通指针，其复杂度
 * 和vector不可以道里计，也当然也影响了各个运算层面
 *
 * 因此 要尽可能选用vector,而非deque
 * 对deque进行的排序操作，为了最高效率，可将deque先完整复制到一个vector身上,
 * 将vector排序后(利用STLsort算法)，再复制回deque。
 *
 */

/*
 * vector 三步:
 * 1-另觅更大空间
 * 2-将原数据复制过去
 * 3-释放原空间
 *
 * deque系由一段一段的定量连续空间构成,一定那有必要在deque的前端或尾端增加新空间，
 * 便配置一段定量连续空间，串接在整个deque的头端或尾端
 * deque的最大任务,便是在这些分段的定量连续空间上,维护其整体连续的假象,
 * 并提供随机存取的接口。避开了"重新配置,复制，释放"的轮回，代价则是复杂的迭代器架构
 *
 * deuqe采用一块所谓的map(不是STL的map容器)作为主控
 * 这里所谓map是一小块连续空间,其中每个元素(此处称为一个节点,node)都是指针,指向另一段
 * (较大的)连续性空间,称为缓冲区。缓冲区才是deque的储存空间主体。
 *
 */
template<class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
	typedef T value_type;						//Basic types
	typedef value_type* pointer;
	...
protected:												// Internal typedefs
		//元素的指针的指针
		typedef pointer* map_pointer;

protected:
		map_pointer map;							//指向map,map是块连续空间，其内的每个元素都是一个指针(称为节点),指向一块缓冲区
		size_type map_size;						//map可容纳多少指针
};

