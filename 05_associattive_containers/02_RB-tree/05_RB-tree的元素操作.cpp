

/*
 * Date:2021-08-11 10:02
 * filename:05_RB-tree的元素操作.cpp
 *
 */

/*
 * 元素(节点)的插入和搜寻
 * RB-tree提供两种插入操作:insert_unique()和insert_equal(),前者表示被插入节点的键值(key)在整颗树中必须独一无二
 * (因此，如果树中已存在相同的键值，插入操作就不会真正进行),后者表示被插入节点的键值在整颗树中可以重复，因此无论
 * 如何插入都会成功(除非空间不足导致配置失败)
 */

//元素插入操作insert_equal()
//插入新值;节点键值允许重复
//注意,返回值是一个RB-tree迭代器，指向新增节点
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const Value& v) {
	link_type y = header;
	link_type x = root();
	while ( x != 0 ) {
		y = x;
		x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);//大想左子树，小于等于往右子树
	}
	return __insert(x, y, v);//x为新值插入点，y为插入点之父节点，v为新值
}

//元素插入操作insert_unique()
//插入新值:节点键值不允许重复，若重复则插入无效
//注意，返回值是个pair,第一个元素是个RB-tree迭代器,指向新增节点，第二个元素表示插入成功与否
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const Value& v) {
	link_type y = header;
	link_type x = root();//从根节点开始
	bool comp = true;
	while (x != 0) {		//从根节点开始，往下寻找适当的插入点
		y = x;
		comp = key_compare(KeyOfValue()(v), key(x));//v键值小于目前节点之键值?
		x = comp ? left(x) : right(x);	//遇"大"则往左，遇"小于或等于"则往右边
	}

	//离开while循环之后，y所指即插入点之父节点(此时的它必须为叶节点)
	iterator j = iterator(y);//令迭代器j指向插入点之父节点y
	if (comp) //如果离开while循环时comp为真(表示遇"大",将插入于左侧)
		if (j == begin()) //如果插入点之父节点为最左节点
			return pair<iterator, bool>(__insert(x, y, v), true);
	//以上，x为插入点，y为插入点之父节点，v为新值
		else // 插入点之父节点不为最左节点
			--j;
	if (key_compare(key(j.node), KeyOfValue()(v)))
		//新建值不与即有节点之键值重复，于是以下执行安插操作
		return pair<iterator, bool>(__insert(x, y, v), true);
	//以上，x为新值插入点,y为插入点之父节点，v为新值

	//进行至此，表示新值一定与树中键值重复，那么就不该插入新值
	return pair<iterator, bool>(j, false);
}

//真正的插入执行程序 __insert()
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::__insert(base_ptr x_, base_ptr y_, const Value& v) {
	//参数x_ 为新值插入点，参数y_为插入点之父节点，参数v为新值
	link_type x = (link_type) x_;
	link_type y = (link_type) y_;
	link_type z;

	//key_compare 是键值大小比较准则，应该会是个function object
	if (y == header || x != 0 || key_compare(KeyOfValue()(v), key(y))) {
		z = create_node(v);//产生一个新节点
		left(y) = z;				//使得当y即为header时，leftmost() = z
		if (y == header) {
			root() = z;
			rightmost() = z;
		}
		else if (y == leftmost())				//如果y为最左节点
			leftmost() = z;							//维护leftmost(),使它永远指向最左节点
	}
	else {
		z = create_node(v);					//产生一个新节点
		right(y) = z;								//令新节点成为插入点之父节点y的右子节点
		if (y == rightmost()) 
			rightmost() = z;					//维护rightmost(),使它永远指向最右节点
	}
	parent(z) = y;								//设定新节点的父节点
	left(z) = 0;									//设定新节点的左子节点
	right(z) = 0;									//设定新节点的右子节点

	__rb_tree_rebalance(z, header->parent);//新节点的颜色将在__rb_tree_rebalance()设定(并调整)参数一为新增节点，参数二为root

	++node_count;//节点数累加
	return iterator(z);//返回一个迭代器，指向新增节点
}

