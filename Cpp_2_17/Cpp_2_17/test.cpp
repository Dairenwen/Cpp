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
	list <int> l1;//��ͷ˫��ѭ������
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
	//�����λ�ò�������
	//l1.insert(l1.begin() + 5, 6);//�Բ���û�������÷������ݲ�����������ģ���������ʹ��
	auto begin = l1.begin();
	for (size_t i = 0; i < 3; i++)
	{
		begin++;//�������ԣ���Ϊ��++����������
	}
	l1.insert(begin, 6);
	for (auto tmp : l1)
	{
		cout << tmp << " ";
	}
	cout << "\n";
	//������ʧЧ���⣺����list��˵insert����ʧЧ������erase��ʧЧ����Ϊinsert�����µĿռ�
	//����Ӱ���������ݣ�erase�ͷ��˿ռ䣬�����ٽ��з���
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
	//����reverse sort���������ܼ��ֵ���������
	//inputiterator�����������֧��++��forward_list��
	//randomaccess iterator�����������֧��++/--/+/-��vector��string��deque��
	//bidirectional iterator˫���������֧��++/--��list��map��set��
	//����list�������㷨���sort��Ϊsort��Ҫ������͵ģ�����ֻ��ʹ��list�е�sort
	//���ǿ��е�reverse��������ʹ�ã�list�е�reverse�Եö��࣬��list�е�sortЧ�ʵ���
	//ͨ�����鿽����vector����sort���ƻ�list
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