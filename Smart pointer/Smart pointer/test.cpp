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

// ʹ��RAII˼����Ƶ�SmartPtr��
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
			cout << "��Դ���ͷ�" << endl;
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
		throw invalid_argument("��0����");
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
	//������ϰһ���쳣
	vector<int> v;
	try
	{
		v.reserve(10000000000000000);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	//����ʹ���׳����쳣��

	//ΪʲôҪ��������ָ�룿���һ���������׳�֮ǰ��Ҫ�ͷţ�����һ��ͻ᲻��������ֶ��ͷţ�����ʹ������ָ��

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
	//c++98���ṩauto_ptr
	bit::auto_ptr<A> ap1(new A(1));
	bit::auto_ptr<A> ap2(new A(2));
	//����Ȩת�ƣ���ѱ������������Դ����Ȩ����������
	//���������±������������գ����ʻ��������
	bit::auto_ptr<A> ap3(ap1);
	//������sp1ȥ����sp3�ͻ����ָ�����յ�����
	//(ap1->a)++;//sp1����Ϊ�պ���ȥ���ʾͻᱨ��
	(ap2->a)++;


	//boost			c++11
	//scoped_ptr	unique_ptr
	//shared_ptr	shared_ptr
	//weak_ptr		weak_ptr

	bit::unique_ptr<A> up1(new A(1));
	bit::unique_ptr<A> up2(new A(2));
	//unique_ptrֱ�ӽ����˷�������������ֹ������ָ�뿽����Ϊ
	//bit::unique_ptr<A> up3(up1);

	bit::shared_ptr<A> sp1(new A(1));
	bit::shared_ptr<A> sp2(new A(2));
	bit::shared_ptr<A> sp3(sp1);//����֧�ֿ���������Ϊʵ�������ü���

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
	//_prev����sp1��_next����sp2
	//ʲôʱ��_prev������sp2����ʱ��ʼ����
	//sp2ʲôʱ��������_next����ʱ��ʼ����
	//_nextʲôʱ��ʼ������sp1����ʱ��ʼ����
	//sp1ʲôʱ��ʼ������_prev����ʱ��ʼ����
	//�����������ѭ��������shared_ptr����Ѩ
	//���Ľ����sp1sp2����ʱ���ü�������1����������A����ڴ�й¶

	//�����Node��ʹ��weak_ptr,weakptr������sharedptr�����죬����ר���������ѭ����
	//�������ǲ��Թ����������ü������иı䣬ʹ����ѭ��������������
	//weak_ptr������RAII�����Բ�����Դ�ķ��ʣ����ǲ�������Դ���ͷţ���������ָ�룡
	//����ʵweakptr�ĵײ�ʵ��ʹ����ǿ�����ü���
}


//����ָ���ܽ᣺
//auto_ptr ����Ȩת�ƣ��ᵼ�±������������գ����鲻Ҫʹ����
//unique_ptr ��ֹ�������򵥴ֱ�ʵ���˷�����������Ҫ�����ĳ���������ʹ����
//shared_ptr ���ü���֧�ֿ�������Ҫ�����ĳ�������ʹ������ҪС�Ĺ���ѭ������
//weak_ptr shared_ptr��ר��ָ�룬������RAII�ķ���

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
	//���new��һ�����飬�ָ�����ͷ��أ�
	//�˽ⶨ��ɾ������new A[10]
	//template <class U, class D> shared_ptr (U* p, D del);
	//template <class D> shared_ptr(nullptr_t p, D del);
	//��������ģ��D�����ƣ���ʵ�Ƿº���,ͬʱҲ���Խ���lameda���ʽ
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