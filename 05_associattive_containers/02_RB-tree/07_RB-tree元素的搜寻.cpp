

/*
 * Date:2021-08-12 20:21
 * filename:07_RB-tree元素的搜寻.cpp
 *
 */

/*
 * RB-tree是一个二叉搜索树，元素的搜寻正是其那手项目
 * find()
 */

//寻找RB树中是否有键值为K的节点
template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key& k) {
	link_type y = header;		//Last node which is not less than K;
	link_type x = root();		//Current node

	while (x != 0) {
		//key_compare是节点键值大小比较准则
		if (!key_compare(key(x), k))
			//表示x键值大于k 遇到大值就向左走
			y = x, x = left(x);
		else
			x = right(x);

		iterator j = iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j; 
	}
}
