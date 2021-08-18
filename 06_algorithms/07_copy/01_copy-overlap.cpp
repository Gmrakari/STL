

/*
 * Date:2021-08-18 14:32
 * filename:01_copy-overlap.cpp
 *
 */

#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
using namespace std;

template <class T>
struct display {
	void operator() (const T& x) {
		cout << x << ' ';
	}
};

int main() {
	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

		cout << "原串:";
		for_each(ia, ia + 9, display<int>());
		cout << endl;

		//以下 输出区间的终点与输入区间重叠，没有问题
		copy(ia + 2, ia + 7, ia);
		cout << "copy(ia + 2, ia + 7, ia):";
		for_each(ia, ia + 9, display<int>());
		cout << endl;
	}
	
	cout << endl;

	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

		cout << "原串:";
		for_each(ia, ia + 9, display<int>());
		cout << endl;

		//以下，输出区间的起点与输入区间重叠，可能会有问题
		copy(ia + 2, ia + 7, ia + 4);
		cout << "copy(ia + 2, ia + 7, ia + 4):";
		for_each(ia, ia + 9, display<int>());
		cout << endl;
		//本例结果正确，因为调用的copy算法使用memmove()执行实际复制操作
	}

	cout << endl;

	{
		cout << "deque test:" << endl;
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		deque<int> id(ia, ia + 9);
		
		deque<int>::iterator first = id.begin();
		deque<int>::iterator last = id.end();

		++++first;								//advance(first, 2);
		cout << "advance(first, 2):";
		cout << *first << endl; //2

		----last;								//advance(last, -2);
		cout << "advance(last, -2):";
		cout << *last << endl;	//7 不是6

		deque<int>::iterator result = id.begin();
		cout << *result << endl;// 第一个元素

		cout << endl << "before copy:";
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;

		//以下，输出区间的终点与输入区间重叠，没有问题
		copy(first, last, result);
		cout << "copy(first, last, result):";
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;
	}

	cout << endl;

	{
		cout << "vector test:" << endl;
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		std::vector<int> id(ia, ia + 9);
		
		vector<int>::iterator first = id.begin();
		vector<int>::iterator last = id.end();

		++++first;								//advance(first, 2);
		cout << "advance(first, 2):";
		cout << *first << endl; //2

		----last;								//advance(last, -2);
		cout << "advance(last, -2):";
		cout << *last << endl;	//7 不是6
		
		vector<int>::iterator result = id.begin();
		advance(result ,4);
		cout << *result << endl;

		//以下，输出区间的终点与输入区间重叠，可能有问题
		copy(first, last, result);
		cout << "copy(first, last, result):";
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;
	}
}


