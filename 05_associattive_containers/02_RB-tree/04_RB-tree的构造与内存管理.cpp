

/*
 * Date:2021-08-11 09:49
 * filename:04_RB-tree的构造与内存管理.cpp
 *
 */

//RB-tree的定义
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
class rb_tree {
protected:
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
};

//RB-tree的构造有两种，一种是以现在的RB-tree复制一个新的RB-tree，另一种是产生一颗空空如也的树
rb_tree<int, int, identity<int>, less<int> > itree;

//dctor
rb_tree(const Compare& comp = Compare())
	: node_count(0), key_compare(comp) { init(); }

private:
void init() {
	header = get_node();//产生一个节点空间，令header指向它
	color(header) = __rb_tree_red;//令header为红色，用来区分header和root(在iterator.operator++中)
	root() = 0;
	leftmost() = header;//令header的左子节点为自己
	rightmost() = header;//令header的右子节点为自己
}

//走到根节点时要有特殊的处理，SGI STL特别为根节点再设计一个节点，名为header,并令其初始化
//每当插入新节点时，不但要依照RB-tree的规则来调整，并且维护header的正确性，使其父节点指向根节点，
//左子节点指向最小节点，右子节点指向最大节点。
