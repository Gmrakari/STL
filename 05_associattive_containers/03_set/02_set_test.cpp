

/*
 * Date:2021-08-13 09:36
 * filename:02_set_test.cpp
 *
 */

#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int i;
	int ia[5] = { 0, 1, 2, 3, 4 };
	set<int> iset(ia, ia + 5);

	cout << "size = " << iset.size() << endl;			// size = 5
	cout << "3 count=" << iset.count(3) << endl; //3 count = 1
	iset.insert(3);

	cout << "size = " << iset.size() << endl; //size = 5
	cout << "3 count=" << iset.count(3) << endl; //3 count = 1
	iset.insert(5);

	cout << "size = " << iset.size() << endl;				//size = 6
	cout << "3 count=" << iset.count(3) << endl; //3 count = 1

	iset.erase(1);
	cout << "size = " << iset.size() << endl;		//size = 5;

	cout << "3 count = " << iset.count(3) << endl;
	cout << "1 count = " << iset.count(1) << endl;

	set<int>::iterator ite1 = iset.begin();
	set<int>::iterator ite2 = iset.end();

	for (; ite1 != ite2; ++ite1) 
		cout << *ite1 << ' '; 
	cout << endl;

	ite1 = find(iset.begin(), iset.end(), 3);
	if (ite1 != iset.end()) 
		cout << "3 found" << endl;
	
	ite1 = find(iset.begin(), iset.end(), 1);
	if (ite1 == iset.end()) 
		cout << "1 not found" << endl;

	//使用STL算法的find更快
	ite1 = iset.find(3);
	if (ite1 != iset.end()) 
		cout << "3 found" << endl;

	ite1 = iset.find(1);
	if (ite1 == iset.end()) 
		cout << "1 not found" << endl;

	//*ite1 = 9;
	//error: assignment of read-only location 
	//'ite1.std::_Rb_tree_const_iterator<_Tp>::operator*<int>()'  *ite1 = 9;
}
