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
//template<class T>//���������һ���������߾���һ���࣬��ȡ������Ҫ����ģ��
//A<T>::A(int year, int month , int day)//A������ A<T>������ Ҫ���ֿ���
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
//		//A* tmp = new A[10]{ A(2025,1,10),A(2025,1,11) };//��operator new->malloc�ٹ���
//		//delete[] tmp;//��������operator free->free
//	}//mallocʧ�ܷ��ؿ�ָ�� newʧ�����쳣��׽
//	catch (const exception& e)
//	{
//		cout << e.what() << endl;
//	}
//	//��ʾʵ����
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
//	delete p2;//���ｫdelete��C�����е�free���ö����Զ���������˵����������
//	          //���������������кܴ���ʻ��bug�����ǺõĴ���ϰ��!
//
//	int* p3 = (int*)malloc(sizeof(int)); 
//	int* p4 = new int;
//	free(p3);
//	delete p4;//����������ȷ���տռ������mallocƥ��free��newƥ��delete
//	A* p5 = (A*)malloc(sizeof(A) * 10);
//	A* p6 = new A[10];//������Զ�A������г�ʼ��,����ֱ�Ӹ�ֵ��Ҳ�����������������ʼ��
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
	string s5("Hello C plus plus");//string�����ڶ��Ͽ��ٵĿռ�
	for (size_t i = 0; i < s5.size(); i++)
	{
		cout << s5[i];
	}
	cout << endl;
	string::iterator it = s5.begin();//beginָ���һ��Ԫ�� endָ�����һ��Ԫ�غ��棬����ҿ�
	while (it != s5.end())
	{
		cout << *it;
	    it++;
	}
	cout << endl;
	for (auto tmp : s5)//��Χfor���ʾ��ǵ���������֧�ֵ�������һ����֧�ַ�Χfor������ջ
	{
		cout << tmp;
	}
	cout << endl;
	//string::reverse_iterator rit = s5.rbegin();
	auto rit = s5.rbegin();//�����ַ��� ʹ��rbegin��ȡָ�����һ��Ԫ��ָ�� ���ﲻ��ʹ��for��Ϊ��Ĭ���������
	                       //Ҫʹ��while������Ϊ��ʡ�£�ʹ��auto�Զ�ʶ������
	while (rit != s5.rend())
	{
		cout << *rit;//����ҿ� rbeginָ�����һ�� rendָ���һ��ǰ��
		rit++;
		//�����������ʹ���߿��ǣ��������ʹ�� ������++�ͺ��ˣ��ײ�Դ��ʵ��ʵ�ʵ��õľ���--�Ľӿڣ�������ǰ��
        //���ӿ������Ϊ���ܹ���begin()��rbegin()������ͳһ�ķ�ʽ���ñ�����ʵ��ʹ����������һ���ģ�����rid++, ���ײ�ʵ���У�
		// begin()���������ߣ�rbegin()�ľ�����ǰ�ߣ�����ײ�ʵ���Ǹ���--�Ľӿڣ�

	}
	cout << endl;
}

//// ר�Ŵ���int�ļӷ�����
//int Add(int left, int right)
//{
//	return left + right;
//}
//// ͨ�üӷ�����
//template<class T>
//T Add(T left, T right)
//{
//	return left + right;
//}
//void Test()
//{
//	Add(1, 2); // ���ģ�庯��ƥ�䣬����������Ҫ�ػ�
//	Add<int>(1, 2); // ���ñ������ػ���Add�汾
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
	cin >> input;//�����c������scanf��fscanf��һ���� �����ո������\n�ͻ�ֹͣ��ȡ
	//���������Ҫʹ��getline(cin,input);
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
	size_t accept = s1.find('/', recieve + 3);//find������ָ���ַ���������ҵ��ͷ��ص�һ���ַ���λ�ã����û�ҵ��ͷ���-1
	if (accept != string::npos)
	{
		domain = s1.substr(recieve + 3, accept-(recieve+3));//substr�������������ַ���
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
//	//delete node;//ֱ�ӱ���ֻ���һ������
//	//delete[] node;//���������10������
//	//char* c = new char[100];
//	//delete c;//���������һ������
//	//delete[] c;//���������100������
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
		// 21��18����
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

		// c���ַ����飬��\0Ϊ��ֹ�㳤��
		// string����\0����sizeΪ��ֹ�㳤��

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
