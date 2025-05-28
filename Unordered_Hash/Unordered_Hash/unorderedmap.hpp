#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include"HashTable.hpp"
using namespace std;

namespace bit
{
	template<class K,class V>
	class unordered_map
	{
		struct Keyofmap
		{
		public:
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename hash_backet::HashTable<K, pair<const K, V>, Keyofmap>::iterator iterator;
		typedef typename hash_backet::HashTable<K, pair<const K, V>, Keyofmap>::const_iterator const_iterator;


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

		V& operator[](const K& k)
		{
			pair<iterator, bool> ret = insert(make_pair(k, V()));
			return ret.first->second;
		}

		pair<iterator,bool> insert(const pair<K, V>& kv)
		{
			pair< hash_backet::HashTable<K, pair<const K, V>, Keyofmap>::iterator ,bool> ret=_t.insert(kv);
			return pair<iterator, bool>(ret.first, ret.second);
		}

		bool erase(const K& k)
		{
			return _t.erase(k);
		}
	private:
		hash_backet::HashTable<K, pair<const K, V>, Keyofmap> _t;
	};
}