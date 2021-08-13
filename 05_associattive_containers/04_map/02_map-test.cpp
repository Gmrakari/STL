

/*
 * Date:2021-08-13 10:52
 * filename:02_map-test.cpp
 *
 */

#include <map>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
	map<string, int> simap;//以string为键值,int为实值
	simap[string("jjhou")] = 1;
	simap[string("jerry")] = 2;
	simap[string("jason")] = 3;
	simap[string("jimmy")] = 4;

	pair<string, int> value(string("david"), 5);
	simap.insert(value);

	//pair<string, int>::iterator simap_iter = simap.begin();
	auto simap_iter = simap.begin();
	for (; simap_iter != simap.end(); ++simap_iter)
		cout << simap_iter->first << ' ' << simap_iter->second << endl;

	int number = simap[string("jjhou")];
	cout << number << endl; //1

	map<string, int>::iterator ite1;

	//面对关联式容器，应该使用其所提供的find函数来搜寻元素会比使用STL算法find()更有效率
	//因为STL算法find()只是循序搜寻
	ite1 = simap.find(string("mchen"));
	if (ite1 == simap.end()) {
		cout << "mchen not found" << endl;
	}

	ite1 = simap.find(string("jerry"));
	if (ite1 != simap.end()) {
		cout << "jerry found" << endl;
	}
	
	ite1->second = 9;//可以通过map迭代器修改"value"(not key)
	int number2 = simap[string("jerry")];
	cout << number2 << endl;

	return 0;
}
