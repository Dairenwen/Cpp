#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;
//提前用到了student，要在这里提前声明
class Student;

class Person
{
public:
	friend void dispaly(const Person& p, const Student& s);
	Person(const string& name = "dairenwen", int age = 18, int tel = 133)
		:name(name)
		, age(age)
		, tel(tel)
	{
		count++;
		cout << "person contruct" << endl;
	}

	Person(const Person& p)
	{
		name = p.name;
		age = p.age;
		tel = p.tel;
	}

	~Person()
	{
		cout << "person destroy" << endl;
	}
protected:
	string name;
	int age;
	int tel;
	static int count;
};
int Person::count = 0;
//基类的private成员统统不能访问,一定要记住是基类的private成员不管怎么继承都不能访问，其他的只能在类中访问
//推荐public继承，private/protected继承维护性差！
//其他的protected/public基类或继承方式选取优先级最低的记忆
//优先级顺序：public>protected>private
class Student :virtual public Person//派生类：继承方式 基类
{
public:
	friend void dispaly(const Person& p, const Student& s);
	Student()
		:Person("shunxinru", 18, 145)
		, add(133)
	{
		cout << name << " " << age << " " << tel << endl;
		cout << add << endl;
		cout << "student contruct" << endl;
	}

	Student(const Student& s)
		:Person(s)//切片赋值Person
		, add(s.add)//初始化其他变量
	{
	}

	Student& operator=(const Student& s)
	{
		name = s.name;
		add = s.add;
		tel = s.tel;
		age = s.age;
		return *this;
	}


	~Student()
	{
		//这里能不能显示调用父类的析构函数？为什么要加上Person：：
		//这是因为多态的原因，析构函数的函数名被特殊处理了，统一处理成destructor
		//并且这样无法先析构子后父，会出问题
		//Person::~Person();
		cout << "Student destroy" << endl;
	}
protected:
	int add;
};
//使用class省略继承方式 默认为private继承 
//使用struct省略继承方式 默认为public继承
//继承实验
void dispaly(const Person& p, const Student& s)
{
	//想要访问父类就加上friend，但是父亲的朋友不是子类的朋友，要是想访问子类，还得在子类中加上
	//很容易理解：父亲都使用不了子类的成员，何况是父亲的朋友
	//cout << "you" << p.name << endl;
	//cout << "you" << s.add << endl;
	//如果是静态成员变量就不会像其他普通变量一样再去拷贝一份，可以理解为继承了静态变量的使用权
	//我的理解：静态变量本身就放在常量区/静态区，所以当然不会再去拷贝
	cout << &p.name << endl;
	cout << &s.name << endl;
	cout << &p.count << endl;
	cout << &s.count << endl;
}
void test1()
{
	Student s;
	Person p;
	//s = p;//父类不能给子类，因为语法规定，并且子类有的父类没有，不好进行处理
	p = s;//子类可以给父亲，赋值兼容转换（切割，切片），子类会把继承自父亲的那一部分拷贝给父亲
	Person& pq = s;//这样符合语法，因为没有发生类型转换产生临时变量，所以没有常性
}


class father
{
public:
	void func()
	{
		cout << "father:func" << endl;
	}
protected:
	int _num;
};

class son :public father
{
public:
	void func()
	{
		cout << "son:func" << endl;
	}
private:
	int _num;
};

void test2()
{
	//如果子类和父类中有同名变量或者函数，那么会优先调用离自己近的那一个
	//子类中优先调用子类的，加上父类：：可以调用父类中的，但是父类只能调用父类中的，不能够调用子类中的
	son s;
	s.func();
	s.father::func();
	//在基类和派生类中，当派生类定义了一个与基类同名的函数时，就会发生隐藏现象。注意！！！！无论函数的参数列表是否相同，派生类的函数都会隐藏基类中同名的函数。
	//也就是说，在派生类作用域内，通过派生类对象或派生类指针访问该同名函数时，默认调用的是派生类中的函数，而基类中的同名函数被隐藏。
}

