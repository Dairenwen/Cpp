#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include"string.hpp"
#include<vector>
//template<class T>
//class A
//{
//public:
//	A(int year = 2025, int month = 1, int day = 19)
//	{
//
//	}
//	~A()
//	{
//		printf("1");
//	}
//private:
//	//T* arr;
//	int _year;
//	int _month;
//	int _day;
//};
//template<class T>//作用域就是一个函数或者就是一个类，提取出来就要加上模板
//A<T>::A(int year, int month , int day)//A是类名 A<T>是类型 要区分开来
//{
//	cout << year << "-" << month << "-" << day << endl;
//	this->_year = year;
//	this->_month = month;
//	this->_day = day;
//}
//int main()
//{
//	A<int> a1;
//	A<double> a2;
//	return 0;
//}
//template<class T>
//T Func(const T& a, const T& b)
//{
//	cout << "123" << endl;
//	return a + b;
//}
//template<typename V>//template<class T>
//void Swap(const V& a,const V& b)
//{
//	V tmp = a;
//	a = b;
//	b = tmp;
//}
//int main()
//{
//	int a = 1, b = 0; 
//    double c = 3.1415925, d = 4.2526036;
//	Swap<double>(a, d);
//	return 0;
//}

//int main()
//{
//	try
//	{
//		//A* tmp = new A[10]{ A(2025,1,10),A(2025,1,11) };//先operator new->malloc再构造
//		//delete[] tmp;//先析构再operator free->free
//	}//malloc失败返回空指针 new失败抛异常捕捉
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	//显示实例化
//	Func<int>(1, 3.3);
//	return 0;
//}
//class A
//{
//public:
//	A(int a = 0)
//		: _a(a)
//	{
//		cout << "A():" << this << endl;
//	}
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//private:
//	int _a;
//};
//int main()
//{
//	A* p1 = (A*)malloc(sizeof(A));
//	A* p2 = new A(1);
//	free(p1);
//	delete p2;//这里将delete和C语言中的free混用对于自定义类型来说看不出区别
//	          //但对于内置类型有很大概率会出bug，不是好的代码习惯!
//
//	int* p3 = (int*)malloc(sizeof(int)); 
//	int* p4 = new int;
//	free(p3);
//	delete p4;//这样才是正确回收空间操作，malloc匹配free，new匹配delete
//	A* p5 = (A*)malloc(sizeof(A) * 10);
//	A* p6 = new A[10];//这里可以对A数组进行初始化,可以直接给值，也可以用匿名对象构造初始化
//	//A* p7 = new A[10]{ 1,2,3,4,5,6,7,8,9,10 };
//	//A* p8 = new A[10]{ A(1),A(2),A(3),A(4),A(5),A(6),A(7),A(8),A(9),A(10) };
//	free(p5);
//	delete[] p6;
//	return 0;
//}
using namespace std;
void test1()
{
	string s2(10, 'a');
	string s3;
	string s4(s2, 5);
	string s1("Hello");
	s1.push_back(' ');
	s1.append("World");
	cout << s1 << endl;
	string s5("Hello C plus plus");//string类是在堆上开辟的空间
	for (size_t i = 0; i < s5.size(); i++)
	{
		cout << s5[i];
	}
	cout << endl;
	string::iterator it = s5.begin();//begin指向第一个元素 end指向最后一个元素后面，左闭右开
	while (it != s5.end())
	{
		cout << *it;
	    it++;
	}
	cout << endl;
	for (auto tmp : s5)//范围for本质就是迭代器，不支持迭代器的一定不支持范围for，比如栈
	{
		cout << tmp;
	}
	cout << endl;
	//string::reverse_iterator rit = s5.rbegin();
	auto rit = s5.rbegin();//逆置字符串 使用rbegin获取指向最后一个元素指针 这里不能使用for因为其默认正向输出
	                       //要使用while，并且为了省事，使用auto自动识别类型
	while (rit != s5.rend())
	{
		cout << *rit;//左闭右开 rbegin指向最后一个 rend指向第一个前面
		rit++;
		//这个不用我们使用者考虑，你就正常使用 ，正常++就好了，底层源码实现实际调用的就是--的接口，就是往前走
        //而接口设计者为了能够让begin()和rbegin()这种以统一的方式调用遍历，实际使用上两者是一样的，都是rid++, 而底层实现中，
		// begin()就是往后走，rbegin()的就是往前走（这里底层实现是复用--的接口）

	}
	cout << endl;
}

