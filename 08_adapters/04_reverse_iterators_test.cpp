

/*
 * Date:2021-09-10 15:20
 * filename:04_reverse_iterators_test.cpp
 *
 */

#include <deque>
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>

using namespace std;

template <class T>
struct display {
	void operator()(const T& x) const {
		cout << x << ' ';
	}
};

int main() {
	deque<int> id;

	id.push_back(32);
	id.push_back(26);
	id.push_back(99);
	id.push_back(1);
	id.push_back(0);
	id.push_back(1);
	id.push_back(2);
	id.push_back(3);
	id.push_back(4);
	id.push_back(0);
	id.push_back(1);
	id.push_back(2);
	id.push_back(5);
	id.push_back(3);

	cout << "deque<int> id:";
	for_each(id.begin(), id.end(), display<int>());
	cout << endl;

	cout << "*(id.begin()): ";
	cout << *(id.begin()) << endl;

	cout << "*(id.rbegin()): ";
	cout << *(id.rbegin()) << endl;

	cout << "*(id.end()): ";
	cout << *(id.end()) << endl;// 0 dangerous

	//cout << "*(id.rend()): "; 
	//cout << *(id.rend()) << endl;


	deque<int>::iterator ite = find(id.begin(), id.end(), 99);
	reverse_iterator<deque<int>::iterator> rite(ite);

	cout << "*ite: ";
	cout << *ite << endl; //99

	cout << "*rite: ";
	cout << *rite << endl; //26

	/*
	 * 为什么"正向迭代器"和"与其相应的逆向迭代器"取出不同的元素呢?
	 * 这并不是一个潜伏的错误，而是一个刻意为之的特征，主要是为了配合迭代器区间的"前闭后开"习惯
	 * 当迭代器被逆向转方向时，虽然其实体位置(真正的地址)不变，但其逻辑位置(迭代器所代表的元素)改变了
	 *
	 * 唯有这样，才能保持正向迭代器的一切惯常行为
	 * 唯有这样，当我们将一个正向迭代器区间转换为一个逆向迭代器区间后，不必再有任何额外处理，
	 * 就可以让接受这个逆向迭代器区间的算法，以相反的元素次序来处理区间中的每一个元素
	 *
	 */

	ostream_iterator<int> outite(cout, " ");
	cout << "copy(id.begin(), id.end(), outite):";
	copy(id.begin(), id.end(), outite);
	cout << endl;
	
	ostream_iterator<int> routite(cout, " ");
	cout << "copy(id.rbegin(), id.rend(), routite):";
	copy(id.rbegin(), id.rend(), routite);
	cout << endl;


	/*
	 * id.rbegin()是个暂时对象
	 * 相当于:
	 * reverse_iterator<deque<int>::iterator>(id.end()); //指向本例的最后元素
	 * deque<int>::reverse_iterator(id.end());					//指向本例的最后元素
	 *
	 */

	cout << endl << "--------------------------------------------------" << endl;
	deque<int> ide;
	ide.push_back(1);
	ide.push_back(0);
	ide.push_back(1);
	ide.push_back(2);
	ide.push_back(3);
	ide.push_back(4);
	ide.push_back(0);
	ide.push_back(1);
	ide.push_back(2);
	ide.push_back(5);
	ide.push_back(3);

	ostream_iterator<int> ide_outite(cout, " ");
	cout << "deque<int> ide:";
	copy(ide.begin(), ide.end(), ide_outite);
	cout << endl;

	deque<int>::reverse_iterator rite2(ide.end());
	cout << "deque<int>::reverse_iterator rite2(ide.end()):" << endl;
	cout << "*rite2:";
	cout << *(rite2) << endl;

	cout << "*(++++++rite2): ";
	cout << *(++++++rite2) << endl;

	cout << "*(--rite2): ";
	cout << *(--rite2) << endl;

	cout << "*(rite2.base()) 恢复正向迭代器后，取值: ";
	cout << *(rite2.base()) << endl;

	cout << "rite2[3] 前进3个位置后取值: ";
	cout << rite2[3] << endl;
}
