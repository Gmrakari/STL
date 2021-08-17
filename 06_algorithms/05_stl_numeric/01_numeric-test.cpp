

/*
 * Date:2021-08-17 15:12
 * filename:01_numeric-test.cpp
 *
 */

#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <cmath>

using namespace std;

int main() {
	int ia[5] = {1, 2, 3, 4, 5};
	vector<int> iv(ia, ia + 5);

	cout << accumulate(iv.begin(), iv.end(), 0) << endl;//vector<int> 元素累加 输出15
	//15 0 + 1 + 2 + 3 + 4  + 5 ,默认+
	
	cout << accumulate(iv.begin(), iv.end(),0, minus<int>()) << endl;
	//-15, 0 - 1 - 2 - 3 - 4 - 5
	
	cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;
	//65 10 + 1 * 1 + 2 * 2 + 3 * 3 + 4 * 4 + 5 * 5
	
	cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>()) << endl;
	//-20, 10 - 1+1 - 2+2 - 3+3 - 4+4 - 5+5 从10开始
	
	//以下这个迭代器将绑定到cout,作为输出用
	ostream_iterator<int> oite(cout, " ");

	partial_sum(iv.begin(), iv.end(), oite);
	//1 3 6 10 15 (第n个新元素是前n个旧元素的相加总计)
	cout << endl;
	
	partial_sum(iv.begin(), iv.end(), oite, minus<int>());
	cout << endl;
	//1 -1 -4 -8 -13(第n个新元素是前n个旧元素的运算总计)
	
	adjacent_difference(iv.begin(), iv.end(), oite);
	cout << endl;
	//1 1 1 1 1 (#1元素照录, #n新元素等于 #n旧元素 - #n - 1旧元素)
	
	adjacent_difference(iv.begin(), iv.end(), oite, plus<int>());
	cout << endl;
	//1 3 5 7 9 (#1元素照录, #n新元素等于op(#n旧元素, #n - 1旧元素))
	
	cout << pow(10, 3) << endl;
	//cout << power(10, 3, plus<int>()) << endl; //30, 10 + 10 + 10
	
	int n = 3;
	iota(iv.begin(), iv.end(), n); //在指定区间内填入n, n + 1, n + 2
	for (int i = 0;i < (int)iv.size(); ++i)
		cout << iv[i] << ' ';
	//3 4 5 6 7  从n = 3 开始, 3, 3 + 1, 3 + 2,...,
	cout << endl;

}
