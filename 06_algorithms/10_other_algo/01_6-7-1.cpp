

/*
 * Date:2021-08-20 10:01
 * filename:01_6-7-1.cpp
 *
 */

#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

template <class T>
struct display {
	void operator()(const T& x) const {
		cout << x << ' ';
	}
};

struct even {
	bool operator()(int x) const {
		return x % 2 ? false : true;
	}
};

class even_by_two {
public:
	int operator()() const {
		return _x += 2;
	}
private:
	static int _x;
};

int even_by_two::_x = 0;

int main() {
	int ia[] = {0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8};
	vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

	cout << "iv:";
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//找出iv之中相邻元素值相等的第一个元素
	cout << "找出iv之中相邻元素值相等的第一个元素:";
	cout << *adjacent_find(iv.begin(), iv.end()) << endl;

	//找出iv之中相邻元素值相等的第一个元素
	cout << "找出iv之中相邻元素值相等的第一个元素 equal_to<int>():";
	cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl;

	//找出iv之中元素值为6的元素个数
	cout << "找出iv之中元素值为6的元素个数:";
	cout << count(iv.begin(), iv.end(), 6) << endl;

	///找出iv之中小于7的元素个数
	cout << "找出iv之中小于7的元素个数:";
	cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) << endl;

	//找出iv之中元素值为4的第一个元素所在位置的值
	cout << "找出iv之中元素值为4的第一个元素所在位置的值:";
	cout << *find(iv.begin(), iv.end(), 4) << endl;//4

	//找出iv之中大于2的第一个元素的所在位置的值
	cout << "找出iv之中大于2的第一个元素的所在位置的值:";
	cout << *find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) << endl;

	//找出iv之中子序列iv2所出现的最后一个位置(再往后3个位置的值)
	cout << "找出iv之中子序列iv2所出现的最后一个位置(再往后3个位置的值):";
	vector<int> iv2(ia + 6, ia + 8);//{6, 6};
	cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3) << endl; //{6,6,6,7,8} [0]=6, [1]=6, [2]=6,[3]=8;

	//找出iv之中子序列iv所出现的第一个位置(再往后3个位置的值)
	cout << "找出iv之中子序列iv所出现的第一个位置(再往后3个位置的值):";
	cout << *(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end()) + 3) << endl;

	//迭代遍历整个iv区间，对每一个元素施行display操作(不得改变元素内容)
	cout << "迭代遍历整个iv区间，对每一个元素施行display操作(不得改变元素内容):";
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	cout << "iv2:";
	for_each(iv2.begin(), iv2.end(), display<int>());	
	cout << endl;

	cout << "generate:";
	generate(iv2.begin(), iv2.end(), even_by_two());
	for_each(iv2.begin(), iv2.end(), display<int>());
	cout << endl;

	//迭代遍历指定区间(起点与长度),对每个元素施行even_by_two操作(得改变元素值)
	cout << "迭代遍历指定区间(起点与长度),对每个元素施行even_by_two操作(得改变元素值):";
	generate_n(iv.begin(), 3, even_by_two());//上面_x = 4,现在执行3次变成 6 8 10
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//删除(但不删除)元素6,。尾端可能有残余数据(可另以容器之erase函数去除之)
	cout << "删除(但不删除)元素6,。尾端可能有残余数据(可另以容器之erase函数去除之):";
	remove(iv.begin(), iv.end(), 6);
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//删除(但不删除)元素6.结果置于另一区间
	cout << "删除(但不删除)元素6.结果置于另一区间:";
	vector<int> iv3(12);
	remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
	for_each(iv3.begin(), iv3.end(), display<int>());
	cout << endl;

	//删除(但不删除)小于6的元素。尾端可能有残留数据
	cout << "删除(但不删除)小于6的元素。尾端可能有残留数据:";
	remove_if(iv.begin(), iv.end(), bind2nd(less<int>(), 6));
	for_each(iv.begin(), iv.end(), display<int>()); //8 10 7 8 6 6 7 8 (6 7 8)
	cout << endl;

	//删除(但不删除)小于7的元素。结果置于另一区间
	cout << "删除(但不删除)小于7的元素。结果置于另一区间:";
	remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
	for_each(iv3.begin(), iv3.end(), display<int>());//(8 0 0 0)
	cout << endl;

	//将所有的元素6,改为元素值3
	cout << "将所有的元素6,改为元素值3:";
	replace(iv.begin(), iv.end(), 6, 3);
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//将所有的元素值3,改为元素值5。结果置于另一区间
	cout << "将所有的元素值3,改为元素值5。结果置于另一区间:";
	replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
	for_each(iv3.begin(), iv3.end(), display<int>());//结果多出一个0
	cout << endl;

	//将所有小于5的元素值，改为元素值2
	cout << "将所有小于5的元素值，改为元素值2:";
	replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//将所有等于8的元素值，改为元素值9.结果置于另一区间
	cout << "将所有等于8的元素值，改为元素值9.结果置于另一区间:";
	replace_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(equal_to<int>(), 8), 9);
	for_each(iv3.begin(), iv3.end(), display<int>());//结果多出一个0
	cout << endl;

	//逆向重排每一个元素
	cout << "逆向重排每一个元素:";
	reverse(iv.begin(), iv.end());
	for_each(iv.begin(), iv.end(), display<int>());
	cout << endl;

	//逆向重排每一个元素，结果置于另一区间
	cout << "逆向重排每一个元素，结果置于另一区间:";
	reverse_copy(iv.begin(), iv.end(), iv3.begin());
	for_each(iv3.begin(), iv3.end(), display<int>()); //多出一个0
	cout << endl;
	
	//旋转(互换元素)[first, middle) 和 [middle, last)
	cout << "旋转(互换元素)[first, middle) 和 [middle, last):";
	rotate(iv.begin(), iv.begin() + 4, iv.end());
	for_each(iv.begin(), iv.end(), display<int>());//从第四个元素开始4个,放到前面，其余的不变 即72287 放在前面 后面顺序不变
	cout << endl;

	//旋转(互换元素)[first, middle) 和[middle, last)，结果置于另一区间
	cout << "旋转(互换元素)[first, middle) 和[middle, last)，结果置于另一区间:";
	rotate_copy(iv.begin(), iv.begin() + 5, iv.end(), iv3.begin());
	for_each(iv3.begin(), iv3.end(), display<int>()); //多出一个0
	cout << endl;
	
	//查找某个子序列的第一次出现地点
	cout << "查找某个子序列的第一次出现地点:";
	int ia2[3] = {2, 8};
	vector<int> iv4(ia2, ia2 + 2);//iv4:{2, 8}
	cout << *search(iv.begin(), iv.end(), iv4.begin(), iv4.end()) << endl;

	//查找连续出现2个8的子序列起点
	cout << "查找连续出现2个8的子序列起点:";
	cout << *search_n(iv.begin(), iv.end(), 2, 8) << endl;

	//查找连续出现3个不小于8的子序列起点
	cout << "查找连续出现3个不小于8的子序列起点:";
	cout << *search_n(iv.begin(), iv.end(), 3, 8, less<int>()) << endl;//7

	//将两个区间内的元素互换。第二区间的元素个数不应小于第一区间的元素个数
	cout << "swap_range:将两个区间内的元素互换。第二区间的元素个数不应小于第一区间的元素个数 iv:" ;
	swap_ranges(iv4.begin(), iv4.end(), iv.begin());
	for_each(iv.begin(), iv.end(), display<int>()); 
	cout << endl;
	cout << "iv4:";
	for_each(iv4.begin(), iv4.end(), display<int>()); 
	cout << endl;

	//改变区间的值，全部减2
	cout << "改变区间的值，全部减2 iv:";
	transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
	for_each(iv.begin(), iv.end(), display<int>()); 
	cout << endl;

	//改变区间的值，令第二区间的元素值加到第一区间的对应元素身上
	//第二区间的元素个数不应小于第一区间的元素个数
	cout << "改变区间的值，令第二区间的元素值加到第一区间的对应元素身上:";
	transform(iv.begin(), iv.end(), iv.begin(), iv.begin(), plus<int>());//想等于*2
	for_each(iv.begin(), iv.end(), display<int>()); 
	cout << endl;

	cout << "----------------------------------------------" << endl << endl;

	vector<int> iv5(ia, ia + sizeof(ia) / sizeof(int));
	vector<int> iv6(ia + 4, ia + 8);
	vector<int> iv7(15);
	cout << "iv5:";
	for_each(iv5.begin(), iv5.end(), display<int>());
	cout << endl;

	cout << "iv6:";
	for_each(iv6.begin(), iv6.end(), display<int>());
	cout << endl;

	cout << "*max_element(iv5.begin(), iv5.end()): " << *max_element(iv5.begin(), iv5.end()) << endl;
	cout << "*min_element(iv5.begin(), iv5.end()): " << *min_element(iv5.begin(), iv5.end()) << endl;

	//判断是否iv6内的所有元素都出现于iv5中
	//注意两个序列都必须是sorted ranges
	cout << "判断是否iv6内的所有元素都出现于iv5中: " << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl;//1

	//将两个序列合并为一个序列
	//两个序列都必须是sorted ranges 获得的结果也是sorted
	cout << "将两个序列合并为一个序列:";
	merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
	for_each(iv7.begin(), iv7.end(), display<int>());
	cout << endl;

	//符合条件的元素放在容器前段，不符合的元素放在后段
	//不保证保留原相对次序
	cout << "符合条件的元素放在容器前段，不符合的元素放在后段 iv7:";
	partition(iv7.begin(), iv7.end(), even());
	for_each(iv7.begin(), iv7.end(), display<int>());
	cout << endl;//0 8 2 6 4 4 6 6 6 6 5 5 3 7 1

	//去除"连续而重复"的元素
	//获得的结果可能有残余数据
	cout << "去除连续而重复的元素:";
	unique(iv5.begin(), iv5.end());
	for_each(iv5.begin(), iv5.end(), display<int>());
	cout << endl;//iv5：0 1 2 3 4 5 6 7 8 (7 8)

	//去除"连续而重复"的元素，将结果置于另一处
	//获得的结果可能有残余数据
	cout << "去除连续而重复的元素，将结果置于另一处:";
	unique_copy(iv5.begin(), iv5.end(), iv7.begin());
	for_each(iv7.begin(), iv7.end(), display<int>());
	cout << endl;//iv7:0 1 2 3 4 5 6 7 8 (7 8 5 3 7 1)
	
	
	
	
}
