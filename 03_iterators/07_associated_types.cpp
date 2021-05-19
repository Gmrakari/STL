

/*
 * Date:2021-05-19 16:26
 * filename:07_associated_types.cpp
 *
 */

/*
 * 什么是相应型别(associated types)?
 * 迭代器所指之物的型别便是其一
 * C++只支持sizeof(),并未支持typeof()
 * 即便动用RTTI性质中的typeid(),获得的也只是型别名称,不能拿来做变量声明之用
 *
 */

/*
 * 解决方法:
 * 利用function template 的参数推导(argument deducation)机制
 */

template <class T,class T>
void func_imp1(I iter,T t)
{
	T tmp;//这里解决了问题，T就是迭代器所指之物的型别,本例为int
};

template <class I>
inline void func(I iter)
{
	func_imp1(iter,*iter); //func 的工作全部移往func_imp1 (pointe to -> line 23)
}

int main()
{
	int i;
	func(&i);		//point to -> line 29
}
/*
 * 我们以func()对外接口,却把实际操作全部置于func_imp1()之中
 * 由于func_imp1()是一个function template,一旦被调用,编译器会
 * 自动进行template参数推导,于是导出型别T,顺利解决问题
 * 
 */


