

/*
 * Date:2021-08-12 19:57
 * filename:06_RB-tree-test.cpp
 *
 */

#include <map>
#include <set>
#include <iostream>

using namespace std;

int test() {
	rb_tree<int, int, identity<int>, less<int>> itree;
	cout << itree.size() << endl;

	//jjhou 修改<stl_tree.h> __rb_tree_rebalance,__rb_tree_rotate_left,__rb_tree_rotate_right
	
	itree.insert_unique(10); // __rb_tree_rebalance
	itree.insert_unique(7); // __rb_tree_rebalance
	itree.insert_unique(8);	// __rb_tree_rebalance

														// __rb_tree_rotate_left
														// __rb_tree_rotate_right

	itree.insert_unique(15);	// __rb_tree_rebalance
	itree.insert_unique(5);		// __rb_tree_rebalance
	itree.insert_unique(6);		// __rb_tree_rebalance

														// __rb_tree_rotate_left
														// __rb_tree_rotate_right

	itree.insert_unique(11);	// __rb_tree_rebalance

														// __rb_tree_rotate_right
														// __rb_tree_rotate_left

	itree.insert_unique(13);	// __rb_tree_rebalance
	itree.insert_unique(12);	// __rb_tree_rebalance

																		// __rb_tree_rotate_right

	cout<< itree.size() << endl; //9

	for (; ite1 != ite2; ++ite1) 
		cout << *ite1 << ' ';					// 5 6 7 8 10 11 12 13 15
	cout << endl;


	//测试颜色和operator++(亦即 __rb_tree_iterator_base::increment)
	rb_tree<int, int, identity<int>, less<int> >::iterator
		ite1 = itree.begin();

	rb_tree<int, int, identity<int>, less<int> >::iterator
		ite2 = itree.end();
	__rb_tree_base_iterator rbtite;

	for (; ite1 != ite2; ++ite1) {
		rbtite = __rb_tree_base_iterator(ite1);
		cout << *ite1 << '(' << rbtite.node->color << ")";
	}
	cout << endl;

	//结果: 5(0) 6(1) 7(0) 8(1) 10(1) 11(0) 12(0) 13(1) 15(0)

	return 0;
}
