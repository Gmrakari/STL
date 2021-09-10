

/*
 * Date:2021-09-10 16:22
 * filename:05_IOStream_Iterator.cpp
 *
 */

/*
 * 所谓iostream iterators 可以将迭代器绑定到某个iostream对象身上
 * 绑定到istream对象(例如std::cin)身上的，称为istream_iterator,拥有输入功能:
 * 绑定到ostream对象(例如std::out)身上的，称为ostream_iterator，拥有输出功能
 * 这种迭代器运用于屏幕输出，非常方便
 *
 * 稍加修改，便可使用于任何输出或输入装置上。
 *
 * 仿函数配接器(functor adapters)总是以仿函数作为参数，予人以"拿某个配接器来修饰某个仿函数"的直观感受
 * 这里所接受的迭代器配接器(iterator adapters)很少以迭代器为直接参数。
 * 所谓对迭代器的修饰，只是一种观念上的改变(赋值操作变成插入操作，前进变成后退，绑定到特殊装置上)
 *
 * 集上述三种iterator adapters之运用大成:
 *
 */
#include <iterator>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
	ostream_iterator<int> outite(cout, " ");

	int ia[] = {0,1,2,3,4,5};
	deque<int> id(ia, ia + 6);

	copy(id.begin(), id.end(), outite);
	cout << endl;

	//将ia[]的部分元素拷贝到id内，使用front_insert_iterator
	//注意，front_insert_iterator会将assign操作改为push_front操作
	copy(ia + 1, ia + 2, front_inserter(id));
	copy(id.begin(), id.end(), outite);
	cout << endl;

	//将ia[]的部分元素拷贝到id内，使用back_insert_iterator
	copy(ia + 3, ia + 4, back_inserter(id));
	copy(id.begin(), id.end(), outite);
	cout << endl;

	//搜寻元素5的位置
	deque<int>::iterator ite = find(id.begin(), id.end(), 5);
	//将ia[]的部分元素拷贝到id内，使用insert_iterator
	copy(ia + 0, ia + 3, inserter(id, ite));
	copy(id.begin(), id.end(), outite);
	cout << endl;

	//将所有元素逆向拷贝到outite
	//rbegin()和rend()与reverse_iterator有关
	copy(id.rbegin(), id.rend(), outite);
	cout << endl;

	//以下，将inite绑定到cin。将元素拷贝到inite，直到eos出现
	istream_iterator<int> inite(cin), eso;
	copy(inite, eso, inserter(id, id.begin()));

	copy(id.begin(), id.end(), outite);
}

