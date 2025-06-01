#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<algorithm>
#include<array>
#include<unordered_set>
#include<forward_list>
#include<functional>
#include"string.hpp"
using namespace std;


struct Point
{
	//explicit Point(int x, int y)
	//本质支持的是多参数的隐式类型转换
	//如果加上了explicit就禁止了
	Point(int x, int y)
		:_x(x)
		, _y(y)
	{
		cout << "Point(int x, int y)" << endl;
	}

	int _x;
	int _y;
};

// 一切皆可用{}初始化，并且可以不写=
// 建议日常定义，不要去掉=，但是我们要能看懂
void test_cpp11_1()
{
	//介绍c++11的初始化更新内容
	int x = 1;
	int y = { 2 };
	int z{ 3 };//居然可以不写=

	int a1[] = { 1,2,3 };
	int a2[]{ 1,2,3 };

	// 本质都是调用构造函数
	Point p0(0, 0);
	Point p1 = { 1,1 };  // 多参数构造函数隐式类型转换
	Point p2{ 2,2 };

	const Point& r = { 3,3 };//权限的缩小

	int* ptr1 = new int[3]{1, 2, 3};
	Point* ptr2 = new Point[2]{p0,p1};
	Point* ptr3 = new Point[2]{ {0,0},{1,1} };
}

struct test
{
	test(int first=0,int second=0)
		:a(first)
		,b(second)
	{ }

private:
	int a; int b;
};
void practice1()
{
	int a{ 1 };
	int b = { 2 };

	auto arr = new int[10] {1, 2, 3, 4, 5, 6, 7};
	auto aa = new test[2]{ test(1,1),test(2,2) };
	test* bb = new test[2]{ {1,1},{2,2} };

	vector<int> v = { 1,2,3,4,5,6 };//这么初始化可以的原因是c++11实现了初始化列表
	initializer_list<int> il = { 1,2,3,4,5,6 };//这样一段列表是放在常量区的，vector实现了用列表进行初始化
	//initializerlist底层存储了两个指针，分别是begin和end指针，方便初始化
	test* ret = new test[10]{ {1},{2},{3},{4},{5}};//这样不是初始化列表就是普通的初始化

	map<string, string> map = { {"插入","insert"},{"拔出","takeout"} };


}

template<class T>
class teststruct
{
private:
	vector<T> _vv;
};

void testfunc(int* a)
{
	return;
}
void test_cpp11_2()
{
	auto ptr = malloc;
	cout << typeid(ptr).name() << endl;

	//单纯定义一个变量出来
	auto pptr = ptr;
	decltype(ptr) ppptr;

	//这点如果是定义一个类那么非常有用
	teststruct<decltype(ptr)> t;

	//nullptr
	testfunc(0);
	testfunc(nullptr);
	testfunc(NULL);//这三者不同，NULL宏替换成了0

	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	for (auto e : arr)
	{
		cout << e << " ";
	}

	//智能指针先不讲

	//STL中的一些变化
	array<int, 10 > array= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//比起静态数组，增加了越界访问的检查，但可以用vector进行替换

	forward_list<int> 单链表;
	单链表.insert_after(单链表.begin(), 1);

	//单链表提供在指定位置之后插入和删除，不能在指定位置进行删除插入，以及头插头删，没有提供的是尾插尾删
	//鸡肋之处显而易见
}

void test_cpp11_3()
{
	//介绍左值以及右值
	//可寻址性
	//左值：具有固定的内存地址，可以通过取地址运算符& 获取其地址。例如，变量是典型的左值，因为它们在内存中有固定的存储位置。
	//右值：通常没有固定的内存地址，不能对其使用取地址运算符& 。例如，字符常量、临时对象等都是右值，它们在表达式求值过程中可能存在于寄存器或临时存储区域，没有可获取的固定地址。
	//出现在赋值运算符的位置
	//左值：可以出现在赋值运算符的左边，作为赋值的目标。因为左值代表一个可以被修改的对象，所以能够接受赋值操作。
	//右值：一般出现在赋值运算符的右边，作为赋值的值来源。虽然有些右值也可以出现在赋值表达式中，但它们不能作为赋值的目标。
	//表达式的类型和性质
	//左值：包括变量、数组元素、函数返回值为左值引用的情况等。例如，函数返回一个左值引用，那么这个返回值就是左值，可以被继续赋值或取地址。
	//右值：除了前面提到的字面常量和临时对象外，还包括一些表达式的结果，如算术表达式的结果（除非该表达式的结果是一个变量的引用）、函数返回值为非引用类型的情况等。

	//左值引用：给左值取别名
	//右值引用：给右值取别名
	double x = 1.1, y = 2.2;
	int a = 0;
	int& b = a;

	int&& right = 10;
	int&& count = x + y;

	const int& con = 10;//使用const可以给右值取左值的别名
	const double& plus = x + y;

	int&& left = move(a);//使用move可以用右值引用给左值取别名

	//左值引用的使用场景：
	//1.引用返回 2.做参数 3.减少拷贝，提高效率
}

