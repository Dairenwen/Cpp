#include<iostream>
#include<vector>
#include<assert.h>

//// 类域
//// 命名空间域
//// 局部域
//// 全局域
//// 局部域->全局域 -> 展开了命名空间域 or 指定访问命名空间域

//namespace bit
//{
//	int rand = 1;//直接用rand会与std库里面的函数冲突，因此要使用命名空间来使用变量rand
//}//如果不使用::来对命名空间进行主动访问，是不会访问命名空间的，除非用using将命名空间进行打开
////
////int main()
////{
////	printf("%d\n", bit::rand);
////	printf("%p\n", rand);
////
////	return 0;
////}
//这里命名空间可以嵌套定义，并且空间里可以定义任何数据，包括函数整形字符结构体
//namespace N1
//{
//    int a = 0;
//    int b;
//    int Add(int left, int right)
//    {
//        return left + right;
//    }
//
//    namespace N2
//    {
//        int a = 1;
//        int c;
//        int d;
//        int Sub(int left, int right)
//        {
//            return left - right;
//        }
//    }
//}

//int main()
//{
//	std::cout << "hello world" << std::endl;//<<写入的标识，使用cout和endl都要
//using namespace std;
//// 直接展开会有风险，我们定义如果跟库重名，就报错了
//// 建议项目里面不要去展开，建议日常练习可以这么玩
//// 项目建议指定访问，不要轻易展开命名空间
//
//int main()
//{
//	cout << "hello world" << endl;//<<流插入运算符，使用cout和endl都要打开std库
//	std::cout << "hello world" << std::endl;
//
//	list<int> lt;
//
//	return 0;
//}

// 展开某个：把常用展开
//using std::cout;
//using std::endl;//endl后自带换行

//int main()
//{
//	int x = 10;
//	double d = 11.11;
//
//	// 自动识别类型
//	cout << x << " " << d << endl;
//
//	// >> 流提取运算符
//	std::cin >> x >> d;
//	cout << x << " " << d << endl;
//	printf("%d,%.2f\n", x, d);
//	cout << x << " " << d << endl;
//	
//	return 0;
//}

//void fun(int a, int b=20, int c = 20)
//{
//	cout << "fun(int a,int b,int c)" << endl;
//}
//int main()
//{
//	fun(10,20,30);
//	return 0;
//}

//#include<stdio.h>
//#include<stdlib.h>
//
//namespace haha
//{
//	int rand = 0;
//	namespace hehe
//	{
//		int add(int a, int b)
//		{
//			return a + b;
//		}
//	}
//}
//int main()
//{
//	printf("%d", haha::hehe::add(114,514));
//	return 0;
//}
//#include"test.h"
using namespace std;
////参数变量名不同
//void f(int a, char b)
//{
//	cout << "f(int a,char b)" << endl;
//}
//char f(int a,char b)
//{
//	cout << "f(char b, int a)" << endl;
//}
//int main()
//{
//	f(10, 'a');
//	f(10,'a');
//	return 0;
//}
void TestConstRef()
{
	const int a = 10;
	//int& ra = a;   // 该语句编译时会出错，a为常量
	const int& ra = a;
	// int& b = 10; // 该语句编译时会出错，b为常量
	const int& b = 10;
	double d = 12.34;
	//int& rd = d; // 该语句编译时会出错，类型不同
	const int& rd = d;
}
//int main()
//{
//	// 不可以
//	// 引用过程中，权限不能放大
//	const int a = 0;
//	//int& b = a;
//
//	// 可以，c拷贝给d，没有放大权限，因为d的改变不影响c
//	const int c = 0;
//	int d = c;
//
//	// 不可以
//	// 引用过程中，权限可以平移或者缩小
//	int x = 0;
//	int& y = x;
//	const int& z = x;
//	++x;
//	//++z;
//
//	const int& m = 10;
//
//	double dd = 1.11;
//	int ii = dd;
//	//int& rii = dd; 这样就不行，是因为临时变量const，给int就权限放大了
//	const int& rii = dd;
//
//	return 0;
//}

//int func1()
//{
//	static int x = 0;
//	return x;
//}
//
//int& func2()
//{
//	static int x = 0;
//	return x;
//}

