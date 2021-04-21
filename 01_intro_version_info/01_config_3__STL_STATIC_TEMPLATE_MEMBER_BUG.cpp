#include <iostream>
using namespace std;

//测试在class template 中拥有 static data members

template<typename T>
class testClass
{
public:
	static int _data;
};

//为static data members 进行定义(配置内存),并设初值
template<> int testClass<int>::_data = 1;
template<> int testClass<char>::_data = 2;

int main()
{
	cout << testClass<int>::_data << endl;
	cout << testClass<int>::_data << endl;

	testClass<int> obji1,obji2;
	testClass<char> objc1,objc2;

	cout << obji1._data << endl;
	cout << obji2._data << endl;
	cout << objc1._data << endl;
	cout << objc2._data << endl;

	obji1._data = 3;
	objc2._data = 4;

	cout << obji1._data << endl;
	cout << obji2._data << endl;
	cout << objc1._data << endl;
	cout << objc2._data << endl;


}


