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
//class D :public B, public C//����ᰴ�ռ̳�˳����
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
//	//��ΪA�����������ȵ���A�Ĺ��캯��������A�Ĺ��캯��ֻ�ܵ���һ�Σ��̳еĻ��൱Ȼ������ÿ�ζ���������
//	delete p;
//
//	B b("class A", "class B");
//
//	return 0;
//}


// �麯����д��һЩϸ�ڣ�
// ��д�������������麯��+����ֵ���͡��������֡������б���ȫ��ͬ��������һЩ����
// 1�����������д�麯�����Բ���virtual -- �������Ҷ����ϣ��п����Ƿ���������������������ü���virtual�����ǽ������
// 2��Э�䣬���ص�ֵ���Բ�ͬ������Ҫ�󷵻�ֵ�����Ǹ��ӹ�ϵָ������ã������ټ����ã����ǲ��������ӣ���

class Person1 {
public:
	virtual	void BuyTicket() const { cout << "��Ʊ-ȫ��" << endl; }
};

class Student1 : public Person1 {
public:
	void BuyTicket() const { cout << "��Ʊ-���" << endl; }
};

class a
{};

class b : public a
{};

class Person2 {
public:
	virtual	a* BuyTicket() const { 
		cout << "��Ʊ-ȫ��" << endl;
		return 0;
	}
};

class Student2 : public Person2 {
public:
	virtual b* BuyTicket() const { 
		cout << "��Ʊ-���" << endl;
		return 0;
	}
};

// ��̬����
// 1�����ú�������д���麯��
// 2������ָ���������
//���ֻ�Ǵ�ֵ�ĵ��ã���ô���ݱ���������ȥ����
//�����ָ��������òŻᷢ����̬������ָ��Ķ������

// ��̬����ͬ���󴫵ݹ�ȥ�����ò�ͬ����
// ��̬���ÿ���ָ��Ķ���
// ��ͨ���󣬿���ǰ������
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
	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
	virtual ~Person3() { cout << "~Person3()" << endl; }
};

class Student3 : public Person3 {
public:
	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }

	virtual~Student3() {
		cout << "~Student3()" << endl;
		delete[] ptr;
	}

protected:
	int* ptr = new int[10];
};
//
// ���������������麯����Ϊʲô��Ҫ���麯����
// ����������virtual���ǲ����麯����д��
// �ǣ���Ϊ�������������������destructor���ͳһ������
// ΪʲôҪ��ô�����أ���ΪҪ�����ǹ�����д
// ��ΪʲôҪ�����ǹ�����д�أ�
// ��Ϊ����ĳ���
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

	// ������������p->destructor()��һ����̬���ã���������ͨ����
	//�������ͨ���ã���ô�ͻ����person���������������student��������

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
class Car
{
public:
	virtual void Drive() final {}//final�������ڲ�����д
};

class Benz :public Car
{
public:
	void Drive(int i) { cout << "Benz-����" << endl; }
};

class Carc {
public:
	 virtual void Drive() {}
};

// override ������������Ƿ������д�����û�лᱨ��
class Benzb :public Carc {
public:
	virtual void Drive() override { cout << "Benz-����" << endl; }
};

// ��Ʋ��뱻�̳��࣬�����ƣ�
// ����1�����๹�캯��˽��   (C++98)
// ����2�������һ��final  ��C++11��
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




// ���ﳣ��һ�������⣺sizeof(Base)�Ƕ��٣�
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
//��Ϊ��ָ����ַ���Ϊ8

void Func(Person3& p)
{
	// ���϶�̬������ʱ��ָ�������麯�������ҵ��ú����ĵ�ַ
	p.BuyTicket();
}

//�麯����ʵ����д/���ǣ�
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
//�����B->1����ôΪʲô��������
//�����p��ȥB����Ѱ�ң�û��test����
//��ȥ�̳е�A��Ѱ�ң��ҵ�����*this����test�����������*this��A��
//�����ǻ�����ü���ָ�룬���ҹ�������д�麯�������أ���������ֵ��������ȱʡֵ�Ƿ�һ��û��ϵ��
//��Ϊpָ��B����ô�ͻ�ȥB�е���func�������int valȱʡֵ��ӡ����ȴ����0
//����Ϊ�������е��麯������дvirtual����Ϊ����������Ϣ�̳��Ի��࣬Ҳ����˵A�и��˿տǣ�B����д��ֻ�Ƕ���
//���Խ����B->1

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
//Ϊʲô�������������ͣ����಻�ܸ����ำֵ
//Ϊʲô������Parent�������ֵ������Ҫ��Ƭ��ֵ����ֵ���Ḵ�������ʱ�Ͳ����������ĺ�����
void test4(const Parent& pp)
{
	int a = 0;
	printf("    ջ��%p\n", &a);
	auto b = new int;
	printf("    �ѣ�%p\n", b);
	static int c = 0;
	printf("  ��̬��%p\n", &c);
	const char* arr = "abcdefg";
	printf("��������%p\n", arr);
	Parent p; Son s;
	printf("parent: %p\n", *(int*)&p);//ǿתΪint����ӡ4���ֽڵĵ�ַ��
	printf("   son: %p", *(int*)&s);

	
}

//��̬���ʵ�֣����/�麯����������̳�ʱ�Ὣ������麯����������������к�����д����ô�͸�����һ�������ĵ�ַ
//��ʵ������ռ�ÿռ�ľ��ǳ�Ա��������һ��ָ�룬ʲôָ�룿_vfptr,��������ĵ�ַ
//�������һ������ָ�����飬ͨ����vs���������һ��Ԫ�ش洢����nullptr���ڴ�����¿�������0
//ֻ���麯���Ż�Ž�����������ͨ�����򲻻�Ž����
//������������в�ͬ�ڻ�����µ��麯������ô���Ӵ����ǿ������ģ�����ͨ���ڴ�ȥ��
//���������Ĵ洢λ�ã�������֤���洢�ڳ�����,���麯�����ڴ����
typedef void(*ptr)();

void test5(ptr* arr)
{
	for (size_t i = 0; arr[i] != nullptr; i++)
	{
		printf("_vfptr[%d]:%p\n", i, arr[i]);
		//arr[i]();
	}
}
//����ǵ��̳У���ô��������麯���ͻ��������������Ƕ�̳У���ô��������麯������ڵ�һ������麯������
//���һ�̳����л��������Լ���������������Լ����麯���ŵ���һ�����������
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
//	cout << " ����ַ>" << vTable << endl;
//	for (int i = 0; vTable[i] != nullptr; ++i)
//	{
//		printf(" ��%d���麯����ַ :0X%x,->", i, vTable[i]);
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
	virtual void test() = 0;//=0Ϊ���麯���������г����࣬������ʵ����

};
class cx :public chouxiang//�̳���û����дҲ������ʵ����
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
	cx x;//����ֻ�жԴ��麯����д���ſ���ʵ���������麯���淶�������������д�������ֳ��˽ӿڼ̳�
}