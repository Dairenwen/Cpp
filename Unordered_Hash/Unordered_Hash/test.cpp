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
	//介绍一下unordered_map
	//底层实现是哈希表
	//迭代器类型是单向的
	//遍历出来是无序的
	//查找效率非常高
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
	//输出并不是有序的

	//哈希存储的值与位置存在某种映射关系，存在三种：
	//1.直接定址法，适用于值的分布范围集中，eg统计字符在字符串中出现的次数
	//2.除留余数法：适用于值的分布范围分散，将key%n，n代表空间大小，这样就可以建立起对应关系，但此时存在哈希冲突的问题
	//闭散列法：开放定址法，再哈希法，链地址法
	//线性探测法：哈希冲突时，向后探测，直到找到空位置
	//找到空位置放置元素，查找时，如果找到空位置，说明没有找到，如果找到的位置不是要找的元素，继续向后探测
	//这里哈希表是不可能满的所以不用考虑不存在空位置的情况
	//
	//需要注意的是：如果要删除某个值，不能直接删除，因为删除后，后面的元素就找不到了
	//或者说不能用值来标记一个数是否被删除，应该用状态来标记：exsit，empty，delete
	// 
	// 随着哈希表的插入，删除，查找，哈希表的负载因子会逐渐增大，当负载因子大于某个值时，哈希表的性能会下降
	// 负载因子越大，哈希冲突的概率越大，查找效率越低
	// 负载因子越小，哈希表的空间利用率越低，哈希冲突的概率越小，查找效率越高
	// 
	// 哈希表不能满了再扩容，需要在负载因子达到某个值时就扩容
	//
	//二次探测法：哈希冲突时，向后探测，探测步长为i^2
	//再哈希法：哈希冲突时，再次哈希，直到找到空位置
	//链地址法：哈希冲突时，将冲突的元素放到链表中
	//3.随机探测法：哈希冲突时，随机探测，直到找到空位置

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
	map.insert(make_pair("插入", "insert"));
	map.insert(make_pair("插", "insert"));
	map.insert(make_pair("插", "insert"));
	map.erase("插");
	map.insert(make_pair("拔出", "takeout"));

	for (auto e : map)
	{
		cout << e.first << e.second << endl;
	}

	bit::unordered_set<string> set;
	set.insert("插入");
	set.insert("插");
	set.insert("插");
	set.erase("插");
	set.insert("拔出");

	for (auto e : set)
	{
		cout << e << endl;
	}
}

void test_HashBucket2()
{
	bit::unordered_map<string, string> map;
	map["插入"] = "insert";
	map["插"] = "insert";
	map.insert(make_pair("插", "insert"));
	map.erase("插");
	map.insert(make_pair("拔出", "takeout"));

	bit::unordered_map<string, string>::const_iterator cit = map.cbegin();
	while (cit != map.cend())
	{
		cout << cit->first << cit->second << endl;
		++cit;
	}

	bit::unordered_set<string> set;
	set.insert("插入");
	set.insert("插");
	set.insert("插");
	set.erase("插");
	set.insert("拔出");

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