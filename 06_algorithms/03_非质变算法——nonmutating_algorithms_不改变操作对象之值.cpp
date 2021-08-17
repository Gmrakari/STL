

/*
 * Date:2021-08-17 10:39
 * filename:03_非质变算法——nonmutating_algorithms_不改变操作对象之值.cpp
 *
 */

/*
 * 所谓"非质变算法"，是指运算过程中不会更改区间内(迭代器所指)的元素内容
 * 诸如查找(find), 匹配(search),计数(count),寻访(for_each),比较(equal, mismatch)
 * 寻找极值(max, min)等算法
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
struct plus2 {
	void operator() (T& x) const {
		x += 2;
	}
};

int main() {
	int ia[] = {22, 30, 30, 17, 33, 40, 17, 23, 22, 12, 20};
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
	auto vite1 = iv.begin();
	auto vite2 = iv.end();
	cout << "before:";
	for (; vite1 != vite2; vite1++ ) {
		cout << *vite1 << ' ';
	}
	cout << endl;

	for_each(iv.begin(), iv.end(), plus2<int>());

	cout << "after:";
	vite1 = iv.begin();
	vite2 = iv.end();
	for (; vite1 != vite2; vite1++ ) {
		cout << *vite1 << ' ';
	}
	cout << endl;

}


