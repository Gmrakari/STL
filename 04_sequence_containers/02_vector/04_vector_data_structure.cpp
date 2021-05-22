

/*
 * Date:2021-05-22 16:37
 * filename:04_vector_data_structure.cpp
 *
 */

/*
 * 线性连续空间。它以两个迭代器start和finish分别指向配置得来的连续空间种目前已被使用的范围
 * 并以迭代器end_of_storage指向整块连续空间(含备用空间)的尾端:
 */

#include <vector>

template <class T, class Alloc = alloc>
class vector {
public:
	typedef T						value_type;
	typedef value_type* iterator;
	typedef size_t			size_type;
protected:
	iterator start;
	iterator finish;
	iterator end_of_storage;


	iterator begin() { return start; }
	iterator end() { return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const {
		return size_type(end_of_storage - begin());
	}
};

/*
 * 为了降低空间配置时的速度成本，vector实际配置的大小可能比客户端需求量更大一些
 * 以备将来可能的扩充。这便是容量(capacity)的观念
 * 一个vector的容量永远大于或等于其大小
 * 一旦容量等于大小，便是满载,下次再有新增元素，整个vector就得另觅居所
 *
 * 运用start,finish,end_of_storage三个迭代器，便可轻易地提供首尾标示
 * 大小,容量,空容器判断,主标运算子,最前端元素值,最后端元素值等几机能
 */

