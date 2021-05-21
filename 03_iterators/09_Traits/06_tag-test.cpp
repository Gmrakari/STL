

/*
 * Date:2021-05-21 15:34
 * filename:06_tag-test.cpp
 *
 */

/*
 * 仿真测试 tag types 继承关系所带来的影响
 */
#include <iostream>
using namespace std;

struct B { };								// B	: InputIterator
struct D1 : public B { };		// D1 : ForwardIterator
struct D2 : public D1 { };	// D2 : BidirectionalIterator

template <class I>
void func(I& p, B) {
	cout << " B version " << endl;
}

template <class I>
void func(I& p, D2) {
	cout << " D2 version " << endl;
}

int main() {
	int* p;
	func(p, B());
	func(p, D1());
	func(p, D2());
}
