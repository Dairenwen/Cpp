#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<list>
#include<windows.h>
#include<queue>
#include<algorithm>
using namespace std;
//�ʼǣ�C������Ҫôʹ��assertǿ����ֹ����Ҫô��ӡ������
//��������Ҫȥ���Һ���
//��c++�д����쳣�ĸ���

//ͨ����try��д����ܳ����쳣�Ĵ��룬��catch�����񣬶���C���Դ�������Ҫ��㷵�أ����쳣����
//��throw��λ��ֱ������catch�������쳣�������ǰ����һ��Ѱ�Ҳ�׽catch�������һ����ڣ�
//��ô�Ͳ����ٱ������catch��׽��Ҳ���ǵ��������catch
//double Division(int a, int b)
//{
//	// ��b == 0ʱ�׳��쳣
//	string ss("Division by zero condition!");
//	if (b == 0)
//		//throw 1;
//		throw ss;//������쳣�׳��ַ�����������Ͳ�ƥ�䣬��ô�ͻᲶ׽����
//	//������Զ������ͷ��أ��᷵�ؿ�����ԭ�������������
//	else
//		return ((double)a / (double)b);
//}
//void Func()
//{
//	int len, time;
//	cin >> len >> time;
//	cout << Division(len, time) << endl;//�쳣�������������Ѱ�ң������catch�Ͳ��ᱻ����catch��׽
//}


int test1()
{
	try {
		//Func();//���funcû����try�ķ�Χ�ڣ���ô����Ͳ��ᱻ��׽��
	}
	catch (const string errmsg)
	{
		cout << errmsg << endl;
	}
	catch (...) //������׽��֪��ʲô���ͻ��߲��淶���쳣����ֹ�쳣���׳����������³����쳣����
	{//δ֪�쳣����ŵ����
		cout << "unkown exception" << endl;
	}//����쳣ֱ�����������û�б���׽����ô�ͻ�ǿ�Ʊ���
	//�ҵ�catch���ִ����󣬻����ִ�к���ĳ���
	return 0;
}

//ʵ�ʹ������У�һ��᷵��һ���Զ������ͣ�������Զ������͵�chat��int idȥ�Բ�ͬ�Ĵ����ŷֱ�������ͬ�Ĵ���
//��˷��ص��Զ������Ͱ�������쳣��Ϣ�Ǳ�Ҫ��
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
		//���õ���bad_alloc out_of_range �����쳣
	}
}
// ������������ͨ��ʹ�õ��쳣�̳���ϵ
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
		throw SqlException("Ȩ�޲���", 100, "select * from name = '����'");
	}
	//throw "xxxxxx";
}
void CacheMgr()
{
	srand(time(0));
	if (rand() % 5 == 0)
	{
		throw CacheException("Ȩ�޲���", 100);
	}
	else if (rand() % 6 == 0)
	{
		throw CacheException("���ݲ�����", 101);
	}
	SQLMgr();
}
void HttpServer()
{
	// ...
	srand(time(0));
	if (rand() % 3 == 0)
	{
		throw HttpServerException("������Դ������", 100, "get");
	}
	else if (rand() % 4 == 0)
	{
		throw HttpServerException("Ȩ�޲���", 101, "post");
	}
	CacheMgr();
}
//�ں������������쳣ջչ��ƥ��ԭ��
//1. ���ȼ��throw�����Ƿ���try���ڲ���������ٲ���ƥ���catch��䡣�����ƥ��ģ���
//����catch�ĵط����д���
//2. û��ƥ���catch���˳���ǰ����ջ�������ڵ��ú�����ջ�н��в���ƥ���catch��
//3. �������main������ջ������û��ƥ��ģ�����ֹ��������������ŵ���������ƥ���
//catch�Ӿ�Ĺ��̳�Ϊջչ��������ʵ�����������Ҫ��һ��catch(...)�����������͵���
//�����������쳣û���񣬳���ͻ�ֱ����ֹ��
//4. �ҵ�ƥ���catch�Ӿ䲢�����Ժ󣬻��������catch�Ӿ�������ִ�С�
int test3()
{
	//test2();
	while (1)
	{
		Sleep(1000);
		try {
			HttpServer();
		}
			catch (const Exception& e) // ���ﲶ�������Ϳ���
		{//������ǽ������ഫ�ݸ����࣬���ж�̬�ĵ���
			// ��̬
			cout << e.what() << endl;
		}
		catch (...)
		{
			cout << "Unkown Exception" << endl;
		}
	}
	return 0;
}

//�쳣�淶���ں��������throw(�쳣����1���쳣����2��,��˵��������������׳����쳣
//�����throw�����ʹ����׳��쳣
//c++11���£�noexcept���ʾ�����׳��쳣

//��ò�Ҫ�ڹ��캯�����������������쳣������ᵼ�³�ʼ������ȫ�����ڴ�й©
//����Ҫ���쳣ͳһ����ʱ��������ʱ���պ��ٴ��׳�

double Divisiond(int a, int b)
{
	// ��b == 0ʱ�׳��쳣
	if (b == 0)
	{
		throw "Divisiond by zero condition!";
	}
	return (double)a / (double)b;
}
void Funcc()
{
	// ������Կ������������0�����׳��쳣�����������arrayû�еõ��ͷš�
	// �������ﲶ���쳣�󲢲������쳣���쳣���ǽ������洦�����ﲶ������
	// �����׳�ȥ��
	int* array = new int[10];
	try {
		int len, time;
		cin >> len >> time;
		cout << Divisiond(len, time) << endl;
	}
	catch (...)//�������������쳣
	{
		cout << "delete []1" << array << endl;
		delete[] array;
		//throw;�����׳��������͵��쳣
		throw;//����������ٴ��׳�����ôarray��û���ͷţ��������׳�֮ǰҪ��������
	}
	// ...
	cout << "delete []2" << array << endl;
	delete[] array;
}

//�쳣�����assert�ʹ�������˵�����з����ݵ����ȣ�assert��release�汾�²���Ч������һЩ���⺯���в��÷���
//һ���ض��ľ���ֵ����ô��ʱ��ʹ���쳣ǡ��

//ȱ�㣺�����������³���ĵ��Գ�����ܻ��൱�鷳
//�쳣throw���ǿ�����ֵ���أ����ܻ���һ������
//��һ�����ʻᵼ���ڴ�й©
//ʹ���쳣ʱһ��Ҫ�淶����ʹ��throw��˵���쳣�����ͣ�������ò�׽��ü����鷳
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


