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

		pair<iterator,bool> insert(const K& k)//set�����iterator����const��������insert���������ͨ���������������ﲻ��ֱ�ӹ���const������������Ҫ��дһ�����캯��
		{
			pair<typename RBTree<K, K, Keyofset>::iterator,bool> ret=_t.Insert(k);//���ﷵ�ص���iterator����ͨ��iterator������set�е�iterator=const iterator
			return pair<iterator,bool>(ret.first, ret.second);//���ﲻ��ֱ�Ӵ�iteratorֱ�ӱ�Ϊconst iterator������Ҫ�ڵ�������������������һ������
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

