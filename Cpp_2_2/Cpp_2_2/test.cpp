#include<assert.h>
#include<iostream>
#include<vector>
#include<algorithm>//算法库 包括sort find reverse
#include<string>
#include"vector.hpp"
using namespace std;

void test_vector1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	for (auto tmp : v1)
	{
		cout << tmp;
	}
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i];
	}
	vector<int>::iterator it = v1.begin();
	while(it != v1.end())
	{
		cout << *it;
		it++;
	}
}
void test_vector2()
{
	vector<string> v1;//可以显式实例化选择string类
	v1.push_back("666");//隐式类型转换
	v1.push_back(string("666"));//匿名对象
}
void test_vector3()
{
	vector<int> v1(10, 1);//10个1
	vector<int> v2(v1.begin() + 4, v1.end());//可以用迭代器初始化
	for (auto tmp : v1)
	{
		cout << tmp;
	}
	for (auto tmp : v2)
	{
		cout << tmp;
	}
	string str("hello world");
	vector<char> v4(str.begin(), str.end());
	for (auto e : v4)
	{
		cout << e << " ";
	}
	cout << endl;

	int a[] = { 16,2,77,29 };
	vector<int> v5(a, a + 4);
	for (auto e : v5)
	{
		cout << e << " ";
	}
	cout << endl;
	//这里介绍一下算法sort,<是less >是greater
	less<int> ls;
	sort(v5.begin(), v5.end(), ls);
	for (auto e : v5)
	{
		cout << e << " ";
	}
	//或者
	sort(v5.begin(), v5.end(), less<int>());//这里less省略也可以 默认升序
	//这里也可以不传>，而是在升序排列的情况下传rbegin和rend，从末尾按照升序排序
	greater<int> gt;
	sort(v5.begin(), v5.end(), greater<int>());
	for (auto e : v5)
	{
		cout << e << " ";
	}
}
void test_vector4()
{
	vector<int> v1;
	/*v1.reserve(10);
	for (size_t i = 0; i < 10; i++)
	{
		v1[i] = i;
    }*///报错，开10个空间，但是size为0，在[]访问时断言pos<size出错，应该用resize先初始化
	v1.resize(10, 1);
	for (size_t i = 0; i < 10; i++)
	{
		v1[i] = i;
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}

}
void test_vector5()
{
	int a[] = { 16,2,77,29,3,33,43,3,2,3,3,2 };
	vector<int> v1(a, a + sizeof(a) / sizeof(int));//指针，也属于最原始的迭代器
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// 头删
	v1.erase(v1.begin());//这里不是传位置，而是迭代器
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// 头插 
	v1.insert(v1.begin(), 100);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// 删除第3个数据
	v1.erase(v1.begin() + 2);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// 删除3，但是不知道3在哪个位置，怎么办？
	vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);//find属于算法库，传参初始末尾迭代器以及要查找的数字
	//find如果找到返回第一次出现的位置迭代器，如果找不到返回最后一个元素下一个位置迭代器
	//auto pos = find(v1.begin(), v1.end(), 3);
	/*if (pos != v1.end())
	{
		v1.erase(pos);
	}*/

	// 删除所有的3 -- 涉及迭代器失效！后面解决
	while (pos != v1.end())
	{
		v1.erase(pos);
		//pos = find(pos+1, v1.end(), 3);//删除操作后pos就不能用了
		pos = find(v1.begin(), v1.end(), 3);
	}
	//补充：迭代器失效！~
	//- 序列式容器删除元素：内存调整，迭代器可能失效。
	//- 序列式容器插入元素（如vector、deque），关联式容器（如set、map）：容量不足重分配内存，所有迭代器失效。
	//- 容器resize / clear：改变大小或清空，迭代器失效。
	//- 移动 / 赋值操作：原容器内容改变，迭代器不再指向有效元素。
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	v1.assign(10, 1);//清楚所有内容，分配10个1，不常用
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}


int main()
{
	string s1("hello world");
	bit::vector<string> v1;
	bit::vector<string> v2;
	v1.push_back(s1);
	v2 = v1;
	/*bit::test_vector1();
	bit::test_vector2();
	bit::test_vector3();
	bit::test_vector4();
	bit::test_vector5();
	bit::test_vector6();*/
	test_vector3();
	//vector<int> v(10, 1);
	//int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//bit::vector<int> v3(a, a + 10);
	//cout << v3.size();
	return 0;
}