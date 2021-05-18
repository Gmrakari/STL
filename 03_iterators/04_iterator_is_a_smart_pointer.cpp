

/*
 * Date:2021-05-18 20:11
 * filename:04_iterator_is_a_smart_pointer.cpp
 *
 */

/*
 * 迭代器是一种行为类似指针的对象，而指针的各种行为中最常见也最重要的便是内容提领(dereference)和成员访问(member access)
 * 迭代器最重要的编程工程就是对operator*和operator->进行重载(overloading)工作
 *
 * c++标准程序库有一个auto_ptr,这是一个用来包装原生指针(native pointer)的对象,声名狼藉的内存漏洞(memory leak)问题可藉此获得解决
 * auto_ptr的用法如下,和原生指针一模一样:
 */
void func()
{
	auto_ptr<string> ps(new string("jjhou"));
	
	cout << *ps << endl; // cout: jjhou;
	cout << ps->size() << endl; // cout:5
	//离开前不需delete,auto_ptr会自动释放
}

//函数第一行的意思是,以算式new动态配置一个初值为"jjhou"的string对象,并将所得结果(一个原生指针)作为auto_ptr<string>对象的初值。
//auto_ptr角括号内放的是"原生指针所指对象"的型别,而不是原生指针的型别

