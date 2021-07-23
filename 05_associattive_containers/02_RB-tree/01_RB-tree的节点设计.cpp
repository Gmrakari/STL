

/*
 * Date:2021-07-23 18:17
 * filename:01_RB-tree的节点设计.cpp
 *
 */

/*
 * miniumum()和maximum()函数可清楚看出,RB-tree作为一个二叉搜索树，其极值容易获取
 * 由于RB-tree的各种操作时常需要上溯其父结点，所以特别在数据结构中安排了一个parent指针
 */

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;//红色为0
const __rb_tree_color_type __rb_tree_black = true;//黑色为1

struct __rb_tree_node_base {
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;//节点颜色，非红即黑
	base_ptr parent;//操作需要
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr x) {
		while (x->left != 0) x = x->left;  //一直往左走，就会找到最小值
		return x;
	}

	static base_ptr maximum(base_ptr x) {
		while(x->right != 0) x = x->right; //一直往右走，就会找到最大值
		return x;
	}
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base {
	typedef __rb_tree_node<Value>* link_type;
	Value value_field;//节点值
};


