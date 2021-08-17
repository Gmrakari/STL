

/*
 * Date:2021-08-17 10:15
 * filename:02_质变算法_mutating_algorithms_会改变操作对象之值.cpp
 *
 */

/*
 * 所有的STL算法都作用在由迭代器[first, last)所标示出来的区间上。
 * 所谓"质变算法",是指运算过程中会改变区间内(迭代器所指)的元素内容
 * 如拷贝(copy),互换(swap),替换(replace),填写(fill),删除(remove)
 * 排列组合(permutation),分割(partition),随机重排(random shuffling)
 * 排序(sort)等算法
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename _Tp>
int compare(_Tp& _ty1, _Tp& _ty2) {
	if (_ty1 < _ty2)
		return _ty1;
	else
		return _ty2;
}

int sort_func_test() {
	int ia[] = {22, 30, 30, 17, 33, 40, 17, 23, 22, 12, 20};
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

	vector<int>::const_iterator cite1 = iv.begin();
	vector<int>::const_iterator cite2 = iv.end();
	cout << "before sort:";
	for (; cite1 != cite2; cite1++) {
		cout << *cite1 << ' ';
	}
	cout << endl;
	sort(cite1, cite2);

	cout << "after sort:";
	for (; cite1 != cite2; cite1++) {
		cout << *cite1 << ' ';
	}
	cout << endl;
	return 1;
}

/*
 * 编译器出现很多error
 *
 */


/*
 * 改进
 */

int template_sort_func_test() {
	int ia[] = {22, 30, 30, 17, 33, 40, 17, 23, 22, 12, 20};
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

	vector<int>::const_iterator cite1 = iv.begin();
	vector<int>::const_iterator cite2 = iv.end();
	cout << "before sort:";
	for (; cite1 != cite2; cite1++) {
		cout << *cite1 << ' ';
	}
	cout << endl;
	sort(iv.begin(), iv.end(),compare<int>());

	cout << "after sort:";
	for (; cite1 != cite2; cite1++) {
		cout << *cite1 << ' ';
	}
	cout << endl;
	return 1;
}
int main() {
	int ret = 0;
//	ret = sort_func_test();
	//cout << ret << endl;
	int template_sort_func_test(void);
	ret = template_sort_func_test();
	cout << ret << endl;
}
