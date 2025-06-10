#define _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
#include<list>
#include<map>
#include<functional>
#include<memory>
#include<string>
#include<unordered_map>
using namespace std;

//class A
//{
//public:
//	explicit A(int a = 0)//加上explicit禁止隐式类型转换
//		:a(a)
//	{
//
//	}
//private:
//	int a;
//
//};
//c++的类型转换
void test1()
{
	//c++兼容c,支持隐式类型转换以及显式类型转换
	double a = 1.1;
	int b = a;//隐式类型

	int c = (int)a;//显示类型

	//单参数类也支持隐私和类型转换构造
	//A d = 1;
	
}

void test2()
{
	volatile const int a = 1;
	int* p = (int*)&a;
	(*p)++;
	cout << a << " " << *p << endl;//这里a打印值不会被修改，编译时存放至寄存器，
	//修改的只是内存中的值，如果从内存取值打印，加上volatile关键字
}

class A
{
public:
	virtual void func()
	{

	}
private:
	int a;
};
class B :public A
{
private:
	int b;
};

void func(A* ach)
{
	//请注意这里只能用于多态类型，如果没有实现虚函数也就没有实现多态，不能使用
	//dynamic_cast进行转换如果成功返回转换后的指针
	//如果转换失败返回空指针
	B* ret1 = dynamic_cast<B*> (ach);
	if (ret1)
	{
		cout << "1success" << endl;
	}
	A* ret2 = dynamic_cast<A*> (ach);
	if (ret2)
	{
		cout << "2success" << endl;
	}
}
void test3()
{
	//C++中重要的四种强制类型转换标识
	double a = 3.14;
	int b = static_cast<int>(a);//中间实例化要转为的类型
	//static适用于具有一定关系的数据
	//string c = static_cast<string>(a);//这样就会出错
	//主要用于基本数据类型之间的转换，以及具有继承关系的类指针或引用之间的转换。它在编译时进行类型检查。


	double* c = reinterpret_cast<double*>(b);//reinterpret可以强制类型转换两个没有关系的变量
	//它可以将任意类型的指针或引用转换为其他类型的指针或引用，甚至可以将指针转换为整数类型
	//比较危险，慎用！

	volatile const int d = 10;
	int* e = const_cast<int*>(&d);
	(*e)++;
	const int& f = 10;
	int* h = const_cast<int*>(&f);
	//constcast去除或添加指针、引用的const属性，不能用于去除变量本身的const性

	A A; B B;
	A = B;//子类可以切片赋值父类
	//B = A;//这样的行为存在风险，可能会越界访问
	//向上转型：子类对象指针 / 引用->父类指针 / 引用(不需要转换，赋值兼容规则)
	//向下转型：父类对象指针 / 引用->子类指针 / 引用(用dynamic_cast转型是安全的)
	//使用dynamiccast可以进行检查
	func(&A); 
	cout << "\n";
	func(&B);
}

//RTTI 运行时类型识别
//. typeid运算符
//2. dynamic_cast运算符
//3. decltype


class AA
{
public:
	AA(int a=0)
		:a(a)
	{ }

	//为什么不重载operator ()因为仿函数中已经存在，会引发冲突
	explicit operator int()//为什么要加上explicit，可能是为了放宽转换，了解即可
	{
		//本身就没有返回值
		return a;
	}

	operator bool()
	{
		return a;
	}
private:
	int a = 0;
};
//iostream
void test4()
{
	int a = 0; int b = 0;
	while (cin >> a)
	{
		cout << a << endl;
	}
	//如果在读取过程中按下ctrlc直接结束了进程
	//按下ctrlz和空格正确结束程序

	//这样循环读取的原理是什么？
	//举例自定义类型AA
	AA aa = 1;
	int bb = aa;//这样是否可以呢？使用operator int函数
	//说明operator类型这种函数是存在的
	double cc = aa;

	while (cin >> a)//先调用operator>>,再调用operator bool判断返回值
	{//operator>>(cin, str).operator bool()
		cout << a << endl;
	}

	while (cin >> a >> b)//cin.operator>>(a).operator>>(b).operator bool()
	{
		cout << a << b << endl;
	}
}

