
/*
 * Date:2021-04-21 10:40
 * file:class template explicit specialization
 */

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
#	define __STL_TEMPLATE_NULL template<>
#else
#	define __STL_TEMPLATE_NULL
#endif

//in <type_traits.h>
template <class Type> struct __type_traits { ... };
__STL_TEMPLATE_NULL struct __type_traits<char> { ... };

//in <stl_hash_fun.h>
template <class Key> struct hash { };
__STL_TEMPLATE_NULL struct hash<char> { ... };
__STL_TEMPLATE_NULL struct hash<unsigned char> { ... };

//展开后

template <class type> struct __type_traits { ... };
template<> struct __type_traits<char> { ... };


template <class Key> struct hash { };
template<> struct hash<char> { ... };
template<> struct hash<unsigned char> { ... };


