

/*
 * Date:2021-06-28 15:55
 * filename:01_heap_intro.cpp
 *
 */

/*
 * head并不归属STL容器组件，它是实现priority queue的基础
 * priority queue允许用户以任何次序将任何元素推入容器内，但取出时一定是从优先权最高的元素开始取
 * binary max heap具有这样的特性，适合作为priority queue的底层机制
 *
 * binary heap 是介于queue和binary search tree之间实现priority queue的底层部件
 *
 * binary heap 是一种complete binary tree(完全二叉树)
 * 整棵binary tree除了最底层的叶节点(s)之外，是填满的，而最底层的叶节点(s)由左至右不得有空隙
 *
 * complete binary tree整棵树内没有任何节点漏洞，这带来一个极大的好处:
 * 我们可以利用array来存储所有节点。假设动用一个小技巧，将array的#0元素保留(或设为无限大值或无限小值)
 * 那么当complete binray tree中的某个节点位于array的i处时,其左子节点比位于array的2i处,其右子节点必位于array的
 * 2i + 1处，其父结点比位于"i / 2" 处(此处的"/"权且代表高斯符号，取其整数)
 *
 * 通过这么简单的位置规则，array可以轻易实现出complete binary tree,这种以array表述tree的方式，我们称为
 * 隐式表述法(impicit representation)
 *
 * 根据元素排列方式，heap可分为max-heap 和 min-heap两种，前者每个节点的键值(key)都大于或等于其子节点键值
 * 后者的每个结点键值(key)都小于或等于其子节点键值
 * max-heap的最大值在根节点，并总是位于底层array或vector的起头处
 */


