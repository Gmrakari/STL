

/*
 * Date:2021-08-28 10:28
 * filename:01_6_7_n.cpp
 *
 */

//gcc291 不接受random_shuffle()
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>

using namespace std;

struct even {
	bool operator()(int x) const {
		return x % 2 ? false : true;
	}
};

template <class T>
struct display {
	void operator() (const T& x) const {
		cout << x << ' ';
	}
};

int main() {
	int ia[] = { 12, 17, 20, 22, 23, 30, 33, 40 };
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

	cout << "vector iv:";
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	cout << "*lower_bound(iv.begin(), iv.end(), 21): ";
	cout << *lower_bound(iv.begin(), iv.end(), 21) << endl;

	cout << "*upper_bound(iv.begin(), iv.end(), 21): ";
	cout << *upper_bound(iv.begin(), iv.end(), 21) << endl;

	cout << "*lower_bound(iv.begin(), iv.end(), 22): ";
	cout << *lower_bound(iv.begin(), iv.end(), 22) << endl;

	cout << "*upper_bound(iv.begin(), iv.end(), 22): ";
	cout << *upper_bound(iv.begin(), iv.end(), 22) << endl;

	cout << endl;
	//面对有序区间(sorted range)，可以二分查找法寻找某个元素
	cout << "面对有序区间(sorted range)，用binary_saerch(iv.begin(), iv.end(), 33): ";
	cout << binary_search(iv.begin(), iv.end(), 33) << endl; //1 (true)
	cout << binary_search(iv.begin(), iv.end(), 34) << endl; //0 (false)

	cout << endl;
	//下一个排列组合
	cout << "next_permutation: ";
	next_permutation(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	//上一个排列组合
	cout << "prev_permutation: ";
	prev_permutation(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	//随机重排
	cout << "random_shuffle: ";
	random_shuffle(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	//将iv.begin() + 4 - iv.begin()个元素排序，放进[iv.begin(), iv.begin() + 4)区间内。
	//剩余元素不保证维持原相对次序
	cout << "将iv.begin() + 4 - iv.begin()个元素排序，放进[iv.begin(), iv.begin() + 4)区间内: ";
	partial_sort(iv.begin(), iv.begin() + 4, iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	//排序(缺省为递增排序)
	cout << "排序(缺省为递增排序):";
	sort(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << endl;
	///排序(指定为递减排序)
	cout << "排序(指定为递减排序):";
	sort(iv.begin(), iv.end(), greater<int>());
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	cout << endl;
	//在iv尾端附加新元素,使成为40 33 30 23 22 20 17 12 22 30 18
	cout << "iv.push_back(22)" << endl;;
	iv.push_back(22);
	cout << "iv.push_back(30)" << endl;
	iv.push_back(30);
	cout << "iv.push_back(17)" << endl;
	iv.push_back(17);
	cout << "new vector:";
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;
	
	cout << endl;
	//排序，并保持"原相对位置"
	cout << "排序，并保持" << "原相对位置: "; 
	stable_sort(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	
	cout << endl;
	//面对一个有序区间，找出其中的一个子区间，其内每个元素都与某特定元素值相同;
	//返回该子区间的头尾迭代器
	//如果没有这样的子区间，返回的头尾迭代器均指向该特定元素可插入
	//(并仍保持排序)的地点
	cout << "pair<vector<int>::iterator, vector<int>::iterator> pairIte :" << endl;
	pair<vector<int>::iterator, vector<int>::iterator> pairIte;
	pairIte = equal_range(iv.begin(), iv.end(), 22);
	cout << "*(pairIte.first):";
	cout << *(pairIte.first) << endl;//22 lower_bound
	cout << "*(pairIte.second):";
	cout << *(pairIte.second) << endl;//23 upper_bound
	cout << endl;

	cout << "pairIte = rqual_range(iv.begin(), iv.end(), 25):" << endl;
	pairIte = equal_range(iv.begin(), iv.end(), 25);
	cout << "*(pairIte.first):"; 
	cout << *(pairIte.first) << endl; //30 lower_bound
	cout << "*(pairIte.second):";
	cout << *(pairIte.second) << endl << endl;//30 upper_bound

	cout << "random_shuffle(iv.begin(), iv.end()):";
	random_shuffle(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;

	//将小于*(iv.begin() + 5)(本例为)的元素置于该元素之左
	//其余置于该元素之右。不保证维持原有的相对位置

	/*
	cout << "iv.begin():";
	sort(iv.begin(), iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;
	*/

	cout << "nth_element(iv.begin(), iv.begin() + 5, iv.end()):";
	nth_element(iv.begin(), iv.begin() + 5, iv.end());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;

	//将大于*(iv.begin() + 5)(本例为)的元素置于该元素之左
	//其余置于该元素之右。不保证维持原有的相对位置
	cout << "nth_element(iv.begin(), iv.begin() + 5, iv.end(), greater<int>()):";
	nth_element(iv.begin(), iv.begin() + 5, iv.end(), greater<int>());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;

	//以"是否符合even()条件"为依据,将符合者置于左段，不符合者置于右段
	//保证维持原有的相对位置。如不需要"维持原有的相对位置"，可改用partition()
	cout << "stable_partition(iv.begin(), iv.end(), even()):";
	stable_partition(iv.begin(), iv.end(), even());
	copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));
	cout << endl << endl;

}
