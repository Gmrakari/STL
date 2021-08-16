

/*
 * Date:2021-08-16 17:06
 * filename:08_hastset-test.cpp
 *
 */
#include <iostream>
#include <cstring>
using namespace std;

struct eqstr {
	bool operator() (const char* s1, const char* s2) const {
		return strcmp(s1, s2) == 0;
	}
};

void lookup(const hash_set<const char*, hash<const char*>, eqstra>& Set, const char* word) {
	hash_set<const char*, hash<const char*>, eqstr>::const_iterator it = Set.find(word);

	cout << " " << word << ":" << (it != Set.end() ? "present" : "not present") << endl;
}


int main() {
	hash_set<const char*, hash<const char*>, eqstr> Set;
	Set.insert("kiwi");
	Set.insert("plum");
	Set.insert("apple");
	Set.insert("mango");
	Set.insert("apricot");
	Set.insert("banana");

	lookup(Set, "mango");// mango:present
	lookup(Set, "apple");// apple:present
	lookup(Set, "durian");// durian : not present

	hash_set<const char*, hash<const char*>, eqstr>::iterator ite1 = Set.begin();
	hash_set<const char*, hash<const char*>, eqstr>::iterator ite2 = Set.end();

	for (; ite1 != ite2;++ite1) {
		cout << *ite1 << ' '; //banana plum mango apple kiwi apricot
	}

	/*
	 * 最后得出的结果显示 字符串并没有排序
	 */
	
	hash_set<int> Set;
	Set.insert(59);
	Set.insert(63);
	Set.insert(108);
	Set.insert(2);
	Set.insert(53);
	Set.insert(55);

	hash_set<int>::iterator ite1 = Set.begin();
	hash_set<int>::iterator ite1 = Set.end();

	for (; ite1 != ite2; ++ite1) 
		cout << *ite1 << ' ';//2 53 55 59 63 108
	cout << endl;

	/*
	 * 结果跟const char* 不同，int结果是排序好的
	 * 答案是,hashtable大小被指定为50,而这里所使用的hast_set缺省情况下
	 * 指定hashtable的大小为100,由于buckets够多，才造成排序假象。
	 * 如果以下面这样的次序输入这些值 就是无序的状态了
	 */

	hash_set<int> Set;
	Set.insert(3);
	Set.insert(196);
	Set.insert(1);
	Set.insert(389);
	Set.insert(194);
	Set.insert(387);

	hash_set<int>::iterator ite1 = Set.begin();
	hash_set<int>::iterator ite1 = Set.end();

	for (; ite1 != ite2; ++ite1) 
		cout << *ite1 << ' ';//387 194 1 389 196 3
	cout << endl;
}
