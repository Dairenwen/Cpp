#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include"HashTable.hpp"
using namespace std;

namespace bit
{
	template<class K>
	class unordered_set
	{
		struct Keyofset
		{
		public:
			const K& operator()(const K& k)
			{
				return k;
			}
		};
	public:
		typedef typename hash_backet::HashTable<K, K, Keyofset>::const_iterator iterator;
		typedef typename hash_backet::HashTable<K, K, Keyofset>::const_iterator const_iterator;


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

		pair<iterator,bool> insert(const K& k)
		{
			pair<typename hash_backet::HashTable<K, K, Keyofset>::iterator,bool> ret= _t.insert(k);
			return pair<iterator, bool>(ret.first, ret.second);
		}

		bool erase(const K& k)
		{
			return _t.erase(k);
		}
	private:
		hash_backet::HashTable<K, K, Keyofset> _t;
	};
}