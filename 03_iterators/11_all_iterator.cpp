

/*
 * Date:2021-05-21 16:33
 * filename:11_all_iterator.cpp
 *
 */

//by SGI STL <stl_iterator.h>

struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

//为避免写代码时挂一漏万，自行开发的迭代器最好继承自下面的std::iterator
struct iterator {
	typedef Category	 iterator_category;
	typedef T					 value_type;
	typedef Distance	 difference_type;
	typedef Pointer		 pointer;
	typedef Reference	 reference;
};

//traits
template <class T>
struct iterator_traits<T*>{
	typedef random_access_iterator_tag iterator_category;
	typedef T													 value_type;
	typedef ptrdiff_t									 difference_type;
	typedef T*												 pointer;
	typedef T&												 reference;
};

//pointer-to-const traits
struct iterator_traits<const T*>{
	typedef random_access_iterator_tag iterator_category;
	typedef T													 value_type;
	typedef ptrdiff_t									 difference_type;
	typedef const T*									 pointer;
	typedef const T&									 reference;
};

//category
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&) {
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}

//distance type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

//distance
template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last) {
		++first;++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline iterator_traits<RandomAccessIterator>::difference_type
__distance(InputIterator first, RandomAccessIterator last, random_access_iterator_tag) {
	return last - frist;
}

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
distance(InputIterator first,InputIterator last) {
	typedef typename iterator_traits<InputIterator>::iterator_category category;
	return __distance(first, last, category());
}

//advance fun
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
	while (n--) ++i;
}

template <class BidiectionalIterator, class Distance>
inline void __advance(BidiectionalIterator& i, Distance n, bidirectional_iterator_tag) {
	//双向，逐一前进
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag) {
	i += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n) {
	__advance(i, n, iterator_traits<InputIterator>::iterator_category(i));
}
