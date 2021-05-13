

/*
 * Date:2021-05-13 20:51
 * filename:01_uninitialized_copy.cpp
 *
 */

/*
 * uninitialized_copy()使我们能够将内存的配置与对象的构造行为分离开来。
 * 如果作为输出目的地的[result,result + (last - first)]范围内的每一个迭代器都指向未初始化区域
 * 则uninitialized_copy()会使用copy constructor,给身为输入来源之[first,last]范围内的每一个对象
 * 产生一粉复制品,放进输入范围中。
 * 换句话说,针对输入范围内的每一个迭代器i,该函数会调用construct(&*(result + (i - first)), *i)
 * 产生*i的复制品,放置于输出范围的相对位置上
 *
 *
 * 全区间构造函数(range constructor)通常以两个步骤完成:
 * 配置内存区块,足以包含范围内的所有元素
 *
 * C++标准规格书要求uninitialized_copy() 
 * 具有"commit or rollback" --> 意思是要么"构造处所有必要元素",
 * 要么"当有任何一个copy constructor 失败时" 不构造任何东西
 */

