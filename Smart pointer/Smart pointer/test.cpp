#define _CRT_SECURE_NO_WARNINGS 1
#include<vector>
#include<iostream>
#include<list>
#include<map>
#include<functional>
#include<memory>
#include"SmartPtr.hpp"
#include<unordered_map>
#include"Special class.hpp"
using namespace std;

// 使用RAII思想设计的SmartPtr类
template<class T>
class SmartPtr {
public:
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr)
	{
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~SmartPtr()
	{
		if (_ptr)
		{
			cout << "资源已释放" << endl;
			delete _ptr;
		}
	}

private:
	T* _ptr;
};

int div()
{
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("除0错误");
	return a / b;
}

void Func()
{
	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2(new int);
	SmartPtr<string> sp3(new string("Darling in the FRANXX"));
	SmartPtr<pair<string, string>> sp4(new pair<string, string>{ "016","002" });
	cout << sp4->first << " " << *sp3 << " " << sp4->second << endl;
	try
	{
		div();
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}

}

void test_sp1()
{
	//先来复习一下异常
	vector<int> v;
	try
	{
		v.reserve(10000000000000000);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	//这样使用抛出的异常，

	//为什么要存在智能指针？如果一个数据在抛出之前需要释放，数量一多就会不方便进行手动释放，必须使用智能指针

}

class A
{
public:
	A(int _a=1)
		:a(_a)
	{
		cout << "class A has been created" << endl;
	}

	~A()
	{
		cout << "class A has been deleted" << endl;
	}

	int a;
};
void test_sp2()
{
	//c++98中提供auto_ptr
	bit::auto_ptr<A> ap1(new A(1));
	bit::auto_ptr<A> ap2(new A(2));
	//管理权转移，会把被拷贝对象的资源管理权给拷贝对象
	//隐患：导致被拷贝对象悬空，访问会出现问题
	bit::auto_ptr<A> ap3(ap1);
	//这里用sp1去构造sp3就会出现指针悬空的问题
	//(ap1->a)++;//sp1被置为空后再去访问就会报错
	(ap2->a)++;


	//boost			c++11
	//scoped_ptr	unique_ptr
	//shared_ptr	shared_ptr
	//weak_ptr		weak_ptr

	bit::unique_ptr<A> up1(new A(1));
	bit::unique_ptr<A> up2(new A(2));
	//unique_ptr直接进行了反拷贝操作，禁止了这种指针拷贝行为
	//bit::unique_ptr<A> up3(up1);

	bit::shared_ptr<A> sp1(new A(1));
	bit::shared_ptr<A> sp2(new A(2));
	bit::shared_ptr<A> sp3(sp1);//这里支持拷贝，是因为实现了引用计数

	sp2 = sp3;
}

struct Node
{
	A a;
	shared_ptr<Node> _next;
	shared_ptr<Node> _prev;
};

struct NodePlus
{
	A a;
	bit::weak_ptr<NodePlus> _next;
	bit::weak_ptr<NodePlus> _prev;
};
void test_sp3()
{
	bit::shared_ptr<NodePlus> sp1(new NodePlus());
	bit::shared_ptr<NodePlus> sp2(new NodePlus());
	

	sp1->_next = sp2;
	sp2->_prev = sp1;
	//_prev管着sp1，_next管着sp2
	//什么时候_prev析构？sp2析构时开始析构
	//sp2什么时候析构？_next析构时开始析构
	//_next什么时候开始析构？sp1析构时开始析构
	//sp1什么时候开始析构？_prev析构时开始析构
	//这样造成引用循环，属于shared_ptr的死穴
	//最后的结果是sp1sp2析构时引用计数还是1，不能析构A造成内存泄露

	//解决：Node中使用weak_ptr,weakptr可以用sharedptr来构造，并且专门针对引用循环，
	//其作用是不对管理对象的引用计数进行改变，使引用循环可以正常析构
	//weak_ptr不属于RAII，可以参与资源的访问，但是不参与资源的释放，属于智能指针！
	//但其实weakptr的底层实现使用了强弱引用计数
}


//智能指针总结：
//auto_ptr 管理权转移，会导致被拷贝对象悬空，建议不要使用它
//unique_ptr 禁止拷贝，简单粗暴实现了反拷贝，不需要拷贝的场景，建议使用它
//shared_ptr 引用计数支持拷贝，需要拷贝的场景，就使用它，要小心构成循环引用
//weak_ptr shared_ptr的专用指针，不属于RAII的范畴

template<class T>
struct Destroy
{
	void operator()(T* ptr)
	{
		delete ptr;
	}
};

void test_sp4()
{
	//如果new了一个数组，又该如何释放呢？
	//了解定制删除器：new A[10]
	//template <class U, class D> shared_ptr (U* p, D del);
	//template <class D> shared_ptr(nullptr_t p, D del);
	//库中用了模板D来控制，其实是仿函数,同时也可以接收lameda表达式
	std::shared_ptr<A> sp1(new A[10], [](const A* ptr) { delete[] ptr; });
	std::shared_ptr<A> sp2((A*)malloc(sizeof(A)*10), Destroy<A>());
	std::shared_ptr<FILE> sp3(fopen("SmartPtr.hpp", "r"), [](FILE* ptr) {return fclose(ptr); });
}


int main()
{
	//test_sp1();
	//Func();
	//test_sp4();
	test_sp4();

	return 0;
}