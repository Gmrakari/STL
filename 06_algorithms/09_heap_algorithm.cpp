

/*
 * Date:2021-08-20 09:21
 * filename:09_heap_algorithm.cpp
 *
 */

/*
 * make_heap(),
 * pop_heap(),
 * push_heap(),
 * sort_heap()
 */
//#include <stl_heap.h>
#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

template <class T>
T cmp(T& a, T& b) {
	return a > b;
}

template <class T>
void display(T& a) {
	for (auto i : a) {
		cout << i << ' ';
	}
	cout << endl;
}

int main() {
	vector<int> vec{29, 23, 20, 22, 17, 15, 26, 51, 19, 12, 35, 40};

	cout << "vec:";	
	display(vec);

	//greater() 小顶堆 
	//less() 大顶堆
	make_heap(vec.begin(), vec.end(), greater<int>());//用于把一个可迭代容器变成一个堆，默认是大顶堆
	cout << "make_heap greater<int>:";
	display(vec);

	cout << "push_heap greater<int>:";
	vec.push_back(8);
	//确保在push_heap之前 把 数据 增加到容器中
	push_heap(vec.begin(), vec.end(), greater<int>());
	display(vec);

	cout << "pop_heap:";
	pop_heap(vec.begin(), vec.end(), greater<int>());//pop_heap 只是交换了两个元素的位置，需要弹出则需要pop_back()
	vec.pop_back();
	display(vec);


	cout << "befor sort_heap:";
	make_heap(vec.begin(), vec.end(), greater<int>());
	display(vec);

	cout << "after sort_heap:";
	sort_heap(vec.begin(), vec.end(), greater<int>());
	display(vec);
}