//// 专门处理int的加法函数
//int Add(int left, int right)
//{
//	return left + right;
//}
//// 通用加法函数
//template<class T>
//T Add(T left, T right)
//{
//	return left + right;
//}
//void Test()
//{
//	Add(1, 2); // 与非模板函数匹配，编译器不需要特化
//	Add<int>(1, 2); // 调用编译器特化的Add版本
//}
void test2()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it;
		it++;
	}
	cout << endl;
	reverse(v.begin(), v.end());
	for (auto tmp : v)
	{
		cout << tmp;
	}
	cout << endl;
}
void test3(const string& st)
{
	string::const_iterator cit = st.begin();
	while (cit != st.end())
	{
		cout << *cit;
		cit++;
	}
	cout << endl;
	string::const_reverse_iterator crit = st.rbegin();
	while (crit != st.rend())
	{
		cout << *crit;
		crit++;
	}
	cout << endl;
}
void test4()
{
	string input;
	cin >> input;//这里跟c语言中scanf和fscanf是一样的 遇到空格或者是\n就会停止读取
	//因此我们需要使用getline(cin,input);
	int length = 0;
	int size = input.size();
	string::reverse_iterator rit = input.rbegin();
	while (length < size && *rit != ' ')
	{
		length++;
		rit++;
	}
	cout << length << endl;
}
void test5()
{
	string s1("ABCD EFGH IJKL");
	string s2;
	auto begin = s1.begin();
	while (begin != s1.end())
	{
		if (*begin == ' ')
		{
			s2 += "20%";
		}
		else
		{
			s2 += *begin;
		}
		begin++;
	}
	cout << s2;
}
void test6()
{
	string s1("https://cplusplus.com/reference/string/string/string/");
	string protocal;
	string domain;
	string left;
	size_t recieve = s1.find("://");
	if (recieve != string::npos)
	{
		protocal = s1.substr(0, recieve);
	}
	size_t accept = s1.find('/', recieve + 3);//find用来找指定字符串，如果找到就返回第一个字符的位置，如果没找到就返回-1
	if (accept != string::npos)
	{
		domain = s1.substr(recieve + 3, accept-(recieve+3));//substr可以用来剪切字符串
	}
	left = s1.substr(accept + 1);
	cout << protocal <<"\n"<< domain<<"\n" << left;
}

