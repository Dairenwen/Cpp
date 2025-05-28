#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#define PRIMECOUNT 28
using namespace std;

//������ʵ�ֹ�ϣ

namespace open_address//�����ǿ��ŵ�ַ��
{
	enum Status
	{
		Exist,
		Empty,
		Delete
	};

	template<class K, class V>
	struct HashData
	{
		HashData(const pair<K, V>& kv)
			:_kv(kv)
			, status(Empty)
		{
		}

		HashData()
			:_kv()
			, status(Empty)
		{
		}

		pair<K, V> _kv;
		Status status;
	};

	template<class K>
	struct DefaultHashFunc
	{
		size_t operator()(const K& k)
		{
			return (size_t)k;//�Ը����ͺ��޷�����������ͳһ����
		}
	};

	//template<class T>
	//size_t BKDRHash(const T* str)
	//{
	//	register size_t hash = 0;
	//	while (size_t ch = (size_t)*str++)
	//	{
	//		hash = hash * 131 + ch;   // Ҳ���Գ���31��131��1313��13131��131313..  
	//		// ����˵���˷��ֽ�Ϊλ���㼰�Ӽ����������Ч�ʣ��罫��ʽ���Ϊ��hash = hash << 7 + hash << 1 + hash + ch;  
	//		// ����ʵ��Intelƽ̨�ϣ�CPU�ڲ��Զ��ߵĴ���Ч�ʶ��ǲ��ģ�  
	//		// �ҷֱ������100�ڴε������������㣬���ֶ���ʱ�������Ϊ0�������Debug�棬�ֽ��λ�����ĺ�ʱ��Ҫ��1/3����  
	//		// ��ARM����RISCϵͳ��û�в��Թ�������ARM�ڲ�ʹ��Booth's Algorithm��ģ��32λ�����˷����㣬����Ч��������йأ�  
	//		// ������8-31λ��Ϊ1��0ʱ����Ҫ1��ʱ������  
	//		// ������16-31λ��Ϊ1��0ʱ����Ҫ2��ʱ������  
	//		// ������24-31λ��Ϊ1��0ʱ����Ҫ3��ʱ������  
	//		// ������Ҫ4��ʱ������  
	//		// ��ˣ���Ȼ��û��ʵ�ʲ��ԣ���������Ȼ��Ϊ����Ч���ϲ�𲻴�          
	//	}
	//	return hash;
	//}

	template<>
	struct DefaultHashFunc<string>
	{
		size_t operator()(const string& s)
		{
			//ģ����ػ�
			//ʹ�������hash�ַ����㷨�����
			size_t hashi = 0;
			for (const auto& ch : s)
			{
				hashi = hashi * 131 + ch;
			}
			return hashi;
		}
	};

	template<class K, class V, class HashFunc = DefaultHashFunc<K>>//����һ���º������ڴ����ַ���ȡֵ
	class HashTable
	{
	public:
		HashTable()
		{
			////�Ƚ�vector�����ݣ���ֹ�ڲ���ʱvector��sizeΪ0
			//_v.resize(10);//������ʮ����λ
			//_n = 0;

			//�ṩһ�ָ��Ӹ�Ч�����ݲ��ԣ�������Ϊ�����������ݣ����巽ʽ����������
			_v.resize(GetNextPrime(1));
		}

		size_t GetNextPrime(size_t prime)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
			  53,         97,         193,       389,       769,
			  1543,       3079,       6151,      12289,     24593,
			  49157,      98317,      196613,    393241,    786433,
			  1572869,    3145739,    6291469,   12582917,  25165843,
			  50331653,   100663319,  201326611, 402653189, 805306457,
			  1610612741, 3221225473, 4294967291
			};

			size_t i = 0;
			for (; i < PRIMECOUNT; ++i)
			{
				if (__stl_prime_list[i] > prime)
					return __stl_prime_list[i];
			}

