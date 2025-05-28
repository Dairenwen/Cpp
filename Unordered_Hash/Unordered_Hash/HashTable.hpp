#pragma once
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#define PRIMECOUNT 28
using namespace std;

//这里来实现哈希

namespace open_address//这里是开放地址法
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
			return (size_t)k;//对浮点型和无符号数进行了统一处理
		}
	};

	//template<class T>
	//size_t BKDRHash(const T* str)
	//{
	//	register size_t hash = 0;
	//	while (size_t ch = (size_t)*str++)
	//	{
	//		hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..  
	//		// 有人说将乘法分解为位运算及加减法可以提高效率，如将上式表达为：hash = hash << 7 + hash << 1 + hash + ch;  
	//		// 但其实在Intel平台上，CPU内部对二者的处理效率都是差不多的，  
	//		// 我分别进行了100亿次的上述两种运算，发现二者时间差距基本为0（如果是Debug版，分解成位运算后的耗时还要高1/3）；  
	//		// 在ARM这类RISC系统上没有测试过，由于ARM内部使用Booth's Algorithm来模拟32位整数乘法运算，它的效率与乘数有关：  
	//		// 当乘数8-31位都为1或0时，需要1个时钟周期  
	//		// 当乘数16-31位都为1或0时，需要2个时钟周期  
	//		// 当乘数24-31位都为1或0时，需要3个时钟周期  
	//		// 否则，需要4个时钟周期  
	//		// 因此，虽然我没有实际测试，但是我依然认为二者效率上差别不大          
	//	}
	//	return hash;
	//}

	template<>
	struct DefaultHashFunc<string>
	{
		size_t operator()(const string& s)
		{
			//模板的特化
			//使用特殊的hash字符串算法来解决
			size_t hashi = 0;
			for (const auto& ch : s)
			{
				hashi = hashi * 131 + ch;
			}
			return hashi;
		}
	};

	template<class K, class V, class HashFunc = DefaultHashFunc<K>>//增加一个仿函数用于处理字符串取值
	class HashTable
	{
	public:
		HashTable()
		{
			////先将vector简单扩容，防止在插入时vector的size为0
			//_v.resize(10);//先扩容十个单位
			//_n = 0;

			//提供一种更加高效的扩容策略：以容量为质数进行扩容，具体方式采用质数表
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
			//由于还没有实现multi版本，因此不能有相同的数据进行插入
			if (Find(kv.first))
			{
				return false;
			}
			//先来检查扩容
			if ((double)_n / (double)_v.size() >= 0.7)//将负载因子设置为0.7，计算方法为有效数据/总容量
			{
				size_t newsize = _v.size() * 2;
				HashTable<K, V> newHT;
				newHT._v.resize(newsize);//扩容映射关系改变，要再次插入
				for (size_t i = 0; i < _v.size(); i++)
				{
					newHT.insert(_v[i]._kv);
				}
				_v.swap(newHT._v);//互换的是数组，_n有效数据没有变，不需要交换
			}

			HashFunc func;
			size_t tmphashi = func(kv.first);
			size_t hashi = tmphashi % _v.size();//映射，不使用capacity是因为如果后面越界访问size后的空间会报错
			if (_v[hashi].status != Exist)
			{
				_v[hashi]._kv = kv;
				_v[hashi].status = Exist;
				_n++;
				return true;
			}
			else//再来线性探测
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
		size_t _n;//记录有效数据个数
	};
}



//这里来实现哈希桶
namespace hash_backet
{
	template<class K>
	struct DefaultHashFunc
	{
		size_t operator()(const K& k)
		{
			return (size_t)k;//对浮点型和无符号数进行了统一处理
		}
	};

	template<>
	struct DefaultHashFunc<string>
	{
		size_t operator()(const string& s)
		{
			//模板的特化
			//使用特殊的hash字符串算法来解决
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
		//由于要存储数据以及表示结点
		T _data;
		HashData<T>* _next;
	};

	template<class K, class T, class KeyofT, class HashFunc>
	class HashTable;//事先声明一下，防止初始化失败

	template<class K, class T, class Ptr, class Ref, class KeyofT, class HashFunc >
	struct HTIterator
	{
		typedef HashData<T> Node;
		typedef HTIterator< K, T , Ptr , Ref, KeyofT, HashFunc> Self;
		typedef HTIterator< K, T,T&, T*, KeyofT, HashFunc> iterator;


		HTIterator(Node* node, const HashTable<K, T, KeyofT, HashFunc>* hs)//只有普通的构造，const修饰传过来权限放大,hs前类型要加上const
			:_node(node)
			, _hs(hs)
		{ }

		HTIterator(const iterator& iterator)//为set的insert返回构造迭代器做好准备！
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

		Self& operator++()//前置++
		{
			if (_node->_next)//如果桶的下一个还存在
			{
				_node = _node->_next;
			}
			else
			{
				//这里要计算在第几个桶
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
		const HashTable<K, T, KeyofT,HashFunc>* _hs;//由于还没有哈希表，先声明一下
		//为什么这里的成员变量要有
	};

	template<class K,class T,class KeyofT,class HashFunc=DefaultHashFunc<K>>
	class HashTable
	{
		template<class K, class T,class Ptr,class Ref, class KeyofT, class HashFunc >
		friend struct HTIterator;//有元类进行声明要带上模板！
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
			//由于对自定义类型不会做出析构处理，需要手动释放空间
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

			//先检查扩容情况
			if (_n == _table.size())//这里的负载因子设置为1
			{
				size_t newsize = _table.size() * 2;
				HashTable<K, T,KeyofT> newHT;
				newHT._table.resize(newsize);
				for (size_t i = 0; i < _table.size(); i++)
				{
					//遍历旧表，插入新表
					Node* cur = _table[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = func(key(t)) % newsize;
						//进行头插
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