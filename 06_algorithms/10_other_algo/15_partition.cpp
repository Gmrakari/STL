

/*
 * Date:2021-08-21 17:14
 * filename:15_partition.cpp
 *
 */

/*
 * partition会将区间[first, last)中的元素重新排列。
 * 所有被一元条件运算pred判定为true的元素，都会被放在区间的前段，被判定为false的元素，
 * 都会被放在区间的后段。这个算法不保证保留元素的原始相对位置。
 * 如果需要保留原始相对位置，应使用stable_partition
 *
 */

/*
 * 所有被pred判定为true的元素，都被放到前段
 * 被pred判定为false的元素，都被放到后段
 * not stable
 */
template <class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred) {
	while (true) {
		while (true)
			if (first == last)						//头指针等于尾指针
				return first;								//所有操作结束
			else if (pred(*first))				//头指针所指的元素符合不移动条件
				++first;										//不移动，头指针向前移动1
			else													//跳出循环
				break;
		--last;													//尾指针回溯1
		while (true)										
			if (first == last)						//头指针等于尾指针
				return first;								//所有操作结束
			else if (!pred(*last))				//尾值针所指向的元素符合不移动条件
				--last;											//不移动，尾指针回溯1
			else													//跳出循环
				break;
		iter_swap(first, last);					//头尾指针所指元素彼此交换
		++first;												//头指针前进1,准备下一个外循环迭代
	}
}
