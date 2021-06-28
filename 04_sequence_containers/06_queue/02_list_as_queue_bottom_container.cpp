

/*
 * Date:2021-06-28 15:44
 * filename:02_list_as_queue_bottom_container.cpp
 *
 */

/*
 * 除了deque之外，list也是双向开口的数据结构
 * empty,size, front, back, push_front, push_back, pop_front, pop_back,这些list都具备
 */
#include <queue>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	queue<int, list<int>> iqueue;
	iqueue.push(1);
	iqueue.push(3);
	iqueue.push(5);
	iqueue.push(7);

	cout << iqueue.size() << endl;	//4
	cout << iqueue.front() << endl; //1

	iqueue.pop(); cout << iqueue.front() << endl; //3
	iqueue.pop(); cout << iqueue.front() << endl; //5
	iqueue.pop(); cout << iqueue.front() << endl; //7
	cout << iqueue.size() << endl;	//1
}
