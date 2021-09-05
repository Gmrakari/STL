

/*
 * Date:2021-09-05 16:08
 * filename:03_threshold_阈值.cpp
 *
 */

/*
 * 面对一个只有十来个元素的小型序列，使用像Quick Sort这样复杂而(可能)需要大量运算的排序法
 * 是否划算，在小数据量下，简单的如Insertion Sort可能也比Quick sort快
 * Quick Sort会为了极小的子序列而产生许多的函数递归调用
 *
 */

/*
 * final insertion sort
 *
 * Donald Knuth:贸然实施优化，是所有恶果的根源。
 * (premature optimization is the root of all evil)
 *
 * 如果我们令某个大小以下的序列滞留在"几近排序但尚未完成"的状态，最后再以一次Insertion Sort将所有这些
 * "几近排序但尚未竟全功"的子序列做一次完整的排序，其效率一般认为会比"将所有子序列彻底排序"更好
 * Insert Sort在面对"几近排序"的序列时，有很好的表现
 *
 */

/*
 * introsort
 * 不当的枢轴选择，导致不当的分割，导致Quick Sort恶化为O(N^2)
 * Introspective Sorting(内省式排序)，简称IntroSort，其行为在大部分情况下几乎与median-of-3 Quick Sort完全相同
 * 但是当分割行为(partitioning)有恶化为二次行为的倾向时，能够自我侦测，转而改用Heap Sort,
 * 使效率维持在Heap Sort的O(N log N)，又比一开始就使用Heap Sort来得好
 */

