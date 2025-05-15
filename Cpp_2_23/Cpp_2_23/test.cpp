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

//�Ȳ���һ�����ȼ�����
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
	bit::priority_queue<int, vector<int>, bit::Greater<int>> pq(v.begin(),v.end());//���ȼ����о��Ƕѣ�Ĭ����vector����ʵ�֣������÷º���
	//�º���Ĭ��Ϊless�������С�������У������
	//��������greater����ô����������С��
	//���õ���������ʼ��һ�� ����û�е���������ô��ֻ��ʹ�ò�Ϊ��������
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

//���ڶѵĸ�ϰ��
//1.���Ͻ���ʱ�临�Ӷ�nlogn�����½���ʱ�临�Ӷ�logn����Ϊһ����logn��
//2.���½��Ѵ���n-2��/2�����Ͻ��Ѵ�i

//���ڷº�����
//1.�Զ�������Ҫ�Լ�����><��������Զ������͵�ָ�룬Ҳ����ʹ�÷º������><���غ���ʹ��


//������ģ��������Լ�ģ������Ĳ���
//ʵ��һ����ӡ���������ĺ���

template<typename Container>
//����class typenme������
void print(const Container& c)
{
	//��const_iterator��: ���� �������Ƶ�ʹ�ñ����ԡ�typename��Ϊǰ׺
	//��������û��ʵ�����ģ���Ҫ��ǰ�����typename������ʵ����ΪҪ���ʵ�������п�����static��Ա����������
	//��������֪��Ҫ�������ͻ��Ǳ��������Ծͻᱨ��
	typename Container::const_iterator cit = c.begin();
	while (cit != c.end())
	{
		cout << *cit << " ";
		cit++;
	}
	cout << endl;
}


template<class T,size_t N>//������ģ�����Ӧ�þ���Ϊ�˿�������������ģ����ﲻͬ���βΣ�ģ���ǲ����Ըı�ģ����Ǹ�����
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
	//��ô����뿪��һ�������أ�c++��֧�ֱ䳤���飬��ô���÷�����ģ�����ֱ�ӽ���С����ȥ����
	//����ֻ���������������Ǹ�����

	mall<int, 10>();
	mall<int, 100>();

	array<int, 10> arr;
	arr[10];//array����ǿ�Ƽ�������Ƿ����Խ����ʵ�����������[]����������������
	//ʵ��Ӧ�ò���vector

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
	//�ػ��������⻰һ������ߺ��������Ҳ��ܹ��������ڣ�������ģ�廯�˵���
	//������ĳһ�����н������⴦��Ҳ����Ϊ�˼�ʵ�����������ػ�
	//�ػ�����Ϊȫ�ػ���ƫ�ػ���ǰ��ȫ�����ƣ������Ƕ�ģ���������һ��������
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


