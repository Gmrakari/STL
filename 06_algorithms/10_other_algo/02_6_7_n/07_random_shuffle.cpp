

/*
 * Date:2021-08-29 14:35
 * filename:07_random_shuffle.cpp
 *
 */

/*
 * 将[first, last)的元素次序随机重排。也就是说，在N!种可能的元素排列顺序中随机选出一种，此处N为last-first.
 * 
 * N个元素的序列，其排列方式有N!种，random_shuffle会产生一个均匀分布，因此任何一个排列被选中的机率为1/N!
 *
 * random_shuffle有两个版本，差别在于随机数的取得，版本1使用内部随机数产生器，版本2使用一个会产生随机随机数的仿函数。
 * 特别注意，该仿函数的传递方式是by reference而非一般的by value,这是因为随机随机数产生器有一个重要性质:
 * 它拥有局部状态(local state)，每次被调用时都会有所改变，并因此保障产生出来的随机数能够随机
 *
 */

//SGI Version 1
template <class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
	__random_shuffle(first, last, distance_type(first));
}

template <class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance *) {
	if (first == last) return ;
	for (RandomAccessIterator i = first + 1; i != last; ++i)
#ifdef __STL_NO_DRAND48
		iter_swap(i, first + Distance(rand() % ((i - first) + 1)));
#else
	iter_swap(i, first + Distance(lrand48() % ((i - first) + 1)));
#endif

}

//STG Version 2
template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& rand) {
	//by reference
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i) 
		iter_swap(i, first + rand((i - first) + 1));
}
