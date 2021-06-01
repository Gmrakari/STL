

/*
 * Date:2021-06-01 16:56
 * filename:03_test-splice.cpp
 *
 */

#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	list<int> ilist;
	ilist.push_back(0);
	ilist.push_back(2);
	ilist.push_back(99);
	ilist.push_back(3);
	ilist.push_back(4);

	cout << "print ilist:";
	for(auto it = ilist.begin();it != ilist.end();it++) {
		cout << *it << ' ';
	}
	cout << endl;

	int iv[5] = {5, 6, 7, 8, 9};
	list<int> ilist2(iv, iv + 5);

	cout << "print ilist2:";
	for(auto it = ilist2.begin();it != ilist2.end();it++) {
		cout << *it << ' ';
	}
	cout << endl;

	auto ite = find(ilist2.begin(), ilist2.end(),99);

	cout << "find target '99' in ilist2:"; 
	if(ite != ilist2.end()) {
		cout << "exist 99" << endl;
	}
	else {
		cout << "does not exist" << endl;
	}
	
	// splice 从定义iterator-ite2 = ilist.begin() 的position位置开始 拼接 容器list-ilist2的内容
	auto ite2 = ilist.begin();
	ilist.splice(ite2,ilist2);
	cout << "print ilist.splice:";
	for(list<int>::iterator it = ilist.begin(); it != ilist.end();it++) {
		cout << *it << " ";	//print ilist.splice:5 6 7 8 9 0 2 99 3 4 
	}
	cout << endl;

	cout << "ilist.reverse:";
	ilist.reverse();
	for(list<int>::iterator it = ilist.begin(); it != ilist.end();it++) {
		cout << *it << " ";
	}
	cout << endl;

	cout << "ilist.sort():";
	ilist.sort();
	for(list<int>::iterator it = ilist.begin(); it != ilist.end();it++) {
		cout << *it << " ";
	}
	cout << endl;

	return 0;

}
