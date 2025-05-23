#pragma once 
#include<iostream>
#include"Red-Black Tree.hpp"
using namespace std;


namespace bit
{
	template<class K, class V>
	class map
	{
	public:
		//typedef _TreeIterator<pair<K,V>> iterator;

		struct Keyofmap
		{
			const K& operator()(const pair<K, V>& p)
			{
				return p.first;
			}
		};

		typedef typename RBTree<K, pair<const K, V>, Keyofmap>::iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, Keyofmap>::const_iterator const_iterator;


		iterator begin()
		{
			return _t.begin();
		}

		iterator end()
		{
			return _t.end();
		}

		const_iterator cbegin()const
		{
			return _t.cbegin();
		}

		const_iterator cend()const
		{
			return _t.cend();
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}

		pair<iterator,bool> insert(const pair<K, V>& kv)
		{
			pair<typename RBTree<K, pair<const K, V>, Keyofmap>::iterator, bool> ret = _t.Insert(kv);
			return pair<iterator, bool>(ret.first, ret.second);
		}

		void InOrder()
		{
			_t.InOrder();
		}
	private:
		RBTree<K, pair<const K, V>, Keyofmap> _t;
	};

}