//调整RB-tree(旋转及改变颜色)
//任何插入操作，于节点插入完毕后，都要做一次调整操作，将树的状态调整到符合RB-tree的要求

//__rb_tree_rebalance是具备如此能力的一个全局函数:
//全局函数
//重新令树形平衡(改变颜色及旋转树形)
//参数以为新增节点，参数二为root

inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
	x->color = __rb_tree_red;//新节点必为红
	while (x != root && x->parent->color == __rb_tree_red) { //父节点为红
		if (x->parent == x->parent->parent->left) {						//父节点为祖父节点之左子节点
			__rb_tree_node_base* y = x->parent->parent->right;	//令y为伯父节点
			if (y && y->color == __rb_tree_red) {								//伯父节点存在，且为红
				x->parent->color = __rb_tree_black;					//更改父节点为黑
				y->color = __rb_tree_black;						//更改伯父节点为黑
				x->parent->parent->color = __rb_tree_red;		//更改祖父节点为红
				x = x->parent->parent;
			}
			else {
				//无伯父节点，或伯父节点为黑
				if (x == x->parent->right) { //如果新节点为父节点之右子节点
					x = x->parent;
					__rb_tree_rotate_left(x, root);//第一参数为左旋点
				}
				x->parent->color = __rb_tree_black;//改变颜色
				x->parent->parent->color = __rb_tree_red;
				__rb_tree_rotate_right(x->parent->parent, root);//第一参数为右旋点
			}
		}
		else {	//父节点为祖父节点之右子节点
			__rb_tree_node_base* y = x->parent->parent->left;	//令y为伯父节点
			if (y && y->color == __rb_tree_red) { //有伯父节点，且为红
				x->parent->color = __rb_tree_black;		//更改父节点为黑
				y->color = __rb_tree_black;		//更改伯父节点为黑
				x->parent->parent->color = __rb_tree_red;//更改祖父节点为红
				x = x->parent->parent;//准备继续往上层检查
			}
			else {		//无伯父节点，或伯父节点为黑
				if (x == x->parent->left) {		//如果新节点为父节点之左节点
					x = x->parent;
					__rb_tree_rotate_right(x, root);	//第一参数为右旋点
				}
				x->parent->color = __rb_tree_black;//改变颜色
				x->parent->parent->color = __rb_tree_red;
				__rb_tree_rotate_left(x->parent->parent, root);//第一参数为左旋点
			}
		}
	}//while end
	root->color = __rb_tree_black;//根节点永远为黑
}

//左旋和右旋的实现

//全局函数
//新节点必为红节点。如果插入处之父节点亦为红节点，就违反红黑树规则，此时可能需要做树形旋转
inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
	//x为旋转点
	__rb_tree_node_base* y = x->right;//令y为旋转点的右子节点
	x->right = y->left;
	if (y->left != 0)
		y->left->parent = x;
	y->parent = x->parent;

	//令y完全顶替x的地位(必须将x对其父节点的关系完全接收过来)
	if (x == root)
		root = y;
	else if (x == x->parent->left)		//x为其父节点的左子节点
		x->parent->left = y;
	else
		x->parent->right = y;			//x为其父节点的右子节点
	y->left = x;
	x->parent = y;
}

//全局函数
//新节点必为红节点。如果插入处之父节点亦为红节点，就违反红黑树规则，此时可能需要做树形旋转
inline void __rb_tree_rorate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root) {
	//x为旋转点
	__rb_tree_node_base* y = x->left; //y为旋转的左子节点
	x->left = y->right;

	if (y->right != 0) 
		y->right->parent = x;
	y->parent = x->parent;

	if (x == root) 
		root = y;
	else if ( x == x->paren->right ) 
		x->parent->right = y;
	else 
		x->parent->left = y;
	y->right = x;
	x->parent = y;
}

