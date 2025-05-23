#pragma once
#include<iostream>
#include<set>
#include<map>
#include<list>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

//介绍一下红黑树的性质：
//红黑树通过对任何一条从根到叶子的路径上各个节点着色的方式，确保没有一条路径会比其他路径长出两倍，因而是接近平衡的
//性质：
//1.每个节点要么是红色，要么是黑色
//2.根节点是黑色
//3.每个叶子节点（NIL）是黑色（注意这里的叶子节点是指空节点）
//4.如果一个节点是红色，那么它的两个子节点都是黑色
//5.对于每个节点，从该节点到其所有后代叶子节点的简单路径上，均包含相同数目的黑色节点
//如果要计算路径，那么根到空结点算一条路径

//简单与AVL树的比较：
//1.虽然AVL高度比红黑树低，但是红黑树的旋转次数比AVL树少，所以红黑树的插入删除效率比AVL树高
//2.AVL插入删除可能需要多次旋转，而红黑树最多只需要两次旋转


enum Colour
{
	RED,
	BLACK
}; 


template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _t;
	Colour _col;
	RBTreeNode(const T& t)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _t(t)
		, _col(RED)
	{
	}
};

template<class T,class Ptr,class Ref>
struct _TreeIterator
{
public:
	typedef RBTreeNode<T> Node;
	typedef _TreeIterator<T,Ptr,Ref> Self;
	typedef _TreeIterator<T, T&,T*> iterator;//这里是为了构造const迭代器


	Node* _node;

	_TreeIterator(Node* node)
		:_node(node)
	{ }

	_TreeIterator(const iterator& iterator)
	{
		_node = iterator._node;
	}

	Ptr operator*()
	{
		return _node->_t;
	}

