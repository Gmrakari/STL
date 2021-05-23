

/*
 * Date:2021-05-23 15:55
 * filename:05_vector-test.cpp
 *
 */

//05_vector_constructor-push_back.cpp

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	vector<int> iv(2,9);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0; i < int(iv.size());i++)
		cout << iv[i] << ' ';
	cout << endl;

	iv.push_back(1);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(2);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(3);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(4);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(5);

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0;i < (int)iv.size();++i) {
		cout << iv[i] << ' ';
	}
	cout << endl;

	iv.pop_back();
	iv.pop_back();

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.pop_back();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	vector<int>::iterator ivite = find(iv.begin(),iv.end(),1);
	if (ivite != iv.end()) iv.erase(ivite);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	for (int i = 0; i < int(iv.size());++i)
		cout << iv[i] << ' ';
	cout << endl;

	ivite = find(iv.begin(),iv.end(),2);

	if (ivite != iv.end()) iv.insert(ivite,3,7);

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0; i < int(iv.size());++i)
		cout << iv[i] << ' ';
	cout << endl;

	iv.clear();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	return 0;
}


