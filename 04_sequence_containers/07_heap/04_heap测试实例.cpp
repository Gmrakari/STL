

/*
 * Date:2021-07-21 14:56
 * filename:04_heap测试实例.cpp
 *
 */

#include <vector>
#include <iostream>
#include <algorithm> //heap algorithm

using namespace std;

int main() {
	{
		//test heap (by vector)
		int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
		vector<int> ivec(ia, ia + 9);

		make_heap(ivec.begin(), ivec.end());
		for (int i = 0; i < (int)ivec.size(); ++i) {
			cout << ivec[i] << ' ';
		}
		cout << endl;

		ivec.push_back(7);
		push_heap(ivec.begin(), ivec.end());
		for (int i = 0; i < (int)ivec.size(); ++i) {
			cout << ivec[i] << ' ';
		}
		cout << endl;

		pop_heap(ivec.begin(), ivec.end());
		cout << ivec.back() << endl;				// 9 return 但是没有被remove
		ivec.pop_back();										// remove last elem and no return

		for (int i = 0; i < (int)ivec.size(); ++i) {
			cout << ivec[i] << ' ';
		}
		cout << endl;

		sort_heap(ivec.begin(), ivec.end());
		for (int i = 0; i < (int)ivec.size(); ++i) {
			cout << ivec[i] << ' ';
		}
		cout << endl;
	}
	
	{
		//test heap(by array)
		int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
		make_heap(ia, ia + 9);
		//array 无法动态改变大小，因此不可以对满载的array进行push_heap()操作
		//因为那得先在array尾端增加一个元素

		sort_heap(ia, ia + 9);
		for (int i = 0; i < 9;++i) {
			cout << ia[i] << ' ';
		}
		cout << endl;
		//经过排序之后的heap,不再是个合法的heap

		//重新再做一个heap
		make_heap(ia, ia + 9);
		pop_heap(ia, ia + 9);
		cout << ia[8] << endl;

	}

	{
		//test heap (by array)
		int ia[6] = {4, 1, 7, 6, 2, 5};
		make_heap(ia, ia + 6);
		for (int i = 0; i < 6; ++i) {
			cout << ia[i] << ' ';
		}
		cout << endl;
	}


}
