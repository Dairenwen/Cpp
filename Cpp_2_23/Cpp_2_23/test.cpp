#include<iostream>
#include<assert.h>
#include<queue>
#include<vector>
#include<list>
#include<array>
using namespace std;
#include"PriorityQueue.hpp"
#include"list.hpp"
#include"template.hpp"
#include"template.cpp"

void pwrint(const bit::list<int>& t)
{
	bit::list<int>::const_reverse_iterator crit = t.crbegin();
	while ( crit != t.crend())
	{
		cout << *crit << " ";
		crit++;
	}
}

//先测试一下优先级队列
int test1()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(42);
	v.push_back(3);
	v.push_back(22);
	v.push_back(5);
	v.push_back(76);
	v.push_back(37);
	v.push_back(85);
	v.push_back(9);
	bit::priority_queue<int, vector<int>, bit::Greater<int>> pq(v.begin(),v.end());//优先级队列就是堆，默认用vector进行实现，后面用仿函数
	//仿函数默认为less，数组从小到大排列，建大堆
	//这里用了greater，那么就是用来建小堆
	//先用迭代器来初始化一下 这里没有迭代器，那么就只能使用不为空来遍历
	//cout << pq.top() << " ";
	/*while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}*/

	bit::list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	bit::list<int>::reverse_iterator rit = l.rbegin();
	while (rit != l.rend())
	{
		cout << *rit << " ";
		rit++;
	}
	cout << "\n";

	pwrint(l);

	return 0;
};

//关于堆的复习：
//1.向上建堆时间复杂度nlogn，向下建堆时间复杂度logn，因为一共有logn层
//2.向下建堆传（n-2）/2，向上建堆传i

//关于仿函数：
//1.自定义类型要自己重载><，如果是自定义类型的指针，也可以使用仿函数配合><重载函数使用


//非类型模板参数，以及模板参数的补充
//实现一个打印任意容器的函数

template<typename Container>
//这里class typenme都可以
void print(const Container& c)
{
	//“const_iterator”: 类型 从属名称的使用必须以“typename”为前缀
	//凡是这里没有实例化的，都要在前面加上typename，这其实是因为要访问的这个类中可能有static成员或者是类型
	//编译器不知道要调用类型还是变量，所以就会报错
	typename Container::const_iterator cit = c.begin();
	while (cit != c.end())
	{
		cout << *cit << " ";
		cit++;
	}
	cout << endl;
}


template<class T,size_t N>//非类型模板参数应该就是为了开辟数组而产生的，这里不同于形参，模板是不可以改变的，这是个常量
void mall()
{

	T _a[N];
}
int test2()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	print(l);

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	print(v);
	//那么如果想开辟一块数组呢，c++不支持变长数组，那么就用非类型模板参数直接将大小传过去即可
	//并且只能是整数，不能是浮点数

	mall<int, 10>();
	mall<int, 100>();

	array<int, 10> arr;
	arr[10];//array可以强制检查数组是否存在越界访问的情况，这里对[]操作符进行了重载
	//实际应用不如vector

	return 0;
}


	template<class T1,class T2>
	class Date
	{
	public:
		Date()
		{
			cout << "Date<T,T>" << endl;
		}
	private:
		T1 a;
		T2 b;
	};
	//特化就是特殊话一个类或者函数，并且不能够独立存在，必须有模板化了的类
	//可以在某一种类中进行特殊处理，也可以为了简化实例化而进行特化
	//特化还分为全特化和偏特化，前者全部限制，后者是对模板参数更进一步的限制
	template<>
	class Date<int, int>
	{
	public:
		Date()
		{
			cout << "Date<int,int>" << endl;
		}
	private:
		int a;
		int b;
	};

	template<class T>
	class Date<T, int>
	{
	public:
		Date()
		{
			cout << "Date<T,int>" << endl;
		}
	private:
		T a;
		int b;
	};
	void test3()
	{
		Date<int, int> d1;
		Date<double, int> d2;
		Date<double, double> d3;
	}


int main()
{
	/*test::stack<int,vector<int>> s;
	s.push(1);
	s.pop();*/
	test3();
	return 0;
}


