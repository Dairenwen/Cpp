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
//	explicit A(int a = 0)//����explicit��ֹ��ʽ����ת��
//		:a(a)
//	{
//
//	}
//private:
//	int a;
//
//};
//c++������ת��
void test1()
{
	//c++����c,֧����ʽ����ת���Լ���ʽ����ת��
	double a = 1.1;
	int b = a;//��ʽ����

	int c = (int)a;//��ʾ����

	//��������Ҳ֧����˽������ת������
	//A d = 1;
	
}

void test2()
{
	volatile const int a = 1;
	int* p = (int*)&a;
	(*p)++;
	cout << a << " " << *p << endl;//����a��ӡֵ���ᱻ�޸ģ�����ʱ������Ĵ�����
	//�޸ĵ�ֻ���ڴ��е�ֵ��������ڴ�ȡֵ��ӡ������volatile�ؼ���
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
	//��ע������ֻ�����ڶ�̬���ͣ����û��ʵ���麯��Ҳ��û��ʵ�ֶ�̬������ʹ��
	//dynamic_cast����ת������ɹ�����ת�����ָ��
	//���ת��ʧ�ܷ��ؿ�ָ��
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
	//C++����Ҫ������ǿ������ת����ʶ
	double a = 3.14;
	int b = static_cast<int>(a);//�м�ʵ����ҪתΪ������
	//static�����ھ���һ����ϵ������
	//string c = static_cast<string>(a);//�����ͻ����
	//��Ҫ���ڻ�����������֮���ת�����Լ����м̳й�ϵ����ָ�������֮���ת�������ڱ���ʱ�������ͼ�顣


	double* c = reinterpret_cast<double*>(b);//reinterpret����ǿ������ת������û�й�ϵ�ı���
	//�����Խ��������͵�ָ�������ת��Ϊ�������͵�ָ������ã��������Խ�ָ��ת��Ϊ��������
	//�Ƚ�Σ�գ����ã�

	volatile const int d = 10;
	int* e = const_cast<int*>(&d);
	(*e)++;
	const int& f = 10;
	int* h = const_cast<int*>(&f);
	//constcastȥ�������ָ�롢���õ�const���ԣ���������ȥ�����������const��

	A A; B B;
	A = B;//���������Ƭ��ֵ����
	//B = A;//��������Ϊ���ڷ��գ����ܻ�Խ�����
	//����ת�ͣ��������ָ�� / ����->����ָ�� / ����(����Ҫת������ֵ���ݹ���)
	//����ת�ͣ��������ָ�� / ����->����ָ�� / ����(��dynamic_castת���ǰ�ȫ��)
	//ʹ��dynamiccast���Խ��м��
	func(&A); 
	cout << "\n";
	func(&B);
}

//RTTI ����ʱ����ʶ��
//. typeid�����
//2. dynamic_cast�����
//3. decltype


class AA
{
public:
	AA(int a=0)
		:a(a)
	{ }

	//Ϊʲô������operator ()��Ϊ�º������Ѿ����ڣ���������ͻ
	explicit operator int()//ΪʲôҪ����explicit��������Ϊ�˷ſ�ת�����˽⼴��
	{
		//�����û�з���ֵ
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
	//����ڶ�ȡ�����а���ctrlcֱ�ӽ����˽���
	//����ctrlz�Ϳո���ȷ��������

	//����ѭ����ȡ��ԭ����ʲô��
	//�����Զ�������AA
	AA aa = 1;
	int bb = aa;//�����Ƿ�����أ�ʹ��operator int����
	//˵��operator�������ֺ����Ǵ��ڵ�
	double cc = aa;

	while (cin >> a)//�ȵ���operator>>,�ٵ���operator bool�жϷ���ֵ
	{//operator>>(cin, str).operator bool()
		cout << a << endl;
	}

	while (cin >> a >> b)//cin.operator>>(a).operator>>(b).operator bool()
	{
		cout << a << b << endl;
	}
}

