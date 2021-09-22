

/*
 * Date:2021-09-22 21:11
 * filename:08_用于成员函数指针_mem_fun_mem_fun_ref.cpp
 *
 */

/*
 * 这种配接器使我们能够将成员函数(member funcitons)当作仿函数来使用，
 * 于是成员函数可以搭配各种泛型算法。当容器的元素型式是X&或者X*，而我们又
 * 一虚拟(virtual)成员函数作为仿函数，便可以藉由泛型算法完成所谓的多态调用(polymorphic function call)
 * 这是泛型(genericity)与多态(polymorphism)之间的一个重要接轨
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Shape {
public:
	virtual void display() = 0;
};

class Rect : public Shape {
public:
	virtual void display() {
		cout << "Rect ";
	}
};

class Circle : public Shape {
public:
	virtual void display() {
		cout << "Circle ";
	}
};

class Square : public Rect {
public:
	virtual void display() {
		cout << "Square ";
	}
};

int main() {
	vector<Shape*> V;

	V.push_back(new Rect);
	V.push_back(new Circle);
	V.push_back(new Square);
	V.push_back(new Circle);
	V.push_back(new Rect);

	//polymorphically
	for(int i = 0; i < V.size(); ++i) 
		(V[i])->display();
	cout << endl;

	//polymorphically
	for_each(V.begin(), V.end(), mem_fun(&Shape::display));
	cout << endl;
	
}

/*
 * 一定要以适配器mem_fun修饰member function,才能被算法for_each接受。
 * 虽然多态(polymorphism)可以对pointer或reference起作用，但很可惜的是，STL容器只支持
 * "实值语意"(value semantic)，不支持"引用语意"(reference semantics)
