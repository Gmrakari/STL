

/*
 * Date:2021-08-14 13:33
 * filename:01_hashtable_intro.cpp
 *
 */

/*
 * hash table可提供对任何有名项(named item)的存取操作和删除操作
 * 由于操作对象是有名项，所以hash table也可被视为一种字典结构(dictionary)
 *
 * 使用hash function会带来一个问题:可能有不同的元素被映射到相同的位置(亦即有相同的索引)
 *
 * 这称为"碰撞问题",解决碰撞问题的方法有许多种:
 * 包括线性探测(linear probing),二次探测(quadratic probing),开链(separate chaining)
 *
 */

/*
 * 线性探测(linear probing)
 * 负载系数(loading factor)，意指元素个数初一表格大小，负载系数永远在0 ~ 1之间--除非采用开链(separate chaining)策略
 *
 * 当hash function计算出某个元素的插入位置，而该位置上的空间以不再可用时，
 * 最简单的做法是往下一一寻找(如果到达尾端,就绕到头部继续寻找),直到找到一个可用空间为止。
 * 只要表格(亦即array)足够大，总是能够找到一个安身立命的空间，但是要花多少时间就很难说了。
 *
 * 进行元素搜寻操作时，道理也相同，如果hash function计算出来的位置上的元素值与我们的搜寻目标不符，
 * 就循序往下一一寻找，直到找到吻合者，或直到遇到空格元素
 *
 * 至于元素的删除，必须采用惰性删除(lazy deletion)，也就是只标记删除记号，实际删除操作则待表格重新整理(rehashing)
 * 时再进行--这是因为hash table中的每一个元素不仅代表它自己，也关系到其他元素的排列
 *
 * 问题:平均插入成本的成长幅度，远高于负载系数的成长幅度。这样的现象在hashing过程中称为主集团(primary clustering)
 *
 * 此时的我们手上有的是一大团已被用过的方格，插入操作极有可能在主集团所形成的泥泞中奋力爬行，不断解决碰撞问题，
 * 最后才射门的分，但是却又助长了主集团的泥泞面积
 *
 */

/*
 * 二次探测(quadratic probing)
 *
 * 二次探测主要用来解决主集团问题(primary clustering)的问题
 * 其命名由来是因为解决碰撞问题的方程式F(i) = i^2是个二次方程式
 * 如果hash function计算出新元素的位置为H,而该位置实际上已被使用，那么我们就依序尝试H + 1^2, H + 2^2, H + 3^2,...,H + i^2,
 * 而不是像线性探测那样依序尝试H + 1, H + 2,..., H + i
 *
 * 二次探测可以消除主集团(parimary clustering),却可能造成次集团(secondary clustering):
 * 两个元素经hash function计算出来的位置若相同，则插入时候所探测的位置也相同，形成某种浪费
 *
 */

/*
 * 开链(separate chaining) 
 * 在每个表格元素中维护一个list;hash function为我们分配某一个list,
 * 然后我们在那个list身上进行元素的插入、搜寻、删除等操作
 * 虽然针对list而进行的搜寻只能是一种线性操作，但如果list够短，速度还是够快
 *
 * SGI STL的hash table是使用开链的做法
 *
 */

