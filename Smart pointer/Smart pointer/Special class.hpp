#pragma once
#include<vector>
#include<iostream>
#include<list>
#include<map>
#include<functional>
#include<memory>
#include<unordered_map>
using namespace std;

//设计一个不能被拷贝的类
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


//请设计一个只能在堆上创建对象的类
class Heaponly1
{
public:
	Heaponly1()
	{ }

	void Delete()
	{
		delete this;//巧妙
	}

private:
	~Heaponly1()
	{
		//...
	}

	//要防止在栈上创建空间，还要将拷贝构造和复制构造delete
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

//设计一个只能在栈上创建对象的类
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


//设计一个不能被继承的类
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
		//派生类要调用基类的构造函数，如果隐藏就不能被继承
	}
};


//实现一个只能创建一个对象的类：单例模式
//饿汉模式：不管是否用上，首先实例化一个变量
//1.如果单例对象初始化内容很多，就会影响启动速度
//2.如果与其他对象形成依赖关系，要求先创建A再创建B，无法做到
//因为无法确定实例顺序


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
		//先将构造函数私有化，防止轻易构造新对象
		Singleton()
		{}

		//以hash表为例子
		unordered_map<string, string> hash;

		//如何确保只有一个对象？使用static
		static Singleton slt;

		//!!!记住要防止拷贝
		Singleton& operator=(const Singleton& st) = delete;
		Singleton(const Singleton& st) = delete;
	};

	Singleton Singleton::slt;//这里有点小奇怪，就理解为用singleton实例化singletion的slt吧
}

//懒汉模式：直接用指针代替，需要的时候再进行实例化
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
		// 一般单例不用释放。
		// 特殊场景：1、中途需要显示释放  2、程序结束时，需要做一些特殊动作（如持久化）,比如写入文件
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
				//垃圾回收站，这是为了方便多个单例对象需要持久化或者手动释放使用的
				Singleton::Delete();
			}
		};
	private:
		//先将构造函数私有化，防止轻易构造新对象
		Singleton()
		{
		}

		~Singleton()
		{
			//在这里可以做一些持久化操作，将数据写入文件
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
	//上面两种都不能创建
	Heaponly1* newnode = new Heaponly1;//必须堆上开辟才可以创建成功
	newnode->Delete();

	Heaponly2* newnode1 = Heaponly2::Create();

	//Stackonly1* newnode2 = new Stackonly1;
	Stackonly1 newnode2 = Stackonly1::Create();
	Stackonly2 newnode3;
	//Stackonly2 newnode4 = new Stackonly2;//new->operator new->constructor
	//禁用opearator new后就可以
	//Stackonly2 newnode4 = new Stackonly2(newnode3);//同时也要防止这样的情况发生

	hungry::Singleton& newnode5 = hungry::Singleton::Create();
	newnode5.Add({ "12345","上山打老虎" });
	newnode5.Add({ "老虎打不到","打到小松鼠" });
	hungry::Singleton& newnode6 = hungry::Singleton::Create();
	cout << &newnode5 << "  " << &newnode6 << endl;
	newnode5.print();

	lazy::Singleton& newnode7 = lazy::Singleton::Create();
	newnode7.Add({ "12345","上山打老虎" });
	newnode7.Add({ "老虎打不到","打到小松鼠" });
	lazy::Singleton& newnode8 = lazy::Singleton::Create();
	cout << &newnode7 << "  " << &newnode8 << endl;
	newnode7.print();

}


