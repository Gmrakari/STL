

/*
 * Date:2021-08-25 15:48
 * filename:26_rotate.cpp
 *
 */

/*
 * 将[first, middle)内的元素和[middle, last)内的元素互换。middle所指的元素会成为容器的一个元素
 * 如果有个数字序列{1,2,3,4,5,6,7} 对元素3做旋转操作，会形成{3,4,5,6,7,1,2}
 * rotate()可以交换两个长度不同的区间
 *
 * 迭代器的双向或随机定位能力，影响了这个算法的效率，所以设计为双层架构
 */

//分派函数(dispatch function)
template <class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last) {
	if (first == middle || middle == last) return ;
	__rotate(first, middle, last, distance_type(first), iterator_category(first));
}

//下面是根据不同的迭代器类型而完成的三个旋转操作
//rotate的forward iterator_category版
template <class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag){
	for (ForwardIterator i = middle; ;) {
		iter_swap(first, i);			//前段、后段的元素一一交换
		++first;									//双双前进1
		++i;

		//以下判断是前段[first, middle)先结束还是后段[middle, last)先结束
		if (first == middle) {				//前段结束了
			if (i == last) return;			//如果后段同时也结束了，整个就结束了
			middle = i;									//否则调整，对新的前、后段再作交换
		}
		else if (i == last)			//后段先结束
			i = middle;				//调整，准备对新的前、后段再作交换
	}
}

//rotate 的bidirectional iterator版
template <class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last,
		Distance*, bidirectional_iterator_tag) {
	reverse(first, middle);
	reverse(middle, last);
	reverse(first, last);
}

//rotate 的random access iterator版
template <class RandomAccessIterator, class Distance>
void __rotate(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last,
		Distance *, random_access_iterator_tag) {
	//以下迭代器的相减操作，只适用于random access iterators
	//取全长和前段长度的最大公因子
	Distance n = __gcd(last - first, middle - first);
	while (n--) 
		__rotate_cycle(first, last, first + n, middle - first, value_type(first));
}

//最大公因子，利用辗转相除法
//__gcd() 应用于__rotate()的random access iterator版
template <class EuclideanRingElement>
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n) {
	while (n != 0) {
		EuclideanRingElement t = m % n;
		m = n;
		n = t;
	}
	return m;
}

template <class RandomAccessIterator, class Distance, class T>
void __rotate_cycle(RandomAccessIterator first, RandomAccessIterator last,
		RandomAccessIterator initial, Distance shift, T*) {
	T value = *initial;
	RandomAccessIterator ptr1 = initial;
	RandomAccessIterator ptr2 = ptr1 + shift;
	while (ptr2 != initial) {
		*ptr1 = *ptr2;
		ptr1 = ptr2;
		if (last - ptr2 > shift)
			ptr2 += shift;
		else
			ptr2 = first + (shift - (last - ptr2));
	}
	*ptr1 = value;
}