void test3()
{
	Student s;
	Person p;
	//这里说明会先去调用基类的构造函数，这是语法默认的，其次是派生类的构造函数，最后析构的是基类
	//这里顺序还可能是因为父类不可能使用子类的成员，但是子类可能使用父类的成员，那么先析构父类会出错
	//如果没有默认构造，传值构造需要在初始化列表中进行，并且初始化列表会按照声明的顺序进行
	//如果在派生类中想要完成初始化，那么先会初始化基类，因为基类先出现，至于派生类的成员变量，初始化顺序在后
	dispaly(p, s);
	//派生类的构造函数必须调用基类的构造函数初始化基类的那一部分成员。如果基类没有默认的构造函数，则必须在派生类构造函数的初始化列表阶段显示调用。
	//派生类的拷贝构造函数必须调用基类的拷贝构造完成基类的拷贝初始化。
	//派生类的operator = 必须要调用基类的operator = 完成基类的复制。
	//派生类的析构函数会在被调用完成后自动调用基类的析构函数清理基类成员。因为这样才能保证派生类对象先清理派生类成员再清理基类成员的顺序。
}

void test4()
{
	Student s1;
	Student s2(s1);
	Student s3;
	s3 = s1;
}
//引入多继承：为了继承多个对象的特性，存在多继承，但是也存在问题
//数据冗余与二义性：当子类继承的两个父类都继承自同一个基类时，
//如果基类中有某个成员变量或成员函数，那么在子类中访问该成员时可能会出现二义性。
//因为子类不知道应该使用从哪个父类继承下来的基类成员。
//并且会出现两份相同的基类成员，出现数据冗余的情况
//如何解决？在继承的两个类上加上virtual
class Teacher :virtual public Person
{
protected:
	int _id;
};
class Underguaduate :public Teacher, public Student
{
protected:
	int _id;
};
//这里是菱形虚拟继承的实现，共同继承的成员，是放在下面，上面是存储的是 不同虚基表的地址，通过这个地址，拿到偏移量，从而去访问公有继承的成员
//这个是他实现的思路，对象模型中存储虚基表的地址，获取偏移量，从而访问继承下共同的成员，它是这样实现的


//2_28
//class A
//{
//public:
//	int _a;
//};
//class B
//{
//public:
//	int _b;
//};
//class C :public A, public B
//{
//public:
//	int _c;
//};
//void test5()
//{
//	C c;
//	A* a = &c;
//	B* b = &c;
//	C* cc = &c;
//	printf("%p %p %p", a, b, cc);
//	//进行切片赋值，C:A,B代表先继承A再继承B，指针cc和a指向同一块
//	//b在a的下面
//	//如果先继承B再继承A，cc和b指向同一块，a在b的下面
//}


//继承与组合：
class Aa
{

};
class Bb :public Aa
{

};
class Cc
{
private:
	Bb _b;
};
//上面这种方式就是组合，在Cc中可以使用继承了Aa的Bb，但是访问不到AaBb中的私有成员
//如果是继承的话，除了private的成员都可以进行访问，那么耦合度较高，如果父类进行改动，调试起来比较困难
//建议：能用组合就用组合，但是要用到继承也不能回避
//白盒测试：知道了底层的实现再去测试，类似于这里的继承
//黑盒测试：不知道底层实现，随便测试
//is-a: 说的是这里的继承关系
//has-a: 说的是这里的组合关系

class A
{
public:
	int a;
};
class B:virtual public A
{
public:
	int b;
};
class C :virtual public A
{
public:
	int c;
};
class D :public B, public C
{
public:
	int d;
};
void test5()
{
	D dd;
	dd.B::a = 1;
	dd.C::a = 2;
	dd.b = 3;
	dd.c = 4;
	dd.d = 5;
	dd.a = 0;



}


