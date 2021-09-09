

/*
 * Date:2021-09-09 11:23
 * filename:02_Insert_Iterators.cpp
 *
 */

/*
 * Insert Iterators 可以将一般迭代器的赋值(assign)操作转变为插入(insert)操作
 * 这样的迭代器包括专司尾端插入操作的back_insert_iterator,
 * 专司头端插入操作的front_insert_iterator,以及可从任意位置执行插入操作的insert_iterator
 * 由于这三个iterator adapters的使用接口不是十分直观，给一般用户带来困扰
 * STL就提供相应的函数:back_inserter()、front_inserter()、inserter()
 *
 * back_inserter(Container& x) -> back_insert_iterator<Container>(x);
 *
 * front_inserter(Container& x) -> front_insert_iterator<Container>(x);
 *
 * inserter(Container& x, Iterator i) -> insert_iterator<Container>(x, Container::iterator(i));
 *
 */
