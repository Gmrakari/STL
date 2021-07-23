

/*
 * Date:2021-07-23 18:26
 * filename:02_RB-tree的迭代器.cpp
 *
 */

/*
 * 将RB-tree实现为一个泛型容器
 * 首先要考虑它的类别(category),然后要考虑它的前进(increment),后退(decrement)
 * 提领(dereference),成员访问(member access)等操作
 *
 */

/*
 * __rb_tree_node 继承__rb_tree_node_base
 * __rb_tree_iterator 继承 __rb_tree_base_iterator
 *
 */

/*
 * RB-tree迭代器的前进操作operator++()调用了基层迭代器的increment()
 * 后退操作operator--()调用了基层迭代器的decrement()
 *
 */

//基层迭代器
struct __rb_tree_base_iterator {
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;

	base_ptr node;//它用来与容器之间产生一个连结关系(make a reference)

	//以下其实可实现于operator++内，因为再无他处会调用此函数了
	void increment() {
		if (node->right != 0) {			//如果有右子节点，状况1
			node = node->right;				//就向右走
			while (node->left != 0)		//然后一直往左子树走到底
				node = node->left;			//即是解答
		}
		else {											//没有右子节点，状况2
			base_ptr y = node->parent; //找出父节点
			while (node == y->right) { //如果现行节点本身是个右子节点
				node = y;								 //就一直上溯,直到"不为右子节点"止
				y = y->parent;
			}
			if (node->right != y)		//若此时的右子节点不等于此时的父节点
				node = y;								//状况3 此时的父节点即为解答
																
															//否则此时的node为解答  状况4
		}
	}

	//以下其实可实现于operator++内，因为再无他处会调用此函数了
	void decrement() {
		if (node->color == __rb_tree_red && node->parent->parent == node)		//如果是红节点，且父节点的父节点等于自己
			node = node->right;							// 状况1 右子节点即为解答
		else if (node->left != 0) {				//如果有左子节点 状况2
			base_ptr y = node->left;				//令y指向左子节点
			while (y->right != 0)						//当y有右子节点时
				y = y->right;									//一直网右子节点走到底
			node = y;												//最后即为答案
		}
		else {														//即非根节点，亦无左子节点
			base_ptr y = node->parent;			//状况3 找出父节点
			while (node == y->left) {				//当行现行节点身为左子节点
				node = y;											//一直交替往上走，直到现行节点
				y = y->parent;								//不为左子节点	
			}
			node = y;												//此时之父节点即为答案
		}
	}
};


//RB-tree的正规迭代器
template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator {
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef __rb_tree_iterator<Value, Ref, Ptr> self;
	typedef __rb_tree_node<Value>* link_type;

	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x) { node = x; }
	__rb_tree_iterator(const iterator& it) { node = it.node; }

	reference operator*() const {return link_type(node)->value_field;}
#ifndef __SGI_STL_NO_ARROW_OPERATPR
	pointer operator->() const {return &(operator*());}
#endif

	self& operator++() { increment();return *this; }
	self operator++(int) {
		self tmp = *this;
		increment();
		return tmp;
	}

	self& operator--() { decrement(); return *this; }
	self operator--(int) {
		self tmp = *this;
		decrement();
		return tmp;
	}
};
