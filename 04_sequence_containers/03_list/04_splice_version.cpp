

/*
 * Date:2021-06-01 17:20
 * filename:04_splice_version.cpp
 *
 */

#include <iterator>
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

class Splice_Version {
public:
	//将x接合于position所指位置之前,x必须不同于*this
	void splice(iterator position, list& x) {
		if (!x.empty()) {
			transfer(position, x.begin(), x.end());
		}
	}

	//将i所指元素结合于position所指位置之前,position 和 i 可指向 同一个list
	void splice(iterator position, list& , iterator i) {
		iterator j = i;
		++j;
		if (position == i || position = j) return ;
		transfer(position, i, j);
	}

	//将[first,last]内的所有元素结合于position所指位置之前
	//position和[first,last]可指向同一个list,但position不能位于[first,last]之内
	void splice(iterator position, list&, iterator first, iterator last) {
		if (first != last) {
			transfer(position, first, last);
		}
	}
};
