#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<algorithm>
#include<array>
#include<unordered_set>
#include<forward_list>
#include<functional>
#include"string.hpp"
using namespace std;


struct Point
{
	//explicit Point(int x, int y)
	//����֧�ֵ��Ƕ��������ʽ����ת��
	//���������explicit�ͽ�ֹ��
	Point(int x, int y)
		:_x(x)
		, _y(y)
	{
		cout << "Point(int x, int y)" << endl;
	}

	int _x;
	int _y;
};

// һ�нԿ���{}��ʼ�������ҿ��Բ�д=
// �����ճ����壬��Ҫȥ��=����������Ҫ�ܿ���
void test_cpp11_1()
{
	//����c++11�ĳ�ʼ����������
	int x = 1;
	int y = { 2 };
	int z{ 3 };//��Ȼ���Բ�д=

	int a1[] = { 1,2,3 };
	int a2[]{ 1,2,3 };

	// ���ʶ��ǵ��ù��캯��
	Point p0(0, 0);
	Point p1 = { 1,1 };  // ��������캯����ʽ����ת��
	Point p2{ 2,2 };

	const Point& r = { 3,3 };//Ȩ�޵���С

	int* ptr1 = new int[3]{1, 2, 3};
	Point* ptr2 = new Point[2]{p0,p1};
	Point* ptr3 = new Point[2]{ {0,0},{1,1} };
}

struct test
{
	test(int first=0,int second=0)
		:a(first)
		,b(second)
	{ }

private:
	int a; int b;
};
void practice1()
{
	int a{ 1 };
	int b = { 2 };

	auto arr = new int[10] {1, 2, 3, 4, 5, 6, 7};
	auto aa = new test[2]{ test(1,1),test(2,2) };
	test* bb = new test[2]{ {1,1},{2,2} };

	vector<int> v = { 1,2,3,4,5,6 };//��ô��ʼ�����Ե�ԭ����c++11ʵ���˳�ʼ���б�
	initializer_list<int> il = { 1,2,3,4,5,6 };//����һ���б��Ƿ��ڳ������ģ�vectorʵ�������б���г�ʼ��
	//initializerlist�ײ�洢������ָ�룬�ֱ���begin��endָ�룬�����ʼ��
	test* ret = new test[10]{ {1},{2},{3},{4},{5}};//�������ǳ�ʼ���б������ͨ�ĳ�ʼ��

	map<string, string> map = { {"����","insert"},{"�γ�","takeout"} };


}

template<class T>
class teststruct
{
private:
	vector<T> _vv;
};

void testfunc(int* a)
{
	return;
}
void test_cpp11_2()
{
	auto ptr = malloc;
	cout << typeid(ptr).name() << endl;

	//��������һ����������
	auto pptr = ptr;
	decltype(ptr) ppptr;

	//�������Ƕ���һ������ô�ǳ�����
	teststruct<decltype(ptr)> t;

	//nullptr
	testfunc(0);
	testfunc(nullptr);
	testfunc(NULL);//�����߲�ͬ��NULL���滻����0

	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	for (auto e : arr)
	{
		cout << e << " ";
	}

	//����ָ���Ȳ���

	//STL�е�һЩ�仯
	array<int, 10 > array= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	//����̬���飬������Խ����ʵļ�飬��������vector�����滻

	forward_list<int> ������;
	������.insert_after(������.begin(), 1);

	//�������ṩ��ָ��λ��֮������ɾ����������ָ��λ�ý���ɾ�����룬�Լ�ͷ��ͷɾ��û���ṩ����β��βɾ
	//����֮���Զ��׼�
}

