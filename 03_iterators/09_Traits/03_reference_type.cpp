

/*
 * Date:2021-05-20 20:46
 * filename:03_reference_type.cpp
 *
 */

/*
 * 从"迭代器所指之物的内容是否允许改变"的角度看,迭代器分两种:
 * 不允许改变"所指对象之内容"者,称为constant iterators,例如 const int* pic;
 * 允许改变"所指对象之内容"者,称之为mutable iterators,例如 int* pi
 * 当我们对一个mutable iterators 进行提领操作时，获得不应该是一个右值(rvalue),
 * 应该是一个左值(lvalue),因为右值不允许赋值操作(assignment),左值才允许:
 */
int* pi = new int(5);
const int* pic = new int(9);

*pi = 7;//对mutable iterators进行提领操作时，获得的应该是个左值,允许赋值
*pic = 1;//这个操作不允许,因为pic是个constant iterator,提领pic所得结果，是个右值,不允许被赋值

/*
 * 在C++，函数如果要传回左值,都是以by reference的方式进行，所以当p是个mutable iterators,
 * 如果其value type 是个T,那么*p的型别不应该是T,应该是T&
 * 将此道理扩充,如果p是一个constant iterators,其value type是T,那么*p的型别不应该是const T,
 * 而应该是const T&.这里所讨论的*p的型别，即所谓的reference type
 */