//int main()
//{
//	// int& ret1 = func1();  // 权限放大
//	//const int& ret1 = func1(); // 权限平移
//	// int ret1 = func1();  // 拷贝
//
//	int& ret2 = func2();		// 权限平移
//	const int& rret2 = func2();  // 权限缩小
//
//	return 0;
//}

//int main()
//{
//	int a = 10;
//
//	// 语法层面：不开空间，是对a取别名
//	int& ra = a;
//	ra = 20;
//
//	// 语法层面：开空间，存储a的地址
//	int* pa = &a;
//	*pa = 30;
//
//	return 0;
//}
//void f(int)
//{
//	cout << "f(int)" << endl;
//}
//void f(int*)
//{
//	cout << "f(int*)" << endl;
//}
//int main()
//{
//	f(nullptr);
//	return 0;
//}

//void Stack::Init(size_t capacity)
//{
//	_array = (DataType*)malloc(sizeof(DataType) * capacity);
//	if (nullptr == _array)
//	{
//		perror("malloc申请空间失败");
//		return;
//	}
//	_capacity = capacity;
//	_size = 0;
//}

//class Date
//{
//public:
//	void Init(int year, int month, int day)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1, d2;
//	d1.Init(2022, 1, 11);
//	d2.Init(2022, 1, 12);
//	d1.Print();
//	d2.Print();
//	return 0;
//}
//// 1.下面程序编译运行结果是？
//class A
//{
//public:
//	void Print()
//	{
//		cout << "Print()" << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p = nullptr;
//	p->Print();
//	return 0;
//}
// 1.下面程序编译运行结果是？
//class A
//{
//public:
//	void PrintA()
//	{
//		cout << _a << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p = nullptr;
//	p->PrintA();
//	return 0;
//}

//typedef int DataType;
//class Stack
//{
//public:
//	Stack(DataType* a, int n)
//	{
//		cout << "Stack(DataType* a, int n)" << endl;
//		_array = (DataType*)malloc(sizeof(DataType) * n);
//		if (NULL == _array)
//		{
//			perror("malloc申请空间失败!!!");
//			return;
//		}
//		memcpy(_array, a, sizeof(DataType) * n);
//
//		_capacity = n;
//		_size = n;
//	}
//
//	Stack(int capacity = 4)
//	{
//		cout << "Stack(int capacity = 4)" << endl;
//		_array = (DataType*)malloc(sizeof(DataType) * capacity);
//		if (NULL == _array)
//		{
//			perror("malloc申请空间失败!!!");
//			return;
//		}
//
//		_capacity = capacity;
//		_size = 0;
//	}
//
//	void Push(DataType data)
//	{
//		CheckCapacity();
//		_array[_size] = data;
//		_size++;
//	}
//
//	void Pop()
//	{
//		if (Empty())
//			return;
//		_size--;
//	}
//	DataType Top() { return _array[_size - 1]; }
//	int Empty() { return 0 == _size; }
//	int Size() { return _size; }
//private:
//	void CheckCapacity()
//	{
//		if (_size == _capacity)
//		{
//			int newcapacity = _capacity * 2;
//			DataType* temp = (DataType*)realloc(_array, newcapacity * sizeof(DataType));
//			if (temp == NULL)
//			{
//				perror("realloc申请空间失败!!!");
//				return;
//			}
//			_array = temp;
//			_capacity = newcapacity;
//		}
//	}
//private:
//	DataType* _array;
//	int _capacity;
//	int _size;
//};
//
//int main()
//{
//	Stack s(1);
//	Stack ss();
//	return 0;
//}
//~Stack()
//{
//	cout << "~Stack()" << endl;
//	if (_array)
//	{
//		free(_array);
//		_array = NULL;
//		_capacity = 0;
//		_size = 0;
//	}
//}

//class Time
//{
//public:
//	Time()
//	{
//		cout << "Time()" << endl;
//		_hour = 0;
//		_minute = 0;
//		_second = 0;
//	}
//
//private:
//	int _hour;
//	int _minute;
//	int _second;
//};
//class Date
//{
//private:
//	// 基本类型(内置类型)
//	int _year=2025;
//	int _month=1;
//	int _day=11;
//	// 自定义类型
//	Time _t;
//public:
//	void Print()
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//};
//int main()
//{
//	Date d;
//	d.Print();
//	return 0;
//}