			return __stl_prime_list[i];
		}

		bool insert(const pair<K, V>& kv)
		{
			//���ڻ�û��ʵ��multi�汾����˲�������ͬ�����ݽ��в���
			if (Find(kv.first))
			{
				return false;
			}
			//�����������
			if ((double)_n / (double)_v.size() >= 0.7)//��������������Ϊ0.7�����㷽��Ϊ��Ч����/������
			{
				size_t newsize = _v.size() * 2;
				HashTable<K, V> newHT;
				newHT._v.resize(newsize);//����ӳ���ϵ�ı䣬Ҫ�ٴβ���
				for (size_t i = 0; i < _v.size(); i++)
				{
					newHT.insert(_v[i]._kv);
				}
				_v.swap(newHT._v);//�����������飬_n��Ч����û�б䣬����Ҫ����
			}

			HashFunc func;
			size_t tmphashi = func(kv.first);
			size_t hashi = tmphashi % _v.size();//ӳ�䣬��ʹ��capacity����Ϊ�������Խ�����size��Ŀռ�ᱨ��
			if (_v[hashi].status != Exist)
			{
				_v[hashi]._kv = kv;
				_v[hashi].status = Exist;
				_n++;
				return true;
			}
			else//��������̽��
			{
				while (_v[hashi].status == Exist)
				{
					hashi++;
					hashi %= _v.size();
				}
				_v[hashi]._kv = kv;
				_v[hashi].status = Exist;
				_n++;
				return true;
			}
		}

		HashData<const K, V>* Find(const K& k)
		{
			HashFunc func;
			size_t tmphashi = func(k);
			size_t hashi = tmphashi % _v.size();
			while (_v[hashi].status != Empty)
			{
				if (_v[hashi]._kv.first == k)
				{
					return (HashData<const K, V>*) & (_v[hashi]);
				}
				hashi++;
				hashi %= _v.size();
			}
			return nullptr;
		}

		bool erase(const pair<K, V>& kv)
		{
			HashData<K, V>* ret = Find(kv);
			if (ret)
			{
				ret->status = Delete;
				_n--;
			}
			else
			{
				return false;
			}
		}
	private:
		vector<HashData<K, V>> _v;
		size_t _n;//��¼��Ч���ݸ���
	};
}



//������ʵ�ֹ�ϣͰ
namespace hash_backet
{
	template<class K>
	struct DefaultHashFunc
	{
		size_t operator()(const K& k)
		{
			return (size_t)k;//�Ը����ͺ��޷�����������ͳһ����
		}
	};

	template<>
	struct DefaultHashFunc<string>
	{
		size_t operator()(const string& s)
		{
			//ģ����ػ�
			//ʹ�������hash�ַ����㷨�����
			size_t hashi = 0;
			for (const auto& ch : s)
			{
				hashi = hashi * 131 + ch;
			}
			return hashi;
		}
	};


	template<class T>
	struct HashData
	{
		HashData(const T& t)
			:_data(t)
			,_next(nullptr)
		{ }

		HashData()
			:_next(nullptr)
		{}
		//����Ҫ�洢�����Լ���ʾ���
		T _data;
		HashData<T>* _next;
	};

	template<class K, class T, class KeyofT, class HashFunc>
	class HashTable;//��������һ�£���ֹ��ʼ��ʧ��

	template<class K, class T, class Ptr, class Ref, class KeyofT, class HashFunc >
	struct HTIterator
	{
		typedef HashData<T> Node;
		typedef HTIterator< K, T , Ptr , Ref, KeyofT, HashFunc> Self;
		typedef HTIterator< K, T,T&, T*, KeyofT, HashFunc> iterator;


		HTIterator(Node* node, const HashTable<K, T, KeyofT, HashFunc>* hs)//ֻ����ͨ�Ĺ��죬const���δ�����Ȩ�޷Ŵ�,hsǰ����Ҫ����const
			:_node(node)
			, _hs(hs)
		{ }

		HTIterator(const iterator& iterator)//Ϊset��insert���ع������������׼����
		{
			_node = iterator._node;
			_hs = iterator._hs;
		}

		Ptr operator*()
		{
			return _node->_data;
		}
	
		Ref operator->()
		{
			return &(_node->_data);
		}

