

/*
 * Date:2021-05-22 15:37
 * filename:12-__type_traits.cpp
 *
 */

/*
 * iterator_traits负责萃取迭代器的特性,__type_traits则负责萃取型别(type)的特性
 * 此处我们所关系的型别特性是指:
 * 这个型别是否具备non-trivial defalt ctor?
 * 是否具备non-trivial copy ctor?
 * 是否具备 non-trivial assignment operator?
 * 是否具备non-trivial dtor?
 * 如果答案是否定的,我们对这个型别进行构造、析构、拷贝、赋值等操作时，就可以采用最有效率的措施
 * 而采用内存直接处理操作malloc(),memcpy()
 */

__type_traits<T>::has_trivial_default_constructor
__type_traits<T>::has_trivial_copy_constructor
__type_traits<T>::has_trivial_assignment_operator
__type_traits<T>::has_trivial_destructor
__type_traits<T>::is_POD_type

template <class type>
struct __type_traits {
	typedef __true_type this_dummy_member_must_be_first;
	typedef __false_type has_trivial_default_constructor;
	typedef __false_type has_trivial_copy_constructor;
	typedef __false_type has_trivial_assignment_operator;
	typedef __false_type has_trivial_destructor;
	typedef __false_type is_POD_type;
};