//class Date
//{
//public:
//	Date(int year = 1900, int month = 1, int day = 1)
//	{
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	Date(const Date& d) 
//	{
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	Date d2(d1);
//	return 0;
//}

//class A
//{
//public:
//	A(int a=0)
//		:_a(a)
//	{}
//private:
//	int _a;
//};
//class Date
//{
//public:
//	Date(int a,int& b)
//		:obj(10)
//		,_a(b)
//		,b(10)
//	{ }
//private:
//	A obj;
//	int& _a;
//	const int b;
//};
////#include"Date.h"
//int main()
//{
//	Date d1(1949, 10, 1);
//	d1.Print();//这里传过去的是d1的地址
//	//const Date d2(1949, 10, 1);
//	//d2.Print();//这里const修饰的是d2的地址，const传给没const权限放大了！
//	return 0;
//}

//class Stack
//{
//public:
//	Stack(int capacity = 4)
//		: _capacity(capacity)
//		,a((int*)malloc(sizeof(int)* _capacity))
//		,_size(0)
//	{
//		if (a == nullptr)
//		{
//			perror("malloc failed");
//			exit(-1);
//		}
//	}
//	void Print()
//	{
//		cout << a <<"\n" << _capacity <<"\n" << _size << endl;
//	}
//private:
//	int* a;
//	int _capacity;
//	int _size;
//};
//
//class A
//{
//public:
//	static int Add(int a, int b)
//	{
//		return a + b;
//	}
//private:
//	static int _a;
//};
//int A::_a = 0;
//int main()
//{
//	A a;
//	a.Add(1, 2);
//	return 0;
//}
// 

class A
{
public:
    A(int a = 0)
        :_a(a)
    {
        cout << "A(int a)" << endl;
    }

    A(const A& aa)
        :_a(aa._a)
    {
        cout << "A(const A& aa)" << endl;
    }

    A& operator=(const A& aa)
    {
        cout << "A& operator=(const A& aa)" << endl;

        if (this != &aa)
        {
            _a = aa._a;
        }

        return *this;
    }

    ~A()
    {
        cout << "~A()" << endl;
    }
private:
    int _a;
};

void Func1(A aa)
{
}

A Func5()
{
	A aa;
	return aa;
}

//int main()
//{
//    A ra1 = Func5(); // 拷贝构造+拷贝构造 ->优化为拷贝构造
//    A ra2;
//    ra2 = Func5();
//
//    //A aa1;
//    //Func1(aa1); // 
//
//    //Func1(A(1)); // 构造+拷贝构造 ->优化为构造
//    //Func1(1);    // 构造+拷贝构造 ->优化为构造
//
//    //A aa2 = 1;  // 构造+拷贝构造 ->优化为构造
//
//
//    return 0;
//}

//int main()
//{
//    int* n1 = new int(10);
//    delete n1;
//
//    int* n2 = new int[10] {1, 2, 3};
//    delete n2;
//
//
//    return 0;
//}

class re
{
public:
    re(int year, int month, int day, int plus)
    {
        _year = year;
        _month = month;
        _day = day;
        _plus = plus;
    }
    void co()
    {
        _day += _plus;
        while (_day > Getmonthday(_year, _month))
        {
            _day -= Getmonthday(_year, _month);
            if (_month == 12)
            {
                _month = 0;
                _year++;
            }
            _month++;
        }
        printf("%d-%02d-%02d\n", _year, _month, _day);
    }
    int Getmonthday(int year, int month)
    {
        int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
        {
            return 29;
        }
        else {
            return arr[month - 1];
        }
    }
private:
    int _year;
    int _month;
    int _day;
    int _plus;
};
int main()
{
    int n = 0;
    cin >> n;
    int i = 0;
    int year=0, month=0, day=0, plus=0;
    for (i = 0; i < n; i++)
    {
        cout << year << month << day << plus;
        re tmp(year, month, day, plus);
        tmp.co();
    }
    return 0;
}