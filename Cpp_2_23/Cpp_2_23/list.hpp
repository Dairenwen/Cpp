#pragma once
#include<iostream>
#include<assert.h>
using namespace std;
#include"ReverseIterator.hpp"
namespace bit
{
	template<class T>
	struct __list_node
	{
		__list_node<T>* prev;
		__list_node<T>* next;
		T val;

		__list_node(const T& t=T())
			:prev(nullptr)
			,next(nullptr)
			,val(t)
		{}

		~__list_node()
		{
			prev = nullptr;
			next = nullptr;
			val = 0;
		}
	};

	template<class T,class Ref,class Ptr>//为什么要传Ref是因为两个结构体太累赘，这样可以简化，要传Ptr是为了给->函数的返回类型也进行模板化
	struct __list_iterator
	{
		typedef __list_node<T> Node;
		typedef __list_iterator<T, Ref,Ptr> self;//这里再次重定义一下方便
		Node* node;

		__list_iterator(Node* _node)
			:node(_node)
		{ }

		Ref operator*()
		{
			return node->val;
		}

		Ptr operator->()//为什么要重载访问成员操作符呢？是因为显式实例化传参也就是vector里面可能保存的是自定义类型而不是内置类型
		{
			return &(node->val);
		}

		self& operator++()//前置
		{
			node = node->next;
			return *this;
		}

		self& operator++(int)//后置
		{
			self tmp(*this);
			node = node->next;
			return tmp;
		}

		self& operator--()//前置
		{
			node = node->prev;
			return *this;
		}

		self& operator--(int)//后置
		{
			self tmp(*this);
			node = node->prev;
			return tmp;
		}

		bool operator!=(const self& it)
		{
			return node != it.node;
		}

		bool operator==(const self& it)
		{
			return node == it.node;
		}

		~__list_iterator()
		{
			node = nullptr;
		}
	};
	//这样实现太过于累赘，最好再添加一个模版参数来实现
	//template<class T>
	//struct __const_list_iterator
	//{
	//	typedef __list_node<T> Node;
	//	Node* node;

	//	__const_list_iterator(Node* _node)
	//		:node(_node)
	//	{
	//	}

	//	const T& operator*()const
	//	{
	//		return node->val;
	//	}

		//__const_list_iterator<T>& operator++()//前置
		//{
		//	node = node->next;
		//	return *this;
		//}

		//__const_list_iterator<T>& operator++(int)//后置
		//{
		//	__const_list_iterator<T> tmp(*this);
		//	node = node->next;
		//	return tmp;
		//}

	//	bool operator!=(const __const_list_iterator<T>& it)
	//	{
	//		return node != it.node;
	//	}

	//	bool operator==(const __const_list_iterator<T>& it)
	//	{
	//		return node == it.node;
	//	}

	//	~__const_list_iterator()
	//	{
	//		node = nullptr;
	//	}
	//};

	template<class T>
	class list
	{
		typedef __list_node<T> Node;
	public:
		/*typedef __list_iterator<T> iterator;
		typedef __const_list_iterator<T> const_iterator;*/
		//typedef const __list_iterator<T> const_iterator;//不能这样使用 const迭代器那么迭代器就不能改变了
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverseiterator<iterator, T&, T*> reverse_iterator;
		typedef Reverseiterator<const_iterator, const T&, const T*> const_reverse_iterator;

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}


		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator crbegin()const
		{
			return const_reverse_iterator(end());
		}


		const_reverse_iterator crend()const
		{
			return const_reverse_iterator(begin());
		}

		void Emptyinit()
		{
			Node* guard = new Node;
			guard->prev = guard;
			guard->next = guard;
			_head = guard;
		}

		list()
		{
			Emptyinit();
		}

		list(const list<T>& l)
		{
			Emptyinit();
			for (auto& e : l)//加上&防止自定义类型深拷贝
			{
				push_back(e);
			}
		}

		list<T>& operator=(list<T> l)
		{
			swap(_head, l._head);
			return *this;
		}

		//void push_back(const T& t)
		//{
		//	Node* newnode = new Node(t);
		//	newnode->prev = _head->prev;
		//	_head->prev->next = newnode;
		//	newnode->next = _head;
		//	_head->prev = newnode;//双向带头循环链表，需要复习！
		//}
		void push_back(const T& t)
		{
			insert(_head, t);
		}

		void pop_back()
		{
			erase(_head->prev);
		}

		void push_front(const T& t)
		{
			insert(_head->next, t);
		}

		void pop_front()
		{
			erase(_head->next);
		}

		iterator begin()
		{
			return _head->next;
		}

		iterator end()
		{
			return _head;
		}

		const_iterator begin()const
		{
			return _head->next;
		}

		const_iterator end()const
		{
			return _head;
		}

		iterator insert(iterator pos, const T& t)
		{
			//无需断言
			Node* prev = pos.node->prev;
			Node* newnode = new Node(t);
			prev->next = newnode;
			newnode->prev = prev;
			newnode->next = pos.node;
			pos.node->prev = newnode;
			return newnode;
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());//不能删除头结点
			Node* prev = pos.node->prev;
			Node* next = pos.node->next;
			prev->next = next;
			next->prev = prev;
			delete pos.node;
			return next;
		}

		size_t size()
		{
			size_t sz = 0;
			iterator it = begin();
			while (it != end())
			{
				sz++;
				it++;
			}
			return sz;
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it=erase(it);//迭代器失效了！！！要注意！！！
			}
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		Node* _head;
	};

	void test_list1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		list<int>::iterator it = lt.begin();//默认发生浅拷贝，无需再

		while (it != lt.end())//这里拷贝返回具有常性，要在！=参数中加上const
		{
			(*it) += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto e : lt)//范围for基于begin和end，编译器会直接替换
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void print(const list<int>& t)
	{
		list<int>::const_iterator cit = t.begin();
		while (cit != t.end())
		{
			cout << *cit << " ";
			cit++;
		}
	}
	void test_list2()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		print(lt);
	}

	struct A
	{
		int _a;
		int _b;
		A(int a = 0, int b = 0)
		{
			_a = a; _b = b;
		}
	};

	void test_list3()
	{
		list<A> l1;
		l1.push_back(A(1, 1));
		l1.push_back(A(2,2));
		l1.push_back(A(3,3));
		l1.push_back(A(4,4));
		auto begin = l1.begin();
		while (begin != l1.end())
		{
			cout << (*begin)._a << " " << (*begin)._b << endl;
			cout << begin->_a << " " << begin->_b << endl;//这里其实应该写为begin->->，但编译器做了优化
			begin++;
		}
	}

	void test_list4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_front(5);
		lt.push_front(6);
		lt.push_front(7);
		lt.push_front(8);
		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;

		lt.pop_front();
		lt.pop_back();

		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;

		lt.clear();
		lt.push_back(10);
		lt.push_back(20);
		lt.push_back(30);
		lt.push_back(40);
		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;

		cout << lt.size() << endl;
	}

	void test_list5()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		for (auto e : lt)
		{
			cout << e << " ";
		}
		cout << endl;

		list<int> lt1(lt);
		for (auto e : lt1)
		{
			cout << e << " ";
		}
		cout << endl;

		list<int> lt2;
		lt2.push_back(10);
		lt2.push_back(20);
		lt2.push_back(30);
		lt2.push_back(40);

		for (auto e : lt2)
		{
			cout << e << " ";
		}
		cout << endl;

		lt1 = lt2;

		for (auto e : lt1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}