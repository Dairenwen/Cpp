#include<iostream>
using namespace std;


//class A {
//public:
//	A(const char* s) { cout << s << endl; }
//	~A() {}
//};
//
//class B :virtual public A
//{
//public:
//	B(const char* sa, const char* sb) :A(sa) { cout << sb << endl; }
//};
//
//class C :virtual public A
//{
//public:
//	C(const char* sa, const char* sb) :A(sa) { cout << sb << endl; }
//};
//
//class D :public B, public C//这里会按照继承顺序构造
//{
//public:
//	D(const char* sa, const char* sb, const char* sc, const char* sd) 
//		:B(sa, sb), C(sa, sc), A(sa)
//	{
//		cout << sd << endl;
//	}
//};
//
//int test1() {
//	D* p = new D("class A", "class B", "class C", "class D");
//	//因为A先声明所以先调用A的构造函数，但是A的构造函数只能调用一次，继承的基类当然不可能每次都发生构造
//	delete p;
//
//	B b("class A", "class B");
//
//	return 0;
//}


// 虚函数重写的一些细节：
// 重写的条件本来是虚函数+返回值类型、函数名字、参数列表完全相同，但是有一些例外
// 1、派生类的重写虚函数可以不加virtual -- （建议大家都加上）有可能是方便派生类的析构函数不用加上virtual，但是建议加上
// 2、协变，返回的值可以不同，但是要求返回值必须是父子关系指针或引用（极其少见少用，但是不可以轻视！）

class Person1 {
public:
	virtual	void BuyTicket() const { cout << "买票-全价" << endl; }
};

class Student1 : public Person1 {
public:
	void BuyTicket() const { cout << "买票-半价" << endl; }
};

class a
{};

class b : public a
{};

class Person2 {
public:
	virtual	a* BuyTicket() const { 
		cout << "买票-全价" << endl;
		return 0;
	}
};

class Student2 : public Person2 {
public:
	virtual b* BuyTicket() const { 
		cout << "买票-半价" << endl;
		return 0;
	}
};

// 多态条件
// 1、调用函数是重写的虚函数
// 2、基类指针或者引用
//如果只是传值的调用，那么根据变量的类型去调用
//如果是指针或者引用才会发生多态，根据指向的对象调用

// 多态，不同对象传递过去，调用不同函数
// 多态调用看的指向的对象
// 普通对象，看当前者类型
void func(const Person2* p)
{
	p->BuyTicket();
}
void func(const Person2& p)
{
	p.BuyTicket();
}

int test2()
{
	Person2 pp;
	func(&pp);
	func(pp);

	Student2 st;
	func(&st);
	func(st);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
class Person3 {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
	virtual ~Person3() { cout << "~Person3()" << endl; }
};

class Student3 : public Person3 {
public:
	virtual void BuyTicket() { cout << "买票-半价" << endl; }

	virtual~Student3() {
		cout << "~Student3()" << endl;
		delete[] ptr;
	}

protected:
	int* ptr = new int[10];
};
//
// 析构函数可以是虚函数吗？为什么需要是虚函数？
// 析构函数加virtual，是不是虚函数重写？
// 是，因为类析构函数都被处理成destructor这个统一的名字
// 为什么要这么处理呢？因为要让他们构成重写
// 那为什么要让他们构成重写呢？
// 因为下面的场景
//
int test3()
{
	//Person p;
	//Student s;

	Person3* p = new Person3;
	p->BuyTicket();
	delete p;

	p = new Student3;
	p->BuyTicket();
	delete p; // p->destructor() + operator delete(p)

	// 这里我们期望p->destructor()是一个多态调用，而不是普通调用
	//如果是普通调用，那么就会调用person的析构而不会调用student的析构了

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
class Car
{
public:
	virtual void Drive() final {}//final可以用于不想重写
};

class Benz :public Car
{
public:
	void Drive(int i) { cout << "Benz-舒适" << endl; }
};

class Carc {
public:
	 virtual void Drive() {}
};

// override 帮助派生检查是否完成重写，如果没有会报错
class Benzb :public Carc {
public:
	virtual void Drive() override { cout << "Benz-舒适" << endl; }
};

// 设计不想被继承类，如何设计？
// 方法1：基类构造函数私有   (C++98)
// 方法2：基类加一个final  （C++11）
//class A
//{
//public:
//	static A CreateObj()
//	{
//		return A();
//	}
//private:
//	A()
//	{}
//};
//
//class B : public A
//{};
//
//int main()
//{
//	// B bb;
//	A::CreateObj();
//
//	return 0;
//}

//class A
//{
//public:
//private:
//	~A()
//	{}
//};
//
//class B : public A
//{};
//
//int main()
//{
//	A* p = new A;
//
//	//B bb;
//
//	return 0;
//}


//class A final
//{
//public:
//private:
//};
//
//class B : public A
//{};
//
//int main()
//{
//	return 0;
//}
// 




// 这里常考一道笔试题：sizeof(Base)是多少？
class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}

private:
	char _b = 1;
};

