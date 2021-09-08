

/*
 * Date:2021-09-08 20:37
 * filename:01_functors_intro.cpp
 *
 */

/*
 * 仿函数(functors)是早期的命名，C++标准规格定案后所采用的新名称是函数对象(function objects)
 *
 * "函数对象" 一种具有函数特质的对象
 * 这种东西在调用者可以像函数一样地被调用，在被调用者则以对象所定义的function call operator扮演函数的实质角色
 *
 * 比如sort的第二个版本操作，是将该"操作"设计为一个所谓的仿函数(就语言层面而言是个class),再以该仿函数产生一个对象
 * 并以此对象作算法的一个参数
 *
 */

/*
 * 仿函数其实上就是一个"行为类似函数"的对象。
 * 为了能够"行为类似函数"，其类别定义中必须自定义(或说改写、重载)function call运算子(operator())
 * 拥有这样的运算子后，我们就可以在仿函数的对象后面加上一对小括号，以此调用仿函数所定义的operator()
 *
 */

#include <functional>
#include <iostream>
using namespace std;

int main() {
	greater<int> ig;
	cout << boolalpha << ig(4, 6) << endl; //false

	cout << greater<int>()(6, 4) << endl;	 //true
}

/*
 * 第一种用法 greater<int> ig的意思是产生一个名为ig的对象，ig(4, 6)则是调用其operator(),并给予两个参数4, 6
 * 第二种用法中的greater<int>()意思是产生一个临时(无名的)对象，之后的(4, 6)才是指定两个参数4, 6
 * 
 * 程序中的boolalpha是一种所谓的iostream manipulators(操控器)，用来控制输出入设备的状态
 * boolalpha意思是从此以后对bool值的输出，都改为以字符串"true"或者"false"表现
 */

/*
 * STL仿函数的分类，若以操作数(operand)的个数划分，可分为一元和二元仿函数，
 * 若以功能划分，可分为算术运算(Arithmetic)、关系运算(Rational)、逻辑运算(Logical)
 *
 * 用仿函数包含#include <functional>文件
 */


