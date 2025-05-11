#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
#include"list.hpp"
using namespace std;


void test_list1()
{
	list <int> l1;//带头双向循环链表
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_front(10);
	l1.push_front(20);
	l1.pop_back();
	l1.pop_front();
	for (auto tmp : l1)
	{
		cout << tmp<<" ";
	}
	cout << "\n";
	//第五个位置插入数据
	//l1.insert(l1.begin() + 5, 6);//对不起没有这种用法，数据不是连续储存的，不能这样使用
	auto begin = l1.begin();
	for (size_t i = 0; i < 3; i++)
	{
		begin++;//这样可以，因为对++进行了重载
	}
	l1.insert(begin, 6);
	for (auto tmp : l1)
	{
		cout << tmp << " ";
	}
	cout << "\n";
	//迭代器失效问题：对于list来说insert不会失效，但是erase会失效，因为insert创建新的空间
	//不会影响其他数据，erase释放了空间，不能再进行访问
	begin = find(l1.begin(), l1.end(), 6);
	if (begin != l1.end())
	{
		begin=l1.insert(begin, 66);
		*begin /= 11;
	}
	for (auto tmp : l1)
	{
		cout << tmp << " ";
	}
}

void test_list2()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);

	lt.push_front(10);
	lt.push_front(20);

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	reverse(lt.begin(), lt.end());
	//关于reverse sort：先来介绍几种迭代器类型
	//inputiterator单向迭代器：支持++（forward_list）
	//randomaccess iterator随机迭代器：支持++/--/+/-（vector，string，deque）
	//bidirectional iterator双向迭代器：支持++/--（list，map，set）
	//这里list不能用算法库的sort因为sort需要随机类型的，所以只能使用list中的sort
	//但是库中的reverse可以正常使用，list中的reverse显得多余，但list中的sort效率低下
	//通常建议拷贝到vector，再sort复制回list
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.reverse();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;


	//sort(lt.begin(), lt.end());
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	lt.sort();
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	list<int> l;
	vector<int> v;
	for (size_t i = 10; i >0; i--)
	{
		l.push_back(i);
	}
	auto begin = l.begin();
	while (begin != l.end())
	{
		v.push_back(*begin++);
	}
	sort(v.begin(), v.end());
	auto start = v.begin();
	begin = l.begin();
	while (start != v.end())
	{
		*begin++ = *start++;
	}
	for (auto e : l)
	{
		cout << e << " ";
	}
}
int main()
{
	//test_list1();
	//test_list2();
	bit::test_list5();
	return 0;
}