void test_cpp11_3()
{
	//������ֵ�Լ���ֵ
	//��Ѱַ��
	//��ֵ�����й̶����ڴ��ַ������ͨ��ȡ��ַ�����& ��ȡ���ַ�����磬�����ǵ��͵���ֵ����Ϊ�������ڴ����й̶��Ĵ洢λ�á�
	//��ֵ��ͨ��û�й̶����ڴ��ַ�����ܶ���ʹ��ȡ��ַ�����& �����磬�ַ���������ʱ����ȶ�����ֵ�������ڱ��ʽ��ֵ�����п��ܴ����ڼĴ�������ʱ�洢����û�пɻ�ȡ�Ĺ̶���ַ��
	//�����ڸ�ֵ�������λ��
	//��ֵ�����Գ����ڸ�ֵ���������ߣ���Ϊ��ֵ��Ŀ�ꡣ��Ϊ��ֵ����һ�����Ա��޸ĵĶ��������ܹ����ܸ�ֵ������
	//��ֵ��һ������ڸ�ֵ��������ұߣ���Ϊ��ֵ��ֵ��Դ����Ȼ��Щ��ֵҲ���Գ����ڸ�ֵ���ʽ�У������ǲ�����Ϊ��ֵ��Ŀ�ꡣ
	//���ʽ�����ͺ�����
	//��ֵ����������������Ԫ�ء���������ֵΪ��ֵ���õ�����ȡ����磬��������һ����ֵ���ã���ô�������ֵ������ֵ�����Ա�������ֵ��ȡ��ַ��
	//��ֵ������ǰ���ᵽ�����泣������ʱ�����⣬������һЩ���ʽ�Ľ�������������ʽ�Ľ�������Ǹñ��ʽ�Ľ����һ�����������ã�����������ֵΪ���������͵�����ȡ�

	//��ֵ���ã�����ֵȡ����
	//��ֵ���ã�����ֵȡ����
	double x = 1.1, y = 2.2;
	int a = 0;
	int& b = a;

	int&& right = 10;
	int&& count = x + y;

	const int& con = 10;//ʹ��const���Ը���ֵȡ��ֵ�ı���
	const double& plus = x + y;

	int&& left = move(a);//ʹ��move��������ֵ���ø���ֵȡ����

	//��ֵ���õ�ʹ�ó�����
	//1.���÷��� 2.������ 3.���ٿ��������Ч��
}

//void func(int& a)
//{
//	cout << "int&" << endl;
//}
//void func(int&& a)
//{
//	cout << "int&&" << endl;
//}
//������������
void func(const int& a)
{
	cout << "int&" << endl;
}
void func(int&& a)//��ֵ��ƥ������
{
	cout << "int&&" << endl;
}

