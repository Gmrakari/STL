

/*
 * Date:2021-07-21 15:37
 * filename:04_priority_queue_测试实例.cpp
 *
 */

#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
	priority_queue<int> ipq(ia, ia + 9);
	cout << "size= " << ipq.size() << endl;

	for (int i = 0;i < (int)ipq.size(); ++i)
		cout << ipq.top() << ' ';
	cout << endl;

	while (!ipq.empty()) {
		cout << ipq.top() << ' ';
		ipq.pop();
	}
	cout << endl;
}
