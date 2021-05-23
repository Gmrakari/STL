

/*
 * Date:2021-05-23 15:55
 * filename:05_vector-test.cpp
 *
 */

//05_vector_constructor-push_back.cpp

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	vector<int> iv(2,9);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0; i < int(iv.size());i++)
		cout << iv[i] << ' ';
	cout << endl;

	iv.push_back(1);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(2);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(3);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(4);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.push_back(5);

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0;i < (int)iv.size();++i) {
		cout << iv[i] << ' ';
	}
	cout << endl;

	iv.pop_back();
	iv.pop_back();

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	iv.pop_back();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	vector<int>::iterator ivite = find(iv.begin(),iv.end(),1);
	if (ivite != iv.end()) iv.erase(ivite);
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;

	for (int i = 0; i < int(iv.size());++i)
		cout << iv[i] << ' ';
	cout << endl;

	ivite = find(iv.begin(),iv.end(),2);

	if (ivite != iv.end()) iv.insert(ivite,3,7);

	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	for (int i = 0; i < int(iv.size());++i)
		cout << iv[i] << ' ';
	cout << endl;

	iv.clear();
	cout << "size = " << iv.size() << endl;
	cout << "capacity = " << iv.capacity() << endl;
	return 0;
}

/*
 * vector 缺省使用alloc作为空间配置器，并据此另外定义了一个data_allocator,为的是更方便以元素大小为配置单位:
 */
template <class T,class Alloc = alloc>
class vector {
protected:
	typedef simple_alloc<value_type,Alloc> data_allocator;
};

/*
 * 于是,data_allocator:allocate(n) 表示配置n个元素空间
 *
 * vector 提供许多constructors,其中一个允许我们指定空间大小及初值:
 */
//构造函数允许指定vector大小n和初值value
vector(size_type n,const T& value) { fill_initialize(n, value); }

//填充并予初始化
void fill_initialize(size_type n,const T& value) {
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;
}

//配置而后填充
iterator allocate_and_fill(size_type n, const T& x) {
	iterator result = data_allocator::allocate(n);		//配置n个元素空间
	uninitialized_fill_n(result, n, x);
	return result;
}

/*
 * uninitialized_fill_n() 会根据第一参数的型别特性(type traits),
 * 决定使用算法fill_n()或反复调用construct()来完成任务
 *
 * 当我们以push_back将新元素插入于vector尾端时，该函数首先检查是否还有备用空间,
 * 如果有就直接在备用空间上构造元素并调整迭代器finish,使vector变大。
 * 如果没有备用空间了，就扩充空间(重新配置、移动数据、释放原空间)
 *
 */
void push_back(const T& x) {
	if (finish != end_of_storage) {		//还有备用空间
		construct(finish, x);						
		++finish;												//调整水位
	}
	else															//已无备用空间
		insert_aux(end(), x);
}

template <class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x) {
	if (finish != end_of_storage) {							//还有备用空间
		// 在备用空间起始处构造一个元素，并以vector最后一个元素值为其初值
		construct(finish, *(finish - 1));
		//调整水位
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;
	}
	else {	//已无备用空间
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;

		//以上配置原则:如果原大小为0，则配置1(个元素大小);
		//如果原大小不为0，则配置原大小的两倍
		//前半段用来放置原数据，后半段准备用来放置新数据

		iterator new_start = data_allocator::allocate(len);	//实际配置
		iterator new_finish = new_start;
		try {
			//将原vector的内容拷贝到新vector
			new_finish = uninitialized_copy(start, position, new_start);
			//为新元素设置初值x
			construct(new_finish, x);
			//调整水位
			++new_finish;
			//将安插点的原内容也拷贝过来
			new_finish = uninitialized_copy(position, finish, new_finish);
		}
		catch(...) {
			//"commit or rollback" semantics
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}

		//析构并释放原vector
		destroy(begin(),end());
		deallocate();

		//调整迭代器,指向新vector
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

/*
 * 所谓动态增加大小，并不是在原空间之后接续新空间(因为无法保证原空间之后尚有可供配置的空间),
 * 而是以原大小的两倍另外配置一块较大空间,然后将原内容拷贝过来，然后才开始在原内容之后构造新元素
 * 并释放原空间。因此，对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器都失效了
 */






