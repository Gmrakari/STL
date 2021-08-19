

/*
 * Date:2021-08-19 10:25
 * filename:03_copy-test.cpp
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <cstring>
using namespace std;

class C {
public:
	C() : _data(3) {}
	//there is a trivial assignment operator
	//没有意义的赋值拷贝操作
private:
	int _data;
};

int main() {
	//test-1
	cout << "test-1:" << endl;
	const char ccs[5] = {'a', 'b', 'c', 'd', 'e'};//数据来源
	char ccd[5];
	cout << "ccs[5]:" ;
	for (int i = 0; i < 5; ++i) {
		cout << ccs[i] << ' ';
	}
	cout << endl;

	copy(ccs, ccs + 5, ccd);
	//调用copy(const char*)
	int ccd_len = sizeof(ccd) / sizeof(ccd[0]);
	cout << "调用copy(const char*):";
	for (int i = 0; i < ccd_len; i++) {
		cout << ccd[i] << ' ';
	}
	cout << endl << endl;


	//test-2
	cout << "test-2:" << endl;
	const wchar_t cwcs[5] = {'a', 'b', 'c', 'd', 'e'};//数据来源
	cout << "cwcs[5]:";
	for (int i = 0; i < 5; ++i) {
		cout << cwcs[i] << ' ';
	}
	cout << endl;
	wchar_t cwcd[5];
	copy(cwcs, cwcs + 5, cwcd);
	//调用copy(const wchar_t*)
	int cwcd_len = sizeof(cwcd) / sizeof(cwcd[0]);
	cout << "调用copy(const wchar_t*):";
	for (int i = 0; i < cwcd_len; i++) {
		cout << cwcd[i] << ' ';
	}
	cout << endl << endl;

	//test-3
	cout << "test-3:" << endl;
	int ia[5] = {0, 1, 2, 3, 4};

	cout << "ia[5]:";
	for (int i : ia) {
		cout << i << ' ';
	}
	cout << endl;

	copy(ia, ia + 5, ia); //允许来源去处相同
	/*
	 * copy()
	 *	__copy_dispatch(T*, T*)
	 *	__copy_t(__true_type)
	 */
	cout << "copy():";
	for (int i : ia) {
		cout << i << ' ';
	}
	cout << endl << endl;

	//test-4
	cout << "test-4:" << endl;
	//list迭代器被归类为InputIterator
	list<int> ilists(ia, ia + 5);	//数据来源
	list<int> ilistd(5);					//数据去处

	cout << "ilist:";
	for (auto i : ilists) {
		cout << i << ' ';
	}
	cout << endl;

	copy(ilists.begin(), ilists.end(), ilistd.begin());
	//调用版本	
	/*
	 * copy()
	 *	__copy_dispatch()
	 *	__copy_t(input_iterator)
	 */
	
	cout << "ilistd:";
	for (auto i : ilistd) {
		cout << i << ' ';
	}
	cout << endl << endl;

	//test-5
	cout << "test-5:" << endl;

	//vector迭代器被归类为原生指针(native pointer)
	vector<int> ivecs(ia, ia + 5);//数据来源
	//为什么会产生输出信息
	auto ivec_ite_begin = ivecs.begin();
	auto ivec_ite_end = ivecs.end();
	cout << "ivecs:";
	for (; ivec_ite_begin != ivec_ite_end; ivec_ite_begin++) {
		cout << *ivec_ite_begin << ' ';
	}
	cout << endl;
	
	vector<int> ivecd(5);				//数据去处
	copy(ivecs.begin(), ivecs.end(), ivecd.begin());
	/*
	 * copy()
	 *	__copy_dispatch(T*, T*)
	 *	__copy_t(_true_type)
	 *
	 *	以上的是否合理
	 *	copy()
	 *		__copy_dispatch()
	 *		__copy(random_access_iterator)
	 *		__copy_d()
	 */
	cout << "copy ivecd:";

	for (auto i : ivecd) {
		cout << i << ' ';
	}
	cout << endl << endl;

	//test-6
	cout << "test-6:" << endl;
	//class C具备trivial operator=
	C c[5];
	vector<C> Cvs(c, c + 5);//数据来源
	//产生数据输出
	
//	auto cvs_ite_begin = Cvs.begin();

	vector<C> Cvd(5);//数据去处
	copy(Cvs.begin(), Cvs.end(), Cvd.begin());
	//	copy()
	//		__copy_dispatch(T* ,T*) //这是否合理?不是randwom_access_iterator?
	//		__copy_t(__false_type) // ? __true_type?
	//		__copy_d()
	
	cout << endl;

	//test-7
	cout << "test-7:" << endl;
	//deque迭代器被归类为random access iterator
	deque<C> Cds(c, c + 5);//数据来源
	deque<C> Cdd(5);				//数据去处	
	copy(Cds.begin(), Cds.end(), Cdd.begin());
	// copy()
	//	__copy_dispatch()
	//	__copy(random_access_iterator)
	//	__copy_d()
	
	cout << endl;

	//test-8
	cout << "test-8:" << endl;
	//class String定义
	vector<string> strvs(5);//数据来源
	vector<string> strvd(5);//数据去处

	strvs[0] = "jjhou";
	strvs[1] = "grace";
	strvs[2] = "david";
	strvs[3] = "jason";
	strvs[4] = "jerry";

	copy(strvs.begin(), strvs.end(), strvd.begin());
	//	copy()
	//		__copy_dispatch(T*, T*) //合理? random_access_iterator?
	//		__copy_t(__false_type) //合理,string确实是__false_type
	//		__copy_d()
	
	cout << endl;

	//test-9
	cout << "test-9:" << endl;
	deque<string> strds(5);//数据来源
	deque<string> strdd(5);//数据去处

	strds.push_back("jjhou");
	strds.push_back("grace");
	strds.push_back("david");
	strds.push_back("jason");
	strds.push_back("jerry");
	copy(strds.begin(), strds.end(), strdd.begin());
	//	copy()
	//	 __copy_dispatch()
	//	 __copy(random_access_iterator)
	//	 __copy_t()
	
	//详解见P324-325
	//涉及vector ctor
	//
	//二:编译器之中，有能力验证"用户自定义型别"之型别特性者极少
	//如果确知某个class具备的是trivial ctor/dtor/operator=
	//我们就得自己动手为它做特性设定，才能保证编译器知道它的身份
	//
}