//int main()
//{
//	//test4();
//	//test6();
//	Solution s;
//	s.isPalindrome("A man, a plan, a canal: Panama");
//	//test2();
//	//test3("HELLO WORlD");
//	//A* node = new A[10];
//	//delete node;//直接报错，只完成一次析构
//	//delete[] node;//不报错，完成10次析构
//	//char* c = new char[100];
//	//delete c;//不报错，完成一次析构
//	//delete[] c;//不报错，完成100次析构
//	return 0;
//}
	void test_string1()
	{
		drw::string s1("hello world");
		cout << s1.c_str() << endl;

		drw::string s2;
		cout << s2.c_str() << endl;

		for (size_t i = 0; i < s1.size(); i++)
		{
			s1[i]++;
		}
		cout << endl;

		for (size_t i = 0; i < s1.size(); i++)
		{
			cout << s1[i] << " ";
		}
		cout << endl;

		const drw::string s3("hello world");
		s3[0];

		//drw::string::const_iterator cit = s3.begin();
		auto cit = s3.begin();
		while (cit != s3.end())
		{
			//*cit += 1;

			cout << *cit << " ";
			++cit;
		}
		cout << endl;

		drw::string::iterator it = s1.begin();
		while (it != s1.end())
		{
			*it += 1;

			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto ch : s1)
		{
			cout << ch << " ";
		}
		cout << endl;
	}

	void test_string2()
	{

		drw::string s1("hello world");
		cout << s1.c_str() << endl;

		s1.push_back(' ');
		s1.push_back('#');
		s1.append("hello bit");
		cout << s1.c_str() << endl;

		drw::string s2("hello world");
		cout << s2.c_str() << endl;

		s2 += ' ';
		s2 += '#';
		s2 += "hello bit";
		cout << s2.c_str() << endl;
	}

	void test_string3()
	{
		drw::string s1("helloworld");
		cout << s1.c_str() << endl;

		s1.insert(5, 3, '#');
		cout << s1.c_str() << endl;

		s1.insert(0, 3, '#');
		cout << s1.c_str() << endl;


		drw::string s2("helloworld");
		s2.insert(5, "%%%%%");
		cout << s2.c_str() << endl;
	}

	void test_string4()
	{
		drw::string s1("helloworld");
		cout << s1.c_str() << endl;

		s1.erase(5, 3);
		cout << s1.c_str() << endl;

		s1.erase(5, 30);
		cout << s1.c_str() << endl;

		s1.erase(2);
		cout << s1.c_str() << endl;
	}

	void test_string5()
	{
		// 21：18继续
		drw::string url = "ftp://www.baidu.com/?tn=65081411_1_oem_dg";

		size_t pos1 = url.find("://");
		if (pos1 != drw::string::npos)
		{
			drw::string protocol = url.substr(0, pos1);
			cout << protocol.c_str() << endl;
		}

		size_t pos2 = url.find('/', pos1 + 3);
		if (pos2 != drw::string::npos)
		{
			drw::string domain = url.substr(pos1 + 3, pos2 - (pos1 + 3));
			drw::string uri = url.substr(pos2 + 1);

			cout << domain.c_str() << endl;
			cout << uri.c_str() << endl;
		}
	}

	void test_string6()
	{
		drw::string s("hello world");
		s.resize(8);
		cout << s.c_str() << endl;
		cout << s << endl;

		s.resize(13, 'x');
		cout << s.c_str() << endl;
		cout << s << endl;

		s.resize(20, 'y');
		cout << s.c_str() << endl;
		cout << s << endl;

		// c的字符数组，以\0为终止算长度
		// string不看\0，以size为终止算长度

		drw::string ss("hello world");
		ss += '\0';
		ss += "!!!!!!!!!!";
		cout << ss.c_str() << endl;
		cout << ss << endl;

		drw::string copy(ss);
		cout << ss << endl;
		cout << copy << endl;

		ss += "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		cout << ss << endl;
	}

	void test_string7()
	{
		drw::string s;
		cin >> s;
		cout << s << endl;

		cin >> s;
		cout << s << endl;

		//char buff[128];
		//for (size_t i = 0; i < 5; i++)
		//{
		//	cin >> buff[i];
		//}

		//for (size_t i = 0; i < 5; i++)
		//{
		//	cout << buff[i] << endl;
		//}
	}

	void test_string8()
	{
		//string s1("bb");
		//string s2("aaa");
		//cout << (s1 < s2) << endl;

		drw::string s1("hello");
		drw::string s2("hello");
		cout << (s1 < s2) << endl;
		cout << (s1 > s2) << endl;
		cout << (s1 == s2) << endl << endl;


		drw::string s3("hello");
		drw::string s4("helloxxx");
		cout << (s3 < s4) << endl;
		cout << (s3 > s4) << endl;
		cout << (s3 == s4) << endl << endl;


		drw::string s5("helloxxx");
		drw::string s6("hello");
		cout << (s5 < s6) << endl;
		cout << (s5 > s6) << endl;
		cout << (s5 == s6) << endl << endl;
	}

	void test_string9()
	{
		drw::string s1("hello");
		drw::string s2(s1);

		cout << s1 << endl;
		cout << s2 << endl;

		drw::string s3("xxxxxxxxxxxxx");
		s1 = s3;

		cout << s1 << endl;
		cout << s3 << endl;
	}

	int main()
	{
	
		test_string1();
		test_string2();
		test_string3();
		test_string4();
		test_string5();
		test_string6();
		test_string7();
		test_string8();
		test_string9();
		return 0;
	}
