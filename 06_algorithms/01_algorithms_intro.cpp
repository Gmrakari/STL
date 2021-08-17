

/*
 * Date:2021-08-17 09:25
 * filename:01_algorithms_intro.cpp
 *
 */

/*
 * STL的70余个算法，包括排序(sorting),查找(searching),排列组合(permutation)
 * 以及用于数据移动、复制、删除、比较、组合、运算等
 *
 * binary search tree(二叉查找树)和RB-tree(红黑树)便是为了解决查找问题而发展出来的特殊数据结构
 * hashtable(散列表)拥有快速查找的能力
 * max-heap(或min-heap)可以协助完成所谓的heap sort(堆排序)
 *
 */

/*
 * 算法分析用Big-Oh来标记复杂度
 *
 */

/*
 * 算法总览
 *
 * accumlate 元素累加
 * adjacent_difference 相邻元素的差额
 * adjacent_find 查找相邻而重复(或符合某条件)的元素
 *
 * binary_search 二分查找
 *
 * Copy 复制
 *
 * Copy_backward 逆向复制
 *
 * Copy_n * 复制n个元素
 *
 * count 计数
 *
 * count_if 在特定条件下计数
 *
 * equal 判断两个区间相等与否
 *
 * equal_range 试图在有序区间中寻找某值(返回一个上下限区间)
 *
 * fill 改填元素值
 *
 * fill_n 改填元素值, n次
 *
 * find_if 循序查找符合特定条件者
 *
 * find_end 查找某个子序列的最后一次出现点
 *
 * find_first_of 查找某些元素的首次出现点
 *
 * for_each 对区间内的每一个元素施行某操作
 *
 * generate 以特定操作之运算结果填充特定区间内的元素
 *
 * generate_n 以特定操作之运算结果填充n个元素内容
 *
 * includes 是否涵盖于某序列中
 *
 * inner_product 内积
 *
 * inplace_merge 合并并就地替换(覆写上去)
 *
 * Iota * 在某区间填入某指定值的递增序列
 *
 * is_heap * 判断某区间是否为一个heap
 *
 * is_sorted * 判断某区间是否已排序
 *
 * iter_swap 元素互换
 *
 * lexicographical_compare 以字典顺序进行比较
 *
 * lower_bound "将制定元素插入区间之内而不影响区间之原本排序的最低位置"
 *
 * max 最大值
 *
 * max_element 最大值所在位置
 *
 * merge 合并两个序列
 *
 * min 最小值
 *
 * min_element 最小值所在位置
 *
 * mismatch 找出不匹配点
 *
 * next_permutation 获得下一个排列组合
 *
 * nth_element 重新安排序列中的第n个元素的左右两端
 *
 * partial_sort 局部排序
 *
 * partial_sort_copy 局部排序并复制到他处
 *
 * partial_sum 局部求和
 *
 * partition 分割
 *
 * prev_permutation 获得前一个排列组合
 *
 * power * 幂次方。表达式可指定
 *
 * random_shuffle 随机重排元素
 *
 * random_sample * 随机取样
 *
 * random_sample_n * 随机取样
 *
 * remove 删除某类元素(但不删除)
	*
	* remove_copy 删除某类元素并将结果复制到另一个容器
	*
	* remove_if 有条件地删除某类元素
	*
	* remove_copy if 有条件地删除某类元素并将结果复制到另一个容器
	*
	* replace 替换某类元素
	*
	* replace_copy 替换某类元素，并将结果复制到另一个容器
	*
	* replace_if 有条件地替换
	*
	* replace_copy_if 有条件地替换，并将结果复制到另一个容器
	*
	* reverse 反转元素次序
	*
	* reverse_copy 反转元素次序并将结果复制到另一个容器
	*
	* rotate 旋转
	*
	* rotate_copy 旋转，并将结果复制到另一个容器
	*
	* search 查找某个子序列
	*
	* search_n 查找"连续发生n次"的子序列
	*
	* set_difference 差集
	*
	* set_intersection 交集
	*
	* set_symmetric_difference 对称差集
	*
	* set_union 并集
	*
	* sort 排序
	*
	* stable_partition 分割并保持元素的相对次序
	*
	* stable_sort 排序并保持等值元素的相对次序
	*
	* swap 交换(对调)
	*
	* swap_ranges 交换(指定区间)
	*
	* transform 以两个序列为基础，交互作用产生第三个序列
	*
	* unique 将重复的元素折叠缩编，使成唯一
	*
	* unique_copy 将重复的元素折叠缩编，使成唯一，并复制到他处
	*
	* upper_bound "将制定元素插入区间之内而不影响区间之原本排序的最高元素"
	*
	* make_heap 制造一个heap
	*
	* pop_heap 从heap去出一个元素
	*
	* push_heap 将一个元素推进heap内
	*
	* sort_heap 对heap排序
 */


