

/*
 * Date:2021-08-17 10:59
 * filename:04_算法的泛化过程.cpp
 *
 */

/*
 * 要写一个find()函数，在array中寻找特定值
 */
namespace version_1_find {
	int* find(int* arrayHead, int arraySize, int value) {
		for (int i = 0; i < arraySize; ++i) 
			if (arrayHead[i] == value)
				break;
		return &(arrayHead[i]);
	}
}

/*
 * 该函数在某个区间内查找value.返回的是一个指针，指向它所找到的第一个符合条件的元素;
 * 如果没有找到，就返回最后一个元素的下一位置(地址)
 *
 */

namespace version_2_find {
	const int arraySize = 7;
	int ia[arraySize] = { 0, 1, 2, 3, 4, 5, 6 };
	int* end = ia + arraySize;//最后元素的下一位置

	int* ip = find(ia, sizeof(ia) / sizeof(int), 4);

	if (ip == end)
		cout << "4 not found" << endl;
	else
		cout << "4 found" << endl;
}

/*
 * 这种find()的做法暴露了容器太多的实现细节(例如arraySize),也因此太依附特定容器
 * 为了让find()适用于所有类型的容器，其操作应该更抽象化些
 * 让find()接受两个指针作为参数，标示出一个操作区间
 */

namespace version_3_find {
	int* find(int* begin, int*end, int value) {
		while (begin != end && *begin != value)
			++begin;
		return begin;
	}
}
/*
 * 这个函数在"前闭后开"区间[begin, end)内(不含end;end指向array最后元素的下一位置)查找value,
 * 并返回一个指针，指向它所找到的第一个符合条件的元素
 * 如果没有找到，就返回end.
 */
namespace version_1_find_use {
	const int arraySize = 7;
	int ia[arraySize] = {0, 1, 2, 3, 4, 5, 6};
	int* end = ia + arraySize;

	int* ip = find(ia, end, 4);
	if (ip == end) {
		cout << "4 not found" << endl;
	}
	else
		cout << "4 found" << *ip << endl;

	namespace use_2 {
		/*
		 * find() 函数也可以方便查找array的子区间
		 */
		int* ip = find(ia + 2, ia + 5, 3);
		if (ip == end)
			cout << "3 not found" << endl;
		else 
			cout << "3 found" << endl;
	}

}

/*
 * 由于find()函数之内并无任何操作是针对特定的整数array而发的，所以我们可将它改成一个template:
 */
namespace version_4_find {
	template<typename T>
		T* find(T* begin, T* end, const T& value) {
			while (begin != end && *begin != value)
				++begin;

			//返回操作会引发copy行为
			return begin;
		}
}

/*
 * 数值的传递由pass-by-value改为pass-by-reference-to-const
 * 因为如今所传递的value,其型别可为任意;于是对象一大，传递成本便会提升
 * pass-by-reference可避免这些成本
 */

/*
 * 设计一个calss,拥有原生指针的行为，并使其"++"操作指向list的下一个节点，那么find()就可以施行与list容器身上了
 * 迭代器是一种行为类似指针的对象，是一种smart pointers
 * 现在将find()函数的指针以迭代器取代
 */

namespace version_good_find {
	template <class Iterator, class T>
		Iterator find(Iterator begin, Iterator end, const T& value) {
			while (begin != end && *begin != value)
				++begin;
			return begin;
		}
}

/*
 * 这便是完全泛型化的find()函数
 */


