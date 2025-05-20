#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<list>
#include<windows.h>
#include<queue>
#include<algorithm>
using namespace std;
//笔记：C语言中要么使用assert强制终止程序，要么打印错误码
//错误码需要去查找含义
//而c++中存在异常的概念

//通常在try中写入可能出现异常的代码，用catch来捕获，对于C语言错误码需要层层返回，而异常可以
//从throw的位置直接跳到catch，出现异常后会依次前往上一层寻找捕捉catch，如果上一层存在，
//那么就不会再被后面的catch捕捉，也就是调用最近的catch
//double Division(int a, int b)
//{
//	// 当b == 0时抛出异常
//	string ss("Division by zero condition!");
//	if (b == 0)
//		//throw 1;
//		throw ss;//这里的异常抛出字符串，如果类型不匹配，那么就会捕捉不到
//	//如果是自定义类型返回，会返回拷贝，原型正常完成析构
//	else
//		return ((double)a / (double)b);
//}
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	cout << Division(len, time) << endl;//异常会现在这个函数寻找，如果有catch就不会被其他catch捕捉
//}


int test1()
{
	try {
		//Func();//如果func没有在try的范围内，那么错误就不会被捕捉到
	}
	catch (const string errmsg)
	{
		cout << errmsg << endl;
	}
	catch (...) //用来捕捉不知道什么类型或者不规范的异常，防止异常被抛出不被捕获导致程序异常结束
	{//未知异常必须放到最后！
		cout << "unkown exception" << endl;
	}//如果异常直到程序结束都没有被捕捉，那么就会强制报错
	//找到catch语句执行完后，会继续执行后面的程序
	return 0;
}

//实际工作当中，一般会返回一个自定义类型，会根据自定义类型的chat和int id去对不同的错误编号分辨做出不同的处理
//因此返回的自定义类型包含多个异常信息是必要的
void test2()
{
	vector<int> v;
	try
	{
		v.reserve(10000000000000);
		//v[9999999999910000000];
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		//常用的是bad_alloc out_of_range 两种异常
	}
}
// 服务器开发中通常使用的异常继承体系
class Exception
{
public:
	Exception(const string& errmsg, int id)
		:_errmsg(errmsg)
		, _id(id)
	{
	}
	virtual string what() const
	{
		return _errmsg;
	}
protected:
	string _errmsg;
	int _id;
};
class SqlException : public Exception
{
public:
	SqlException(const string& errmsg, int id, const string& sql)
		:Exception(errmsg, id)
		, _sql(sql)
	{
	}
	virtual string what() const
	{
		string str = "SqlException:";
		str += _errmsg;
		str += "->";
		str += _sql;
		return str;
	}
private:
	const string _sql;
};
class CacheException : public Exception
{
public:
	CacheException(const string& errmsg, int id)
		:Exception(errmsg, id)
	{
	}
	virtual string what() const
	{
		string str = "CacheException:";
		str += _errmsg;
		return str;
	}
};
class HttpServerException : public Exception
{
public:
	HttpServerException(const string& errmsg, int id, const string& type)
		:Exception(errmsg, id)
		, _type(type)
	{
	}
	virtual string what() const
	{
		string str = "HttpServerException:";
		str += _type;
		str += ":";
		str += _errmsg;
		return str;
	}
private:
	const string _type;
};
void SQLMgr()
{
	srand(time(0));
	if (rand() % 7 == 0)
	{
		throw SqlException("权限不足", 100, "select * from name = '张三'");
	}
	//throw "xxxxxx";
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("权限不足", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("数据不存在", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("请求资源不存在", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("权限不足", 101, "post");
	}
	CacheMgr();
}
//在函数调用链中异常栈展开匹配原则
//1. 首先检查throw本身是否在try块内部，如果是再查找匹配的catch语句。如果有匹配的，则
//调到catch的地方进行处理。
//2. 没有匹配的catch则退出当前函数栈，继续在调用函数的栈中进行查找匹配的catch。
//3. 如果到达main函数的栈，依旧没有匹配的，则终止程序。上述这个沿着调用链查找匹配的
//catch子句的过程称为栈展开。所以实际中我们最后都要加一个catch(...)捕获任意类型的异
//常，否则当有异常没捕获，程序就会直接终止。
//4. 找到匹配的catch子句并处理以后，会继续沿着catch子句后面继续执行。
int test3()
{
	//test2();
	while (1)
	{
		Sleep(1000);
		try {
			HttpServer();
		}
			catch (const Exception& e) // 这里捕获父类对象就可以
		{//这里就是将派生类传递给基类，进行多态的调用
			// 多态
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}

//异常规范：在函数后加上throw(异常类型1，异常类型2）,来说明这个函数可能抛出的异常
//如果是throw（）就代表不抛出异常
//c++11更新：noexcept则表示不会抛出异常

//最好不要在构造函数和析构函数中抛异常，否则会导致初始化不完全或者内存泄漏
//当想要将异常统一处理时，可以暂时接收后再次抛出

double Divisiond(int a, int b)
{
	// 当b == 0时抛出异常
	if (b == 0)
	{
		throw "Divisiond by zero condition!";
	}
	return (double)a / (double)b;
}
void Funcc()
{
	// 这里可以看到如果发生除0错误抛出异常，另外下面的array没有得到释放。
	// 所以这里捕获异常后并不处理异常，异常还是交给外面处理，这里捕获了再
	// 重新抛出去。
	int* array = new int[10];
	try {
		int len, time;
		cin >> len >> time;
		cout << Divisiond(len, time) << endl;
	}
	catch (...)//接收任意类型异常
	{
		cout << "delete []1" << array << endl;
		delete[] array;
		//throw;可以抛出任意类型的异常
		throw;//如果在这里再次抛出，那么array就没有释放，所以在抛出之前要进行析构
	}
	// ...
	cout << "delete []2" << array << endl;
	delete[] array;
}

//异常相比于assert和错误码来说，具有方便快捷的优先，assert在release版本下不生效，且在一些特殊函数中不好返回
//一个特定的具体值，那么这时候使用异常恰当

//缺点：会乱跳，导致程序的调试程序可能会相当麻烦
//异常throw都是拷贝传值返回，性能会有一定开销
//有一定概率会导致内存泄漏
//使用异常时一定要规范化，使用throw来说明异常的类型，否则会让捕捉变得极其麻烦
int main()
{
	test2();
	//test3();
	try
	{
		Funcc();
	}
	catch (const char* errmsg)
	{
		cout << errmsg << endl;
	}
	cout << "xxxxxxxxx" << endl;
	return 0;
}