	Ref operator->()
	{
		return &(_node->_t);
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	Self& operator++()//前置++
	{
		//如果parent的右边存在，那么就跳到右边的最小子树
		//如果不存在就走到cur为parent左边位置，返回parent
		Node* cur = _node;
		Node* parent = cur->_parent;
		if (cur->_right)
		{
			Node* Leftmin = cur->_right->_left;
			Node* prev = cur->_right;
			while (Leftmin)
			{
				prev = Leftmin;
				Leftmin = Leftmin->_left;
			}
			_node = prev;
		}
		else
		{
			while (parent)
			{
				if (parent->_left == cur)
				{
					break;
				}
				else
				{
					cur = parent;
					parent = cur->_parent;
				}
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator++(int)//后置++
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	//库中的end实际上是一个哨兵位，而不是用nullptr来代替
	//实际上多了一个哨兵位会非常麻烦，旋转的时候要进行调整
	Self& operator--()
	{
		Node* cur = _node;
		Node* parent = cur->_parent;
		if (cur->_left)
		{
			Node* Rightmax = cur->_left->_right;
			Node* prev = cur->_left;
			while (Rightmax)
			{
				prev = Rightmax;
				Rightmax = Rightmax->_right;
			}
			_node = prev;
		}
		else
		{
			while (parent)
			{
				if (parent->_right == cur)
				{
					break;
				}
				else
				{
					cur = parent;
					parent = cur->_parent;
				}
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--(int)//后置--
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}
};

template<class K, class T,class KeyofT>
class RBTree
{
public:
	typedef RBTreeNode<T> Node;
	typedef _TreeIterator<T,T&,T*> iterator;
	typedef _TreeIterator<T, const T&,const T*> const_iterator;

	RBTree()
		:_root(nullptr)
	{
	}

	iterator Find(const T& t)
	{
		KeyofT k;
		Node* cur = _root;
		while (cur)
		{
			if (k(t) > k(cur))
			{
				cur = cur->_right;
			}
			else if (k(t) < k(cur))
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return iterator(nullptr);
	}

	iterator begin()
	{
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			prev = cur;
			cur = cur->_left;
		}
		return iterator(prev);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator cbegin()const
	{
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			prev = cur;
			cur = cur->_left;
		}
		return const_iterator(prev);
	}

	const_iterator cend()const
	{
		return const_iterator(nullptr);
	}
	//红黑树的插入
	//1.插入的节点默认是红色，这是因为如果插入黑色节点，会改变从根节点到该插入节点路径上的黑色节点数量，从而破坏红黑树的 
	//“从一个节点到该节点的子孙节点的所有路径上包含相同数目的黑色节点” 这一性质，修复起来相对复杂。而插入红色节点，
	//可能只会破坏 “如果一个节点是红色的，则它的两个子节点都是黑色的” 这一性质，这种情况相对容易处理。
	pair<iterator,bool> Insert(const T& t)
	{
		//情况 1：插入的节点是根节点
			//若插入的节点是树的根节点，把该节点颜色设为黑色，这样能满足根节点为黑色的性质。
		//情况 2：父节点是黑色
			//若父节点 P 是黑色，插入红色节点不会破坏红黑树的任何性质，无需进行额外的颜色调整或树结构调整。
		//情况 3：父节点是红色
			//若父节点 P 是红色，就破坏了 “不能有两个连续的红色节点” 这一性质，此时需要根据叔叔节点 U 的颜色进一步分类处理。
		KeyofT k;
		//总共可以分为两种情况
		//1.uncle存在且为红色，此时需要将parent和uncle都改为黑色，grandparent改为红色，
		// 然后递归向上调整,如果grandparent为根节点，那么需要将其改为黑色
		//2.uncle不存在或者为黑色，此时需要进行旋转调整，并且进行颜色调整
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			if (k(t) < k(cur->_t))
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (k(t) > k(cur->_t))
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				return make_pair(nullptr,false);
			}
		}
		Node* newnode = new Node(t);
		Node* copy = newnode;
		if (_root == nullptr)
		{
			_root = newnode;
			_root->_col = BLACK;
			return make_pair(iterator(copy), true);
		}
		if (k(t) > k(prev->_t))
		{
			prev->_right = newnode;
		}
		else
		{
			prev->_left = newnode;
		}
		newnode->_parent = prev;
		newnode->_col = RED;
		//设置循环条件
		while (prev && prev->_col == RED)
		{
			Node* grandparent = prev->_parent;
			if (prev == grandparent->_left)//prev在grandparent左
			{
				Node* uncle = grandparent->_right;
				//第一种情况，uncle存在且为RED
				if (uncle && uncle->_col == RED)
				{
					prev->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					newnode = grandparent;
					prev = newnode->_parent;
				}
				else//另一种情况，uncle不存在或者uncle存在且为黑
				{
					//都要进行旋转，并且要改变颜色
					//具体是双旋转还是单旋转要依据cur接在parent的位置而定
					if (prev->_left == newnode)
					{
						RotateR(grandparent);
						prev->_col = BLACK;
						newnode->_col=grandparent->_col = RED;
					}
					else
					{
						//先左旋再右旋
						RotateL(prev);
						RotateR(grandparent);
						newnode->_col = BLACK;
						prev->_col = grandparent->_col = RED;
					}
					//调整过后已经平衡，所以直接跳出循环
					break;
				}
			}
			else//prev在grandparent右
			{
				Node* uncle = grandparent->_left;
				//第一种情况，uncle存在且为RED
				if (uncle && uncle->_col == RED)
				{
					prev->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					newnode= grandparent;
					prev =newnode->_parent;
				}
				else//另一种情况，uncle不存在或者uncle存在且为黑
				{
					//都要进行旋转，并且要改变颜色
					//具体是双旋转还是单旋转要依据cur接在parent的位置而定
					if (prev->_right == newnode)
					{
						RotateL(grandparent);
						prev->_col = BLACK;
						newnode->_col = grandparent->_col = RED;
					}
					else
					{
						//先右旋再左旋
						RotateR(prev);
						RotateL(grandparent);
						newnode->_col = BLACK;
						prev->_col=grandparent->_col = RED;
					}
					//调整过后已经平衡，所以直接跳出循环
					break;
				}
			}
		}
		//最后对根结点的颜色统一处理为BLACK
		_root->_col = BLACK;
		return make_pair(iterator(copy), true);
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		Node* ppnode = parent->_parent;
		parent->_right = curleft;
		cur->_left = parent;
		//这里curleft有可能是不存在的，那么需要特殊判断一下
		if (curleft)
		{
			curleft->_parent = parent;

		}
		//parent有可能为根结点，根节点需要改变，判断一下
		cur->_parent = ppnode;
		if (parent == _root)
		{
			_root = cur;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
		}
		parent->_parent = cur;
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		Node* ppnode = parent->_parent;
		parent->_left = curright;
		cur->_right = parent;
		//这里curleft有可能是不存在的，那么需要特殊判断一下
		if (curright)
		{
			curright->_parent = parent;

		}
		//parent有可能为根结点，根节点需要改变，判断一下
		cur->_parent = ppnode;
		if (parent == _root)
		{
			_root = cur;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
		}
		parent->_parent = cur;
	}

	void InOrder()
	{
		return _InOrder(_root);
	}

	int Height()
	{
		return _Height(_root);
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}
private:

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << " " << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool CheckColor(Node* root, int blacknum, int benchmark)
	{
		if (root == nullptr)
		{
			if (blacknum != benchmark)
			{
				return false;
			}
			else
				return true;
		}

		if (root->_col == BLACK)
		{
			blacknum++;
		}

		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "出现连续红色节点" << endl;
			return false;
		}

		return CheckColor(root->_left, blacknum, benchmark)
			&& CheckColor(root->_right, blacknum, benchmark);
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}

		if (root->_col != BLACK)
		{
			cout << "红色节点的子节点必须为黑色" << endl;
			return false;
		}

		int Benchmark = 0;
		Node* cur = root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				Benchmark++;
			}
			cur = cur->_left;
		}

		return CheckColor(root, 0, Benchmark);
	}

	Node* _root;
};