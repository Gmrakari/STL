/*
 * Date:2021-04-20 20:44
 * file __STL_NULL_TMPL_ARGS(bound friend template friend)
 */


#ifdef __STL_EXPLICIT_FUNCTION_TMPL_ARGS
#define __STL_NULL_TMPL_ARGS <>
#else
#define __STL_NULL_TMPL_ARGS
#endif

//occur in this occasion:class template's friend function declaration

//in <stl_stack.h>
template <class T,class Sequence = deque<T>>
class stack
{
	friend bool operator==__STL_NULL_TMPL_ARGS(const stack&,const stack&);
	friend bool operator<__STL_NULL_TMPL_ARGS(const stack&,const stack&);
	...
};

//展开后
template<class T,class Sequence = deque<T>>
class stack
{
	friend bool operator== <>(const stack&,const stack&);
	friend bool operator< <> (const stack&,const stack&);
	...
};


