

/*
 * Date:2021-08-18 10:42
 * filename:01_algobase-test.cpp
 *
 */

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

template <class T>
struct display {
	void operator()(const T& x) const {
		cout << x  << ' ';
	}
};

int main() {
	int ia[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	vector<int> iv1(ia, ia + 5);
	vector<int> iv2(ia, ia + 9);
	
	//{0, 1, 2, 3, 4} vs {0, 1, 2, 3, 4, 5, 6, 7, 8}
	cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first) << endl; //0
	cout << *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second) << endl;//5

	//以上判断两个区间的第一个不匹配点。返回一个由迭代器组成的pair
	//其中第一个迭代器指向区间的不匹配点，第二个迭代器指向第二区间的不匹配点
	//上述写法很危险，应该先判断迭代器是否不等于容器的end(),然后才做输出操作

	//如果两个序列在[first, last) 区间内相等，equal()返回 true
	//如果第二序列的元素比较多，多出来的元素不予考虑
	cout << equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;//1, true;

	//{0, 1, 2, 3, 4} 小于 {3, 4, 5, 6, 7};
	cout << equal(iv1.begin(), iv1.end(), &ia[3], less<int>()) << endl; //1

	fill(iv1.begin(), iv1.end(), 9);	//区间区内全部填9
	for_each(iv1.begin(), iv1.end(), display<int>());//9 9 9 9 9
	cout << endl;

	fill_n(iv1.begin(), 3, 7);			//从迭代器所指位置开始，填3个7
	for_each(iv1.begin(), iv1.end(),display<int>());//7 7 7 9 9
	cout << endl;

	vector<int>::iterator ite1 = iv1.begin();
	vector<int>::iterator ite2 = ite1;	
	advance(ite2, 3);//指向9 
	cout << "swap ite1 and ite2:";
	iter_swap(ite1, ite2);
	cout << *ite1 << ' ' << *ite2 << endl;
	cout << "for_each from iv1 to iv2:";
	for_each(iv1.begin(), iv1.end(), display<int>());
	cout << endl;

	//以下取两者之大者
	cout << "max:";
	cout << max(*ite1, *ite2) << endl;
	//以下取两者之小者
	cout << "min:";
	cout << min(*ite1, *ite2) << endl;

	//取两个迭代器(本身)之大者(或小者)，然后再取值*，迭代器本身的大小，对用户没有意义
	cout << *max(ite1, ite2) << endl;//7  
	cout << *min(ite1, ite2) << endl;//9

	//iv1:{9, 7, 7, 7, 9} iv2:{0, 1, 2, 3, 4, 5, 6, 7, 8}
	swap(*iv1.begin(), *iv2.begin());//将两数值对调
	for_each(iv1.begin(), iv1.end(), display<int>());//0 7 7 7 9
	cout << endl;

	for_each(iv2.begin(), iv2.end(), display<int>());//9 1 2 3 4 5 6 7 8
	cout << endl;

	//准备两个字符串数组
	string stra1[] = { "Jamie", "JJHou", "Jason" };
	string stra2[] = { "Jamie", "HHhou", "Jerry" };

	cout << lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2) << endl;//1
	cout << lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2, greater<string>()) << endl;//0
}
