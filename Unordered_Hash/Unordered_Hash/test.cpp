#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include"HashTable.hpp"
#include"unorderedset.hpp"
#include"unorderedmap.hpp"
using namespace std;

void test_unordered_map()
{
	//����һ��unordered_map
	//�ײ�ʵ���ǹ�ϣ��
	//�����������ǵ����
	//���������������
	//����Ч�ʷǳ���
	unordered_map<int, int> m;
	m.insert(make_pair(1, 1));
	m.insert(make_pair(3, 3));
	m.insert(make_pair(2, 2));
	m.insert(make_pair(4, 4));
	m.insert(make_pair(5, 5));
	m.insert(make_pair(6, 6));
	m.insert(make_pair(7, 7));
	m.insert(make_pair(8, 8));
	unordered_set<int> s;
	s.insert(1);
	s.insert(3);
	s.insert(2);
	unordered_map<int, int>::iterator it = m.begin();
	unordered_set<int>::iterator sit = s.begin();
	for (; it != m.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}
	for (; sit != s.end(); ++sit)
	{
		cout << *sit << endl;
	}
	//��������������

	//��ϣ�洢��ֵ��λ�ô���ĳ��ӳ���ϵ���������֣�
	//1.ֱ�Ӷ�ַ����������ֵ�ķֲ���Χ���У�egͳ���ַ����ַ����г��ֵĴ���
	//2.������������������ֵ�ķֲ���Χ��ɢ����key%n��n����ռ��С�������Ϳ��Խ������Ӧ��ϵ������ʱ���ڹ�ϣ��ͻ������
	//��ɢ�з������Ŷ�ַ�����ٹ�ϣ��������ַ��
	//����̽�ⷨ����ϣ��ͻʱ�����̽�⣬ֱ���ҵ���λ��
	//�ҵ���λ�÷���Ԫ�أ�����ʱ������ҵ���λ�ã�˵��û���ҵ�������ҵ���λ�ò���Ҫ�ҵ�Ԫ�أ��������̽��
	//�����ϣ���ǲ������������Բ��ÿ��ǲ����ڿ�λ�õ����
	//
	//��Ҫע����ǣ����Ҫɾ��ĳ��ֵ������ֱ��ɾ������Ϊɾ���󣬺����Ԫ�ؾ��Ҳ�����
	//����˵������ֵ�����һ�����Ƿ�ɾ����Ӧ����״̬����ǣ�exsit��empty��delete
	// 
	// ���Ź�ϣ��Ĳ��룬ɾ�������ң���ϣ��ĸ������ӻ������󣬵��������Ӵ���ĳ��ֵʱ����ϣ������ܻ��½�
	// ��������Խ�󣬹�ϣ��ͻ�ĸ���Խ�󣬲���Ч��Խ��
	// ��������ԽС����ϣ��Ŀռ�������Խ�ͣ���ϣ��ͻ�ĸ���ԽС������Ч��Խ��
	// 
	// ��ϣ�������������ݣ���Ҫ�ڸ������Ӵﵽĳ��ֵʱ������
	//
	//����̽�ⷨ����ϣ��ͻʱ�����̽�⣬̽�ⲽ��Ϊi^2
	//�ٹ�ϣ������ϣ��ͻʱ���ٴι�ϣ��ֱ���ҵ���λ��
	//����ַ������ϣ��ͻʱ������ͻ��Ԫ�طŵ�������
	//3.���̽�ⷨ����ϣ��ͻʱ�����̽�⣬ֱ���ҵ���λ��

}

void test_HashTable1()
{
	open_address::HashTable<int, int> hash;
	for (int i = 0; i < 9999; i++)
	{
		hash.insert(make_pair(i, i));
		if (hash.Find(i))
		{
			cout << "_";
		}
		else
		{
			cout << "wrong!" << endl;
		}
	}
	

	printf("%p", hash.Find(4));
}

void test_HashTable2()
{
	open_address::HashTable<string, int> hash;
	for (size_t i = 0; i < 9999; i++)
	{
		hash.insert(make_pair("i", i));
		if (hash.Find("i"))
		{
			cout << "_";
		}
		else
		{
			cout << "wrong!" << endl;
		}
	}
}

void test_HashBucket1()
{
	bit::unordered_map<string, string> map;
	map.insert(make_pair("����", "insert"));
	map.insert(make_pair("��", "insert"));
	map.insert(make_pair("��", "insert"));
	map.erase("��");
	map.insert(make_pair("�γ�", "takeout"));

	for (auto e : map)
	{
		cout << e.first << e.second << endl;
	}

	bit::unordered_set<string> set;
	set.insert("����");
	set.insert("��");
	set.insert("��");
	set.erase("��");
	set.insert("�γ�");

	for (auto e : set)
	{
		cout << e << endl;
	}
}

void test_HashBucket2()
{
	bit::unordered_map<string, string> map;
	map["����"] = "insert";
	map["��"] = "insert";
	map.insert(make_pair("��", "insert"));
	map.erase("��");
	map.insert(make_pair("�γ�", "takeout"));

	bit::unordered_map<string, string>::const_iterator cit = map.cbegin();
	while (cit != map.cend())
	{
		cout << cit->first << cit->second << endl;
		++cit;
	}

	bit::unordered_set<string> set;
	set.insert("����");
	set.insert("��");
	set.insert("��");
	set.erase("��");
	set.insert("�γ�");

	bit::unordered_set<string>::const_iterator ct=set.cbegin();
	while (ct != set.cend())
	{
		cout << *ct << endl;
		++ct;
	}
}


int main()
{
	//test_unordered_map();
	//test_HashTable1();
	//test_HashTable2();
	//test_HashBucket1();
	test_HashBucket2();

	return 0;
}