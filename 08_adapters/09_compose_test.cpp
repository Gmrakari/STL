

/*
 * Date:2021-09-12 11:12
 * filename:09_compose_test.cpp
 *
 */

#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;


int main() {
	ostream_iterator<int> outite(cout, " ");

	int ia[6] = {2, 21, 12, 7, 19, 23};
	vector<int> iv(ia, ia + 6);

	//每个元素v 身上执行(v + 2) * 3
	for_each(iv.begin(), iv.end(), compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2)));

	copy(iv.begin(), iv.end(), outite);
	cout << endl;

	//如果像这样，输往另一地点(cout)，是可以的
	transform(iv.begin(), iv.end(), outite, compose1(bind2nd(multiplies<int>(), 3), bind2nd(plus<int>(), 2)));
	cout << endl;
}

/*
 * 仿函数就是"将function call 操作符重载"的一种class,而任何算法接受一个仿函数时，总是在其演算过程汇总调用该仿函数
 * 的operator(),这使得不具备仿函数之形、确有真函数之实的"一般函数"和"成员函数"感到为难
 *
 */

