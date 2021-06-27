

/*
 * Date:2021-06-27 18:33
 * filename:02_as_list_to_stack.cpp
 *
 */


//以list作为stack的底层容器

/*
 * 除了deque之外,list也是双向开口的数据结构
 * empty,size,back,push_back,pop_back,list都具备
 * 因此，若以list为底部结构并封闭其头端开口，一杨能轻易形成一个stack
 */

#include <stack>
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	stack<int, list<int>> istack;
	istack.push(1);
	istack.push(3);
	istack.push(5);
	istack.push(7);


	cout << istack.size() << endl;
	cout << istack.top() << endl;

	istack.pop();cout << istack.top() << endl;
	istack.pop();cout << istack.top() << endl;
	istack.pop();cout << istack.top() << endl;
	cout << istack.size() << endl;
}
