

/*
 * Date:2021-06-21 15:20
 * filename:04_deque-test.cpp
 *
 */

#include <deque>
#include <iostream>
#include <algorithm>

using	namespace std;

int main() {
	//deque<int, allocator, 8> ideq(20, 9); //alloc,only using in g++
	deque<int> ideq(20, 9);

	//默认的缓冲区大小是多少? (deque的第三个参数)
	cout << "size = " << ideq.size() << endl; 
	
	//为每一个元素设定新值
	for (int i = 0; i < (int)ideq.size(); ++i) {
		ideq[i] = i;
	}

	for (int i = 0; i < (int)ideq.size(); ++i) 
		cout << ideq[i] << ' ';
	cout << endl;

	cout << endl;
	//在最尾端增加一个元素，其值为0,1,2
	for (int i = 0;i < 3;i++) 
		ideq.push_back(i);

	for (int i = 0; i < (int)ideq.size(); ++i) 
		cout << ideq[i] << ' ';
	cout << endl;
	cout << "size = " << ideq.size() << endl;

	cout << endl;
	//在最尾端增加一个元素，其值为3
	cout << "push_back one element the value is 3" << endl;
	ideq.push_back(3);
	for(int i = 0; i < (int)ideq.size(); ++i) {
		cout << ideq[i] << ' ';
	}
	cout << endl;
	cout << "size = " << ideq.size() << endl;

	cout << endl;
	//在最前端增加一个元素，其值为99
	cout << "push_front one element : 99" << endl;
	ideq.push_front(99);
	for(int i = 0; i < (int)ideq.size(); ++i) {
		cout << ideq[i] << ' ';
	}
	cout << endl;
	cout << "size = " << ideq.size() << endl;

	cout << endl;
	cout << "push_front two element : 98,97" << endl;
	//在最前端增加两个元素,其值分别为98,97
	ideq.push_front(98);
	ideq.push_front(97);
	for (int i = 0;i < (int)ideq.size(); ++i) {
		cout << ideq[i] << ' ';
	}
	cout << endl;
	cout << "size = " << ideq.size() << endl;

	//find 99 element & print
	deque<int>::iterator itr;
	itr = find(ideq.begin(),ideq.end(), 99);
	cout << *itr << endl;
	cout << *(itr._M_cur) << endl;

	return 0;


}