//int main()
//{
//	Base b1;
//	cout << sizeof(Base) << endl;
//	return 0;
//}
//因为有指针加字符，为8

void Func(Person3& p)
{
	// 符合多态，运行时到指向对象的虚函数表中找调用函数的地址
	p.BuyTicket();
}

//虚函数表实现重写/覆盖：
//int main()
//{
//	Person3 Mike;
//	Func(Mike);
//
//	Student3 Johnson;
//	Func(Johnson);
//
//	return 0;
//}

class A
{
public:
	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
	virtual void test() { func(); }
};

class B : public A
{
public:
	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
};

//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->test();
//	return 0;
//}
//结果是B->1，那么为什么会这样？
//这里的p先去B类中寻找，没有test函数
//再去继承的A中寻找，找到后由*this调用test函数，这里的*this是A的
//由于是基类调用加上指针，并且构成了重写虚函数（三重：参数返回值函数名，缺省值是否一样没关系）
//因为p指向B，那么就回去B中调用func，这里的int val缺省值打印出来却不是0
//是因为派生类中的虚函数不用写virtual是因为函数所有信息继承自基类，也就是说A中给了空壳，B中重写的只是定义
//所以结果是B->1

class Parent
{
public:
	virtual void print()
	{
		cout << "parent print" << endl;
	}

	virtual void count()
	{

	}
private:
	int a;
};

class Son:public Parent
{
public:
	virtual void print()
	{
		cout << "son print" << endl;
	}
	virtual void func()
	{
		cout << "son func" << endl;
	}
private:
	int b;
};
//为什么不能是子类类型？父类不能给子类赋值
//为什么不能是Parent？如果传值拷贝需要切片赋值，赋值不会复制虚表，这时就不会调用子类的函数了
void test4(const Parent& pp)
{
	int a = 0;
	printf("    栈：%p\n", &a);
	auto b = new int;
	printf("    堆：%p\n", b);
	static int c = 0;
	printf("  静态：%p\n", &c);
	const char* arr = "abcdefg";
	printf("常量区：%p\n", arr);
	Parent p; Son s;
	printf("parent: %p\n", *(int*)&p);//强转为int来打印4个字节的地址；
	printf("   son: %p", *(int*)&s);

	
}

//多态如何实现？虚表/虚函数表，派生类继承时会将基类的虚函数表拷贝下来，如果有函数重写，那么就更改那一个函数的地址
//其实在类中占用空间的就是成员变量和这一个指针，什么指针？_vfptr,存的是虚表的地址
//虚表本质是一个函数指针数组，通常在vs下数组最后一个元素存储的是nullptr，内存调用下看到的是0
//只有虚函数才会放进虚表，如果是普通函数则不会放进虚表
//如果派生类中有不同于基类的新的虚函数，那么监视窗口是看不到的，必须通过内存去看
//再来看虚表的存储位置，经过验证，存储在常量区,而虚函数存在代码段
typedef void(*ptr)();

void test5(ptr* arr)
{
	for (size_t i = 0; arr[i] != nullptr; i++)
	{
		printf("_vfptr[%d]:%p\n", i, arr[i]);
		//arr[i]();
	}
}
//如果是单继承，那么派生类的虚函数就会放在虚表最后，如果是多继承，那么派生类的虚函数会放在第一个类的虚函数表里
//并且会继承所有基类的虚表，自己不会生成虚表，将自己的虚函数放到第一个类的虚表后面
void test6()
{
	Parent p;
	Son s;
	cout << sizeof(p) << endl;
	cout << sizeof(s) << endl;
}
int main()
{
	Parent pp;
	test4(pp);
	//Parent p;
	//Son s;
	//test5((ptr*)&p);
	//cout << "\n";
	//test5((ptr*)& s);
	//test6();
	return 0;
}

class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
		int b2;
};
class Derive : public Base1, public Base2 {
public:
	virtual void func1()override { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};
//typedef void(*VFPTR) ();
//void PrintVTable(VFPTR vTable[])
//{
//	cout << " 虚表地址>" << vTable << endl;
//	for (int i = 0; vTable[i] != nullptr; ++i)
//	{
//		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
//		VFPTR f = vTable[i];
//		f();
//	}
//	cout << endl;
//}
//int main()
//{
//	/*Derive d;
//	Base1* ptr1 = &d;
//	ptr1->func1();
//
//	Base2* ptr2 = &d;
//	ptr2->func1();
//
//	Derive* ptr3 = &d;
//	ptr3->func1();*/
//	test4();
//	return 0;
//}




class chouxiang
{
public:
	virtual void test() = 0;//=0为纯虚函数，这个类叫抽象类，不可以实例化

};
class cx :public chouxiang//继承了没有重写也不可以实例化
{
public:
	virtual void test()
	{
		cout << "chongxie" << endl;
	}
private:
	int a;
};

void test7()
{
	//chouxiang c;
	cx x;//这里只有对纯虚函数重写，才可以实例化，纯虚函数规范了派生类必须重写，更体现出了接口继承
}