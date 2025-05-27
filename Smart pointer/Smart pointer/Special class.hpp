#pragma once
#include<vector>
#include<iostream>
#include<list>
#include<map>
#include<functional>
#include<memory>
#include<unordered_map>
using namespace std;

//���һ�����ܱ���������
//c++98
class Uncopyclass1
{
private:
	Uncopyclass1(const Uncopyclass1& uc);
	Uncopyclass1& operator=(const Uncopyclass1& uc);

};

//c++11
class Uncopyclass2
{
public:
	Uncopyclass2(const Uncopyclass2& uc) = delete;
	Uncopyclass2& operator=(const Uncopyclass2& uc) = delete;

}; 


//�����һ��ֻ���ڶ��ϴ����������
class Heaponly1
{
public:
	Heaponly1()
	{ }

	void Delete()
	{
		delete this;//����
	}

private:
	~Heaponly1()
	{
		//...
	}

	//Ҫ��ֹ��ջ�ϴ����ռ䣬��Ҫ����������͸��ƹ���delete
	Heaponly1& operator=(const Heaponly1& hp) = delete;
	Heaponly1(const Heaponly1& hp) = delete;
};

class Heaponly2
{
public:
	static Heaponly2* Create()
	{
		return new Heaponly2;
	}
private:
	Heaponly2()
	{
		//...
	}

	Heaponly2& operator=(const Heaponly2& hp) = delete;
	Heaponly2(const Heaponly2& hp) = delete;
};

//���һ��ֻ����ջ�ϴ����������
class Stackonly1
{
public:
	static Stackonly1 Create()
	{
		Stackonly1 st;
		return st;
	}
private:
	Stackonly1()
	{

	}
};

class Stackonly2
{
public:
	Stackonly2()
	{ }
private:
	void* operator new(size_t size) = delete;
};


//���һ�����ܱ��̳е���
//c++11
class Uninheritance1 final
{

};

//c++98
class Uninheritance2
{
public:
	static Uninheritance2* Create()
	{
		return new Uninheritance2;
	}
private:
	Uninheritance2()
	{
		//������Ҫ���û���Ĺ��캯����������ؾͲ��ܱ��̳�
	}
};


//ʵ��һ��ֻ�ܴ���һ��������ࣺ����ģʽ
//����ģʽ�������Ƿ����ϣ�����ʵ����һ������
//1.������������ʼ�����ݺܶ࣬�ͻ�Ӱ�������ٶ�
//2.��������������γ�������ϵ��Ҫ���ȴ���A�ٴ���B���޷�����
//��Ϊ�޷�ȷ��ʵ��˳��


namespace hungry
{
	class Singleton
	{
	public:
		static Singleton& Create()
		{
			return slt;
		}

		bool Add(const pair<string, string>& kv)
		{
			hash.insert(kv);
			return true;
		}

		void print()
		{
			for (const auto& e : hash)
			{
				cout << e.first << " " << e.second << endl;
			}
		}
	private:
		//�Ƚ����캯��˽�л�����ֹ���׹����¶���
		Singleton()
		{}

		//��hash��Ϊ����
		unordered_map<string, string> hash;

		//���ȷ��ֻ��һ������ʹ��static
		static Singleton slt;

		//!!!��סҪ��ֹ����
		Singleton& operator=(const Singleton& st) = delete;
		Singleton(const Singleton& st) = delete;
	};

	Singleton Singleton::slt;//�����е�С��֣������Ϊ��singletonʵ����singletion��slt��
}

//����ģʽ��ֱ����ָ����棬��Ҫ��ʱ���ٽ���ʵ����
namespace lazy
{
	class Singleton
	{
	public:
		static Singleton& Create()
		{
			if (slt == nullptr)
			{
				slt = new Singleton;
				return *slt;
			}
			else
			{
				return *slt;
			}
		}
		// һ�㵥�������ͷš�
		// ���ⳡ����1����;��Ҫ��ʾ�ͷ�  2���������ʱ����Ҫ��һЩ���⶯������־û���,����д���ļ�
		static void Delete()
		{
			if (slt)
			{
				delete slt;
				slt = nullptr;
			}
			else return;
		}

		bool Add(const pair<string, string>& kv)
		{
			hash.insert(kv);
			return true;
		}

		void print()
		{
			for (const auto& e : hash)
			{
				cout << e.first << " " << e.second << endl;
			}
		}

		class GC
		{
		public:
			~GC()
			{
				//��������վ������Ϊ�˷���������������Ҫ�־û������ֶ��ͷ�ʹ�õ�
				Singleton::Delete();
			}
		};
	private:
		//�Ƚ����캯��˽�л�����ֹ���׹����¶���
		Singleton()
		{
		}

		~Singleton()
		{
			//�����������һЩ�־û�������������д���ļ�
			cout << "destructor" << endl;
		}

		unordered_map<string, string> hash;

		static Singleton* slt;
		static Singleton::GC gc;

		Singleton& operator=(const Singleton& st) = delete;
		Singleton(const Singleton& st) = delete;
	};

	Singleton* Singleton::slt=nullptr;
	Singleton::GC Singleton::gc;
}


void test_sp5()
{
	//Heaponly1 sp1;
	//static Heaponly1 sp2;
	//�������ֶ����ܴ���
	Heaponly1* newnode = new Heaponly1;//������Ͽ��ٲſ��Դ����ɹ�
	newnode->Delete();

	Heaponly2* newnode1 = Heaponly2::Create();

	//Stackonly1* newnode2 = new Stackonly1;
	Stackonly1 newnode2 = Stackonly1::Create();
	Stackonly2 newnode3;
	//Stackonly2 newnode4 = new Stackonly2;//new->operator new->constructor
	//����opearator new��Ϳ���
	//Stackonly2 newnode4 = new Stackonly2(newnode3);//ͬʱҲҪ��ֹ�������������

	hungry::Singleton& newnode5 = hungry::Singleton::Create();
	newnode5.Add({ "12345","��ɽ���ϻ�" });
	newnode5.Add({ "�ϻ��򲻵�","��С����" });
	hungry::Singleton& newnode6 = hungry::Singleton::Create();
	cout << &newnode5 << "  " << &newnode6 << endl;
	newnode5.print();

	lazy::Singleton& newnode7 = lazy::Singleton::Create();
	newnode7.Add({ "12345","��ɽ���ϻ�" });
	newnode7.Add({ "�ϻ��򲻵�","��С����" });
	lazy::Singleton& newnode8 = lazy::Singleton::Create();
	cout << &newnode7 << "  " << &newnode8 << endl;
	newnode7.print();

}


