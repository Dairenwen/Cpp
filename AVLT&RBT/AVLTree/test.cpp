#pragma once
#include<iostream>
#include<set>
#include<map>
#include<list>
#include<string>
#include<vector>
#include"AVLTree.hpp"
#include"Map.hpp"
#include"Set.hpp"
#include<assert.h>
using namespace std;

//void test_AVLTree()
//{
//	vector<int> v = { 16,3,7,11,9,26,18,14,15 };
//	AVLTree<int, int> avl;
//	for (size_t i = 0; i < v.size(); ++i)
//	{
//		avl.Insert(make_pair(v[i], i));
//		cout << "IsBalance:"<<v[i] <<" " << avl.IsBalance() << endl;
//	}
//	avl.InOrder();
//
//	cout << endl;
//}
//
//void test_RedBlackTree()
//{
//	vector<int> v = { 16,3,7,11,9,26,18,14,15 };
//	RBTree<int, int> rbt;
//	for (size_t i = 0; i < v.size(); ++i)
//	{
//		rbt.Insert(make_pair(v[i], i));
//		cout << "\n" << endl;
//		rbt.InOrder();
//		cout << rbt.IsBalance() << endl;
//	}
//	cout << rbt.Height() << endl;
//	//rbt.InOrder();
//}

int test()
{
	//test_AVLTree();
	//test_RedBlackTree();
	//const int N = 10000000;
	//vector<int> v;
	//v.reserve(N);
	//srand(time(0));

	//for (size_t i = 0; i < N; i++)
	//{
	//	v.push_back(i);
	//}

	//RBTree<int, int> rbt;
	//for (auto e : v)
	//{
	//	rbt.Insert(make_pair(e, e));
	//	//cout << "Insert:" << e << "->" << t.IsBalance() << endl;
	//}
	//cout << rbt.IsBalance() << endl;
	//cout << rbt.Height() << endl;

	//AVLTree<int, int> avlt;
	//for (auto e : v)
	//{
	//	avlt.Insert(make_pair(e, e));
	//	//cout << "Insert:" << e << "->" << t.IsBalance() << endl;
	//}
	//cout << avlt.IsBalance() << endl;
	//cout << avlt.Height() << endl;

	return 0;
}

int main()
{
	map<int, int> map;
	map.insert(make_pair(1, 1));
	bit::map<int, int> m;
	m[1] = 1;
	m[2] = 2;
	m[3] = 3;

	bit::map<int, int>::iterator mit = m.begin();
	//auto mit = m.begin();
	/*while (mit != m.end())
	{
		mit->first = 1;
		mit->second = 2;

		cout << mit->first << ":" << mit->second << endl;
		++mit;
	}*/
	cout << endl;

	for (const auto& kv : m)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
	cout << endl;

	bit::set<int> s;
	s.insert(5);
	s.insert(2);
	s.insert(2);
	s.insert(12);
	s.insert(22);
	s.insert(332);
	s.insert(7);
	bit::set<int>::iterator it = s.begin();
	/*while (it != s.end())
	{
		if (*it % 2 == 0)
		{
			*it += 10;
		}

		cout << *it << " ";
		++it;
	}
	cout << endl;*/

	for (const auto& e : s)
	{
		cout << e << " ";
	}
	cout << endl;

	return 0;
}