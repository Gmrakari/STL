

/*
 * Date:2021-08-18 15:30
 * filename:02_copy-realize.cpp
 *
 */

//完全泛化版本
template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
	return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}

/*
 * 下面两个多载函数，针对原生指针(可视为一种特殊的迭代器)
 * const char*和const wchar_t*,进行内存直接拷贝操作
 */

//version_1
inline char* copy(const char* first, const char* last, char* result) {
	memmove(result, first, last - first);
	return result + (last - first);
}

//version_2
inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result) {
	memmove(result, first, sizeof(wchar_t) * (last - first));
	return result + (last - first);
}

/*
 * copy()函数的泛化版本中调用了一个__copy_dispatch()函数，此函数有一个完全泛化版本和两个偏特化版本:
 *
 */
//完全泛化版本
template <class InputIterator, class OutputIterator>
struct __copy_dispatch {
	OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result) {
		return __copy(first, last, result, iterator_category(first));
	}
};

//偏特化版本1,两个参数都是T*指针形式
template <class T>
struct __copy_dispatch<T*, T*>
{
	T* operator()(T* first, T* last, T* result) {
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
};

//偏特化版本2,第一个参数为const T*指针形式，第二参数为T*指针形式
template <class T>
struct __copy_dispatch<const T*, T*> {
	T* operator() (const T* first, const T* last, T* result) {
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}
};


/*
 * __copy_dispatch()的完全泛化版根据迭代器种类的不同，调用了不同的__copy(),
 * 为的是不同种类的迭代器所使用的循环条件不同,有快慢之别。
 */

//InputIterator 版本
template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag) {
	//以迭代器等同与否，决定循环是否继续。速度慢
	for (; first != last; ++result, ++first)
		*result = *first;
	return result;
}

//RandomAccessIterator 版本
template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last,
		OutputIterator result, random_access_iterator_tag) {
	//又划分出一个函数，为的是其它地方也可能用到
	return __copy_d(first, last, result, distance_type(first));
}

template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last,
		OutputIterator result, Distance*) {
	//以n决定循环的执行次数。速度快
	for (Distance n = last - first; n > 0; --n, ++result, ++first)
		*result = *first;
	return result;
}

/*
 * __copy_t
 */
//以下版本适用于"指针所指之对象具备 trivial assignment operator"
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type) {
	memmove(result, first, sizeof(T) * (last - first));
	return result + (last - first);
} 

// 以下版本适用于"指针所指之对象具备non-trivial assignment operator"
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type) {
	//原声指针毕竟是一种RandomAccessIterator
	memove(result, first, result, (ptrdiff_t)0);
}