drw::string Movecopy()
{
	drw::string str("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	str[0] = '1';
	return str;
}//���Ҫ��֤�ƶ����죬��Ҫ��ֵ���أ�����������Ż�����ô�����������ʱ�����ǽ���ֵ
//�����Ż���ֱ�ӽ�str��Ϊ����ֵ�����ƶ�����

class defaultcopy
{
public:
	defaultcopy()
	{
		_a = new char[10];
	}

	defaultcopy(const defaultcopy& dc) = default;

	defaultcopy(defaultcopy&& dc) = default;

	//~defaultcopy() = delete;//�����������Ĭ�Ϻ���������ֱ�Ӽ���delete��������98�ж�����private��
private:
	char* _a;
};
void test_cpp11_4()
{
	/*int a = 0;
	func(1+1);*/

	//�����������ƶ������Լ��ƶ���ֵ
	//�����������͵���ʱ�����Ϊ����ֵ
	//�����Զ������͵���ʱ�����Ϊ����ֵ
	//drw::string newstr = Movecopy();
	/*drw::string ns;
	ns = Movecopy();*/
	//���ƶ�����֮ǰ������ǿ������췵�أ���ô�Ȳ���һ����ʱ�����ٿ��������¶�������Ҫ�������������
	//���Ǳ�����������Ż���ͨ����һ�ο����������ƶ�����֮���ȿ���������ʱ����Ȼ���ƶ������¶��󣬵��Ǳ����������Ż���ֻ���ƶ���������ˣ�

	drw::string s("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	drw::string s1 = s;
	//move(s);
	drw::string s2 = move(s);

	////�ƶ����첻�������ڴ�ֵ������ʱ����ٿ������ۣ��������ڸ��������Ĳ�������ƶ�����
	list<string> list;
	string s3("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	list.push_back(s3);

	list.push_back("xxxxxxxxxxxxxxxxxxxxxxxxx");
	list.push_back(move(s3));
	//Ĭ���ƶ����죺ʲô�����»�����Ĭ���ƶ����죿
	//����������죬�ƶ����ƣ����������κ�һ����û��ʵ�֣���ô������Ĭ���ƶ����죬
	//������������ȥ����ǳ�����������Զ�������ȥ���ÿ�������
	//������������������ڣ�Ҳ����ǿ��ʵ��Ĭ���ƶ����죬�ں����������=default���ɡ�

	//�ƶ���ֵ����Ҳ��������Ĭ���ƶ���ֵ��������û��������������ֵ���������������캯�������������ɣ�
	//������������ǳ�����������Զ������͵����ƶ���ֵ����
	defaultcopy test;
	defaultcopy newtest = test;
}

void Fun(int& x) { cout << "��ֵ����" << endl; }
void Fun(const int& x) { cout << "const ��ֵ����" << endl; }
void Fun(int&& x) { cout << "��ֵ����" << endl; }
void Fun(const int&& x) { cout << "const ��ֵ����" << endl; }
// ģ���е�&&��������ֵ���ã������������ã�����ܽ�����ֵ���ܽ�����ֵ��
// ģ�����������ֻ���ṩ���ܹ�����ͬʱ������ֵ���ú���ֵ���õ�������
// �����������͵�Ψһ���þ��������˽��յ����ͣ�����ʹ���ж�(�˻�������ֵ)��
// ����ϣ���ܹ��ڴ��ݹ����б���������ֵ������ֵ������, ����Ҫ����������ѧϰ������ת��
template<typename T>
void PerfectForward(T&& t)//ע��������ģ���&&���˴������������ã�������ֵ������۵�����ֱֵ�ӽ���
{
	Fun(t);//���ﴫ�ι�ȥ������һ������ֵ���������������ֵ����ô�ƶ����캯�����ƶ����ƺ������޷������޸�
	//��ô���Ҫ�����������ֵ�����أ�
	//����ת����
	//Fun(forward<T>(t));
}

void test_cpp11_5()
{
	PerfectForward(10); // ��ֵ
	int a;
	PerfectForward(a); // ��ֵ
	PerfectForward(std::move(a)); // ��ֵ
	const int b = 8;
	PerfectForward(b); // const ��ֵ
	PerfectForward(std::move(b)); // const ��ֵ
}
	

namespace bit
{
	template<class T>
	struct ListNode
	{
		ListNode* _next = nullptr;
		ListNode* _prev = nullptr;
		T _data;
	};

	template<class T>
	class List
	{
		typedef ListNode<T> Node;
	public:
		List()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		template<class Ty>
		void PushBack(Ty&& x)//��ע��ǰ���T��ʵ���������ͣ������Ty������������Ҫ�Լ��˵������ͣ����������ʵ����T&&����������ֵ���ã�������������
		{
			//Insert(_head, x);
			Insert(_head, forward<Ty>(x));
		}

		void PushFront(T&& x)
		{
			//Insert(_head->_next, x);
			Insert(_head->_next, forward<T>(x));
		}

		template<class Ty>
		void Insert(Node* pos, Ty&& x)
		{
			Node* prev = pos->_prev;
			Node* newnode = new Node;
			newnode->_data =forward<Ty>(x); // �ؼ�λ��
			// prev newnode pos
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = pos;
			pos->_prev = newnode;
		}

		//void Insert(Node* pos, const T& x)
		//{
		//	Node* prev = pos->_prev;
		//	Node* newnode = new Node;
		//	newnode->_data = x; // �ؼ�λ��
		//	// prev newnode pos
		//	prev->_next = newnode;
		//	newnode->_prev = prev;
		//	newnode->_next = pos;
		//	pos->_prev = newnode;
		//}
	private:
		Node* _head;
	};
}

//������������������������������������
void test_cpp11_6()
{
	bit::List<int> lt;
	int a = 0;
	const int b = 0;
	lt.PushBack(a);
	lt.PushBack(b);
}

class Date
{
public:
	Date(const int& year=2025,const int& month=4,const int& day=5)
		:_year(year)
		,_month(month)
		,_day(day)
	{ }
public:
	int _year;
	int _month;
	int _day;
};
struct compare
{
	bool operator()(const Date& d1, const Date& d2)
	{
		if (d1._year < d2._year) return true;
		else if (d1._year == d2._year)
		{
			if (d1._month < d2._month) return true;
			else if (d1._month == d2._month)
			{
				if (d1._day < d2._day) return true; else return false;
			}
			else return false;
		}
		else return false;
	}
};
//void test_cpp11_1111()
//{
//	vector<Date> v = { {2006,8,21},{2006,12,28},{2007,7,21} };
//	sort(v.begin(), v.end(),compare() );
//	for (const auto& e : v)
//	{
//		cout << e._year << '-' << e._month << '-' << e._day << endl;
//	}
//}

void test_cpp11_7()
{
	vector<Date> v = { {2006,8,21},{2006,12,28},{2007,7,21} };
	//lameda���������Բ���ȥ���أ���������������ֱ�Ӷ���
	sort(v.begin(), v.end(), [](const Date& d1, const Date& d2)->bool
		{if (d1._year < d2._year) return true;
		else if (d1._year == d2._year)
		{
			if (d1._month < d2._month) return true;
			else if (d1._month == d2._month)
			{
				if (d1._day < d2._day) return true; else return false;
			}
			else return false;
		}
		else return false; });

	for (const auto& e : v)
	{
		cout << e._year << '-' << e._month << '-' << e._day << endl;
	}

	//����lameda������
	double a = 1.0, b = 2.0, c = 3.0;
	auto add = [](int a,int b) {return a + b; };
	cout << add(a, b) << endl;
	//auto add1 = [](int a, int b) {return add(a, b); };//������ô���ú����𣿲��У����ǿ����ڽṹ�ڵ���ȫ�ֺ���
	auto add1 = [](int a, int b) {return func(a); };

	//��ע�⣬�����б�ͷ���ֵ���Ͷ��ǿ���ʡ�ԵĲ��֣�����ֵ�����Զ��Ƶ�
	//�����Ҫʹ���������������Բ�׽
	auto add2 = [c](int a, int b)mutable { c = 2.0;  return a + b + c; };//��ô���Զ�c�����޸��𣿲����ԣ���׽��ֵĬ��ʹ��const����
	//�����Ҫ�����޸Ŀ��Լ���mutable,���ǣ�����muableҲ�����ǶԿ���������c�����޸ģ�������Ӱ�쵽ʵ��
	//mutableһ��û�����ã�ʹ��&�������࣬���ҿ��Ըı�ʵ��
	auto add3 = [&c](int a, int b) {c = 2.0; return a + b + c; };

	int A = 1, B = 2,C = 3, D = 4;
	//�����Ҫȫ����׽����ʹ��=�����þ�ʹ��&
	auto add4 = [=]() {return A+B+C+D; };
	auto add5 = [&]() {A=B=C=D = 0; return A+B+C+D; };

	//��Ҫע�����add4��add5֮�䲻�ܻ��ำֵ����������������������
	cout << typeid(add4).name() << endl;
	cout << typeid(add5).name() << endl;
	//������ӡ��UUID��ÿ���඼�ж�һ�޶���UUID��Ҳ����˵��������������һģһ��������Ҳ�ǲ���ͬ��
	//���յײ�ʵ�֣���ʵlameda���ʾ���ʹ�÷º����������أ�����������������ʵ�ֵģ�����ͨ�����鿴
}


//�ɱ���ģ�����
template<class ...Args>
void Showlist(Args...args)//args����0-N�Ĳ�����
{
	cout << sizeof...(args) << endl;//�ɱ�ģ�����������Ҫ��ô��ӡ������ĸ���

	//for (int i = 0; i < sizeof...(args); i++) { cout << args[i] << endl; }//�����������з���
}

//��ô��ν��з����أ����õݹ�
template<class T>
int showlist(T t)
{
	cout << t << endl;
	return 0;
}

template<class T, class...Args>
void showlist(T t,Args...args)
{
	cout << t << " ";
	showlist(args...);
}

template<class ...Args>
void cppprint(Args...args)
{
	int a[] = { showlist(args)... };//����ʹ���չ�������ղ����������ݸ�������������ռ�

}

template<class...Args>
void initdate(Args...args)
{
	Date* newdate = new Date(args...);
	return;
}
void test_cpp11_8()
{
	Showlist(1);
	Showlist(1, 11);
	Showlist(1, 11, 111);

	showlist(1);
	showlist(1, 11);
	showlist(1, 11, 111);

	//��������ͨ��������ʽ�����У�ͨ������չ���ķ�ʽʵ��
	cppprint(1);
	cppprint(1, 11);
	cppprint(1, 11, 111);

	//��Ȼ���ɱ�ģ���Ͳ����������õ��ǿ���������
	initdate(2025, 3, 8);
}

void test_cpp11_9()
{
	//c++11�������¼ӵ�emplace�÷������ù���Ĵ��۽���
	list<pair<string,string>> hash;
	hash.emplace_back("xxxx", "1234");//�������ݵ��ǲ�����������makepair��Ч�����ƶ�������ʵ���
	hash.push_back(make_pair("insert", "����"));

}


class funcc
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}

	int Func(int a, int b)
	{
		return a + b;
	}
};

int Func(int a, int b)
{
	return a + b;
}

double Funcc(char a, int b, double c)
{
	return a + b * c;
}
void test_cpp11_10()
{
	//��װ��

	//�����ѷº�����lameda������ָ��Ž��������ô�죬��ʱ��Ҫʹ�ð�װ��
	//�ô����ڰ�����������װ��ͬһ���͵Ķ��������������
	function<int(int,int)> f1 = [](int a, int b) {return a + b; };
	function<int(int,int)> f2 = funcc();
	function<int(int,int)> f3 = Func;
	//��װ���м��Ƿ���ֵ�Ӳ�����
	vector < function<int(int, int)>> v = { f1,f2,f3 };
	//�����º���������ָ���Լ�lameda���ԷŽ�vector

	//bind�󶨣�
	function<double(char, int)> func1 = bind(Funcc, placeholders::_1, placeholders::_2, 3.1415);
	function<double(char, int)> func2 = bind(Funcc, placeholders::_2, placeholders::_1, 3.1415);
	function<double( int, double)> func3 = bind(Funcc, 3.1415, placeholders::_1, placeholders::_2);
	function<double( int, double)> func4 = bind(Funcc, 3.1415, placeholders::_2, placeholders::_1);	
	function<double(char, double)> func5 = bind(Funcc, placeholders::_1, 3.1415, placeholders::_2);
	function<double(char, double)> func6 = bind(Funcc, placeholders::_2, 3.1415, placeholders::_1);
	cout << func1(1, 2) << endl;
	cout << func2(1, 2) << endl;
	cout << func3(1, 2) << endl;
	cout << func4(1, 2) << endl;
	cout << func5(1, 2) << endl;
	cout << func6(1, 2) << endl;
	//ע��placeholders�е�_1_2_3��������ĵڼ���������ֵ��bind��ʡ�ԣ�����ʵ�ְ󶨣�����ע��function�еĸ�ʽ
	//����ǰ������ֵ�������д����ε����ͣ���ע�⴫�εĸ���һ��Ҫ���ϣ����еĲ�������
	//����İ������ȱʡ������˵��ȱʡֵ�����ģ������ֵ���Զ��

	function<int(int, int)> func7 = bind(&funcc::Func, funcc(), placeholders::_1, placeholders::_2);
	//��ע�⣬����func7����һ��������Ҫ������ַ����ʵ��һ������Ҳ���Դ��ηº���lambda���ʽ���ߺ���ָ�룬bothok
	//�ڶ���������Ҫ���ص�thisָ�룬��������������ʱ������ֵ���ܹ�ȡ��ַ
}


int main()
{
	//test_cpp11_1();
	//test_cpp11_4();
	//practice1();
	test_cpp11_7();
	

	return 0;
}