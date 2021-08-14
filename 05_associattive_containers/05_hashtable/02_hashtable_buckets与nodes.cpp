

/*
 * Date:2021-08-14 15:35
 * filename:02_hashtable_buckets与nodes.cpp
 *
 */

/*
 * hash table表格内的元素为桶子(bucket),
 * 意义为表格内的每个单元，涵盖的不只是个节点(元素),甚且可能是"桶"节点
 *
 * hash table的节点定义:
 */
template <class Value>
struct __hashtable_node {
	__hashtable_node* next;
	Value val;
};

/*
 * bucket所维护的linked list,并不采用STL的list或slist,而是自行维护上述的hash table node
 * 至于bucket聚合体，则以vector完成，以便有动态扩充能力
 *
 */


