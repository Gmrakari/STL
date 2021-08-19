

/*
 * Date:2021-08-19 11:42
 * filename:04_copy_backward-overlap.cpp
 *
 */

#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

/*
namespace copy_backward_intro {
	void test() {
		template <class BidrectionalIterator1, class BidirectionalIterator2>
		inline BidirectionalIterator2 copy_backward(BidrectionalIterator1 first,
				BidrectionalIterator1 last, BidirectionalIterator2 result);
	}
}

*/

/*
 * copy_backward将[first, last)区间内的每一个元素，以逆行的方向复制到result - 1为起点，
 * 方向亦为逆行的区间上
 * copy_backward算法会执行赋值操作*(result - 1) = *(last - 1), *(result - 2) = *(last - 2),...,
 * 返回一个迭代器:result - (last - first)
 * copy_backward所接受的迭代器必须是BidirectionalIterators,才能够"倒行逆施"
 * 你可以使用copy_backward算法，将任何容器的任何一段区间的内容，复制到任何容器的任何一段区间上
 */

template <class T>
struct display {
	void operator() (const T& x) {
		cout << x << ' ';
	}
};


int main() {
	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		cout << "ia:";
		for (auto i : ia) {
			cout << i << ' ';
		}
		cout << endl;

		//以下，输出区间的终点(就你想而言)与输出区间重叠，没问题
		copy_backward(ia + 2, ia + 7, ia + 9); //*first = 2, *last = 6
		cout << "copy_backward:";
		for_each(ia, ia + 9, display<int>());
		cout << endl << endl;

	}
	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		copy_backward(ia + 2, ia + 7, ia + 5);
		for_each(ia, ia + 9, display<int>());
		cout << endl;
	}

	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		deque<int> id(ia, ia + 9);

		deque<int>::iterator first = id.begin();
		deque<int>::iterator last = id.end(); //
		++++first;
		cout << *first << endl;
		----last;														//减去两个 是到*6
		cout << *last << endl;

		cout << "befor copy_backward:";
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;

		deque<int>::iterator result = id.end();

		copy_backward(first, last, result);
		cout << "copy_back:";
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;
	}

	{
		int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
		deque<int> id(ia, ia + 9);

		deque<int>::iterator first = id.begin();
		deque<int>::iterator last = id.end();

		++++first;
		cout << *first << endl;

		----last;
		cout << *last << endl;

		deque<int>::iterator result = id.begin();
		advance(result, 5);
		cout << *result << endl;

		copy_backward(first, last, result);
		for_each(id.begin(), id.end(), display<int>());
		cout << endl;
	}
	return 0;
}