//void func(int& a)
//{
//	cout << "int&" << endl;
//}
//void func(int&& a)
//{
//	cout << "int&&" << endl;
//}
//两个构成重载
void func(const int& a)
{
	cout << "int&" << endl;
}
void func(int&& a)//右值会匹配这种
{
	cout << "int&&" << endl;
}

drw::string Movecopy()
{
	drw::string str("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	str[0] = '1';
	return str;
}//如果要验证移动构造，需要传值返回，如果不进行优化，那么拷贝构造的临时对象是将亡值
//进行优化后，直接将str作为将亡值调用移动构造

class defaultcopy
{
public:
	defaultcopy()
	{
		_a = new char[10];
	}

	defaultcopy(const defaultcopy& dc) = default;

	defaultcopy(defaultcopy&& dc) = default;

	//~defaultcopy() = delete;//如果不像生成默认函数，可以直接加上delete，不必在98中定义在private中
private:
	char* _a;
};
void test_cpp11_4()
{
	/*int a = 0;
	func(1+1);*/

	//下面来测试移动构造以及移动赋值
	//对于内置类型的临时对象称为纯右值
	//对于自定义类型的临时对象称为将亡值
	//drw::string newstr = Movecopy();
	/*drw::string ns;
	ns = Movecopy();*/
	//有移动构造之前，如果是拷贝构造返回，那么先产生一个临时对象再拷贝构造新对象，这里要进行两次深拷贝，
	//但是编译器会进行优化，通常是一次拷贝，有了移动构造之后，先拷贝构造临时对象，然后移动构造新对象，但是编译器进行优化，只用移动构造就行了，

	drw::string s("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	drw::string s1 = s;
	//move(s);
	drw::string s2 = move(s);

	////移动构造不仅可以在传值拷贝的时候减少拷贝代价，还可以在各种容器的插入进行移动构造
	list<string> list;
	string s3("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	list.push_back(s3);

	list.push_back("xxxxxxxxxxxxxxxxxxxxxxxxx");
	list.push_back(move(s3));
	//默认移动构造：什么场景下会生成默认移动构造？
	//如果拷贝构造，移动复制，析构函数任何一个都没有实现，那么会生成默认移动构造，
	//对于内置类型去调用浅拷贝，对于自定义类型去调用拷贝构造
	//如果上述三个函数存在，也可以强制实现默认移动构造，在函数名后加上=default即可。

	//移动赋值函数也是这样，默认移动赋值函数会在没有析构函数，赋值操作符，拷贝构造函数的条件下生成，
	//对于内置类型浅拷贝，对于自定义类型调用移动赋值构造
	defaultcopy test;
	defaultcopy newtest = test;
}

void Fun(int& x) { cout << "左值引用" << endl; }
void Fun(const int& x) { cout << "const 左值引用" << endl; }
void Fun(int&& x) { cout << "右值引用" << endl; }
void Fun(const int&& x) { cout << "const 右值引用" << endl; }
// 模板中的&&不代表右值引用，而是万能引用，其既能接收左值又能接收右值。
// 模板的万能引用只是提供了能够接收同时接收左值引用和右值引用的能力，
// 但是引用类型的唯一作用就是限制了接收的类型，后续使用中都(退化成了左值)，
// 我们希望能够在传递过程中保持它的左值或者右值的属性, 就需要用我们下面学习的完美转发
template<typename T>
void PerfectForward(T&& t)//注意这里是模板的&&，此处就是万能引用，接受左值会产生折叠，右值直接接受
{
	Fun(t);//这里传参过去的属性一定是左值，举例如果不是左值，那么移动构造函数和移动复制函数就无法进行修改
	//那么如何要保持这里的右值属性呢？
	//完美转发：
	//Fun(forward<T>(t));
}

void test_cpp11_5()
{
	PerfectForward(10); // 右值
	int a;
	PerfectForward(a); // 左值
	PerfectForward(std::move(a)); // 右值
	const int b = 8;
	PerfectForward(b); // const 左值
	PerfectForward(std::move(b)); // const 右值
}
	

namespace bit
{
	template<class T>
	struct ListNode
	{
		ListNode* _next = nullptr;
		ListNode* _prev = nullptr;
		T _data;
	};

	template<class T>
	class List
	{
		typedef ListNode<T> Node;
	public:
		List()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		template<class Ty>
		void PushBack(Ty&& x)//请注意前面的T是实例化的类型，这里的Ty是万能引用需要自己退到的类型，如果进行了实例化T&&就属于了右值引用！不是万能引用
		{
			//Insert(_head, x);
			Insert(_head, forward<Ty>(x));
		}

		void PushFront(T&& x)
		{
			//Insert(_head->_next, x);
			Insert(_head->_next, forward<T>(x));
		}

		template<class Ty>
		void Insert(Node* pos, Ty&& x)
		{
			Node* prev = pos->_prev;
			Node* newnode = new Node;
			newnode->_data =forward<Ty>(x); // 关键位置
			// prev newnode pos
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = pos;
			pos->_prev = newnode;
		}

		//void Insert(Node* pos, const T& x)
		//{
		//	Node* prev = pos->_prev;
		//	Node* newnode = new Node;
		//	newnode->_data = x; // 关键位置
		//	// prev newnode pos
		//	prev->_next = newnode;
		//	newnode->_prev = prev;
		//	newnode->_next = pos;
		//	pos->_prev = newnode;
		//}
	private:
		Node* _head;
	};
}

//！！！！！！！！！！！！！！！！！！
void test_cpp11_6()
{
	bit::List<int> lt;
	int a = 0;
	const int b = 0;
	lt.PushBack(a);
	lt.PushBack(b);
}

class Date
{
public:
	Date(const int& year=2025,const int& month=4,const int& day=5)
		:_year(year)
		,_month(month)
		,_day(day)
	{ }
public:
	int _year;
	int _month;
	int _day;
};
struct compare
{
	bool operator()(const Date& d1, const Date& d2)
	{
		if (d1._year < d2._year) return true;
		else if (d1._year == d2._year)
		{
			if (d1._month < d2._month) return true;
			else if (d1._month == d2._month)
			{
				if (d1._day < d2._day) return true; else return false;
			}
			else return false;
		}
		else return false;
	}
};
//void test_cpp11_1111()
//{
//	vector<Date> v = { {2006,8,21},{2006,12,28},{2007,7,21} };
//	sort(v.begin(), v.end(),compare() );
//	for (const auto& e : v)
//	{
//		cout << e._year << '-' << e._month << '-' << e._day << endl;
//	}
//}

void test_cpp11_7()
{
	vector<Date> v = { {2006,8,21},{2006,12,28},{2007,7,21} };
	//lameda函数，可以不用去重载（）操作符函数，直接定义
	sort(v.begin(), v.end(), [](const Date& d1, const Date& d2)->bool
		{if (d1._year < d2._year) return true;
		else if (d1._year == d2._year)
		{
			if (d1._month < d2._month) return true;
			else if (d1._month == d2._month)
			{
				if (d1._day < d2._day) return true; else return false;
			}
			else return false;
		}
		else return false; });

	for (const auto& e : v)
	{
		cout << e._year << '-' << e._month << '-' << e._day << endl;
	}

	//补充lameda函数：
	double a = 1.0, b = 2.0, c = 3.0;
	auto add = [](int a,int b) {return a + b; };
	cout << add(a, b) << endl;
	//auto add1 = [](int a, int b) {return add(a, b); };//可以这么调用函数吗？不行，但是可以在结构内调用全局函数
	auto add1 = [](int a, int b) {return func(a); };

	//请注意，参数列表和返回值类型都是可以省略的部分，返回值可以自动推导
	//如果想要使用其他变量，可以捕捉
	auto add2 = [c](int a, int b)mutable { c = 2.0;  return a + b + c; };//那么可以对c进行修改吗？不可以，捕捉的值默认使用const修饰
	//如果想要进行修改可以加上mutable,但是，加上muable也仅仅是对拷贝过来的c进行修改，并不能影响到实参
	//mutable一般没有人用，使用&拷贝更多，而且可以改变实参
	auto add3 = [&c](int a, int b) {c = 2.0; return a + b + c; };

	int A = 1, B = 2,C = 3, D = 4;
	//如果想要全部捕捉，就使用=，引用就使用&
	auto add4 = [=]() {return A+B+C+D; };
	auto add5 = [&]() {A=B=C=D = 0; return A+B+C+D; };

	//需要注意的是add4和add5之间不能互相赋值，本质上这两个都是类名
	cout << typeid(add4).name() << endl;
	cout << typeid(add5).name() << endl;
	//这里会打印出UUID，每个类都有独一无二的UUID，也就是说这两个东西即便一模一样，类名也是不相同的
	//按照底层实现，其实lameda本质就是使用仿函数并且重载（）操作符函数进行实现的，可以通过汇编查看
}


//可变型模板参数
template<class ...Args>
void Showlist(Args...args)//args代表0-N的参数包
{
	cout << sizeof...(args) << endl;//可变模板参数，必须要这么打印参数表的个数

	//for (int i = 0; i < sizeof...(args); i++) { cout << args[i] << endl; }//不能这样进行访问
}

//那么如何进行访问呢？运用递归
template<class T>
int showlist(T t)
{
	cout << t << endl;
	return 0;
}

template<class T, class...Args>
void showlist(T t,Args...args)
{
	cout << t << " ";
	showlist(args...);
}

template<class ...Args>
void cppprint(Args...args)
{
	int a[] = { showlist(args)... };//这里就代表展开，按照参数包的数据个数来开辟数组空间

}

template<class...Args>
void initdate(Args...args)
{
	Date* newdate = new Date(args...);
	return;
}
void test_cpp11_8()
{
	Showlist(1);
	Showlist(1, 11);
	Showlist(1, 11, 111);

	showlist(1);
	showlist(1, 11);
	showlist(1, 11, 111);

	//不仅可以通过上述方式，还有：通过数组展开的方式实现
	cppprint(1);
	cppprint(1, 11);
	cppprint(1, 11, 111);

	//当然，可变模版型参数真正有用的是拷贝场景：
	initdate(2025, 3, 8);
}

void test_cpp11_9()
{
	//c++11中其中新加的emplace用法可以让构造的代价降低
	list<pair<string,string>> hash;
	hash.emplace_back("xxxx", "1234");//这样传递的是参数包，不用makepair，效率与移动构造其实差不多
	hash.push_back(make_pair("insert", "插入"));

}


class funcc
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}

	int Func(int a, int b)
	{
		return a + b;
	}
};

int Func(int a, int b)
{
	return a + b;
}

double Funcc(char a, int b, double c)
{
	return a + b * c;
}
void test_cpp11_10()
{
	//包装器

	//如果想把仿函数，lameda，函数指针放进数组该怎么办，这时需要使用包装器
	//好处在于把则这三个包装成同一类型的东西方便放入数组
	function<int(int,int)> f1 = [](int a, int b) {return a + b; };
	function<int(int,int)> f2 = funcc();
	function<int(int,int)> f3 = Func;
	//包装器中间是返回值加参数包
	vector < function<int(int, int)>> v = { f1,f2,f3 };
	//这样仿函数，函数指针以及lameda可以放进vector

	//bind绑定：
	function<double(char, int)> func1 = bind(Funcc, placeholders::_1, placeholders::_2, 3.1415);
	function<double(char, int)> func2 = bind(Funcc, placeholders::_2, placeholders::_1, 3.1415);
	function<double( int, double)> func3 = bind(Funcc, 3.1415, placeholders::_1, placeholders::_2);
	function<double( int, double)> func4 = bind(Funcc, 3.1415, placeholders::_2, placeholders::_1);	
	function<double(char, double)> func5 = bind(Funcc, placeholders::_1, 3.1415, placeholders::_2);
	function<double(char, double)> func6 = bind(Funcc, placeholders::_2, 3.1415, placeholders::_1);
	cout << func1(1, 2) << endl;
	cout << func2(1, 2) << endl;
	cout << func3(1, 2) << endl;
	cout << func4(1, 2) << endl;
	cout << func5(1, 2) << endl;
	cout << func6(1, 2) << endl;
	//注意placeholders中的_1_2_3代表参数的第几个，部分值在bind的省略，可以实现绑定，但是注意function中的格式
	//括号前代表返回值，括号中代表传参的类型，请注意传参的个数一定要符合（）中的参数个数
	//这里的绑定相较于缺省参数来说：缺省值是死的，这里的值可以多变

	function<int(int, int)> func7 = bind(&funcc::Func, funcc(), placeholders::_1, placeholders::_2);
	//请注意，上面func7，第一个参数需要函数地址，其实第一个参数也可以传参仿函数lambda表达式或者函数指针，bothok
	//第二个参数需要隐藏的this指针，但是这里属于临时对象右值不能够取地址
}


int main()
{
	//test_cpp11_1();
	//test_cpp11_4();
	//practice1();
	test_cpp11_7();
	

	return 0;
}