		Self& operator++()//ǰ��++
		{
			if (_node->_next)//���Ͱ����һ��������
			{
				_node = _node->_next;
			}
			else
			{
				//����Ҫ�����ڵڼ���Ͱ
				KeyofT key;
				HashFunc func;
				size_t hashi = func(key(_node->_data)) % (_hs->_table.size());
				hashi++;
				for (size_t i = hashi; i < _hs->_table.size(); i++)
				{
					if (_hs->_table[i])
					{
						_node = _hs->_table[i];
						return *this;
					}
				}
				_node = nullptr;
			}
			return *this;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		bool operator==(const Self& s)
		{
			return _node == s._node;
		}

		Node* _node;
		const HashTable<K, T, KeyofT,HashFunc>* _hs;//���ڻ�û�й�ϣ��������һ��
		//Ϊʲô����ĳ�Ա����Ҫ��
	};

	template<class K,class T,class KeyofT,class HashFunc=DefaultHashFunc<K>>
	class HashTable
	{
		template<class K, class T,class Ptr,class Ref, class KeyofT, class HashFunc >
		friend struct HTIterator;//��Ԫ���������Ҫ����ģ�壡
	public:

		typedef HashData<T> Node;
		typedef HTIterator<K, T,T&,T*, KeyofT, HashFunc> iterator;
		typedef HTIterator<K, T,const T&,const T*, KeyofT, HashFunc> const_iterator;


		HashTable()
		{
			_n = 0;
			_table.resize(10, nullptr);
		}

		~HashTable()
		{
			//���ڶ��Զ������Ͳ�����������������Ҫ�ֶ��ͷſռ�
			for (size_t i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				Node* prev = nullptr;
				while (cur)
				{
					prev = cur;
					cur = cur->_next;
					delete prev;
				}
				_table[i] = nullptr;
			}
		}

		iterator begin()
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i])
				{
					return iterator(_table[i], this);
				}
			}
			return iterator(nullptr, this);
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		const_iterator cbegin()const
		{
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i])
				{
					return const_iterator(_table[i], this);
				}
			}
			return const_iterator(nullptr, this);
		}

		const_iterator cend()const
		{
			return const_iterator(nullptr, this);
		}

		pair<iterator,bool> insert(const T& t)
		{
			HashFunc func;
			KeyofT key;
			iterator ret = Find(key(t));
			if(ret._node)
			{
				return make_pair(iterator(nullptr,this),false);
			}

			//�ȼ���������
			if (_n == _table.size())//����ĸ�����������Ϊ1
			{
				size_t newsize = _table.size() * 2;
				HashTable<K, T,KeyofT> newHT;
				newHT._table.resize(newsize);
				for (size_t i = 0; i < _table.size(); i++)
				{
					//�����ɱ������±�
					Node* cur = _table[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = func(key(t)) % newsize;
						//����ͷ��
						cur->_next = newHT._table[hashi];
						newHT._table[hashi] = cur;
						cur = next;
					}
				}
				_table.swap(newHT._table);
			}

			size_t hashi = func(key(t)) % _table.size();
			Node* newnode = new Node(t);
			newnode->_next = _table[hashi];
			_table[hashi] = newnode;
			_n++;
			return make_pair(iterator(newnode, this),true);

		}

		iterator Find(const K& k)
		{
			HashFunc func;
			KeyofT key;
			size_t hashi = func(k) % _table.size();
			Node* cur = _table[hashi];
			while (cur)
			{
				if (func(key(cur->_data))==func(k))
				{
					return iterator(cur,this);
				}
				cur = cur->_next;
			}
			return iterator(nullptr,this);
		}

		bool erase(const K& k)
		{
			iterator ret = Find(k);
			if (ret._node)
			{
				HashFunc func;
				KeyofT key;
				size_t hashi = func(k) % _table.size();
				Node* cur = _table[hashi];
				Node* prev = nullptr;
				while (cur)
				{
					if (func(key(cur->_data)) == func(k))
					{
						if (prev == nullptr)
						{
							_table[hashi] = cur->_next;
						}
						else
						{
							prev->_next = cur->_next;
						}
						_n--;
						delete cur;
						return true;
					}
					else
					{
						prev = cur;
						cur = cur->_next;
					}
				}
				return false;
			}
			else
			{
				return false;
			}
		}

		void print()
		{
			KeyofT key;
			for (size_t i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					printf("[%d]->", i);
					cout << key(cur->_data)<< "->" << key(cur->_data) << endl;
					cur = cur->_next;
				}
			}
		}
	private:
		vector<Node*> _table;
		size_t _n;

	};
}