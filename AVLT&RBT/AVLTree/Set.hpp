#pragma once
#include<iostream>
#include"Red-Black Tree.hpp"
using namespace std;


namespace bit
{
	template<class K>
	class set
	{
	public:
		//typedef _TreeIterator<K> iterator;
		 

		struct Keyofset
		{
			const K& operator()(const K& p)
			{
				return p;
			}
		};

		typedef typename RBTree<K,K, Keyofset>::const_iterator iterator;
		typedef typename RBTree<K, K, Keyofset>::const_iterator const_iterator;

		pair<iterator,bool> insert(const K& k)//set这里的iterator就是const迭代器，insert传入的是普通迭代器，所以这里不能直接构造const迭代器，才需要多写一个构造函数
		{
			pair<typename RBTree<K, K, Keyofset>::iterator,bool> ret=_t.Insert(k);//这里返回的是iterator中普通的iterator，但是set中的iterator=const iterator
			return pair<iterator,bool>(ret.first, ret.second);//这里不能直接从iterator直接变为const iterator，所以要在迭代器拷贝构造中增加一个函数
		}

		void InOrder()
		{
			_t.InOrder();
		}

		iterator begin()const
		{
			return _t.cbegin();
		}

		iterator end()const
		{
			return _t.cend();
		}

		const_iterator cbegin()const
		{
			return _t.cbegin();
		}

		const_iterator cend()const
		{
			return _t.cend();
		}
	private:
		RBTree<K, K, Keyofset> _t;
	};
}

