

/*
 * Date:2021-07-21 15:48
 * filename:01_slist-intro.cpp
 *
 */

/*
 * STL list是一个双向链表(double linked list).
 * SGI STL 另提供了一个单向链表（single linked list),名为slist
 *
 * slist和list的主要差别在于，前者的迭代器属于单向的Forward iterator,
 * 后者的迭代器属于双向爱那个的Bidirectional iterator
 *
 * 为此，slist的功能自然也收到限制很多，不过单向链表所耗用的空间更少，某些操作更快
 *
 * slist和list共同具有一个相同特色是,他们的插入(insert),移除(erase),接合(splice)等操作并不会造成原有的迭代器失效
 *
 * 注意 根据STL的习惯，插入操作会将新元素插入于指定位置之前，而非之后
 *
 * 然而作为一个单向链表，slist没有任何方便的办法可以回头定出前一个位置，因此它必须从头找起
 *
 * slist提供insert_after() 和 erase_after()
 *
 * slist不提供push_back(),只提供push_front()，因此slist的元素次序会和元素插入进来的次序相反
 *
 */


