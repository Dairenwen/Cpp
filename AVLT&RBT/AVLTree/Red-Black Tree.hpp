#pragma once
#include<iostream>
#include<set>
#include<map>
#include<list>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

//����һ�º���������ʣ�
//�����ͨ�����κ�һ���Ӹ���Ҷ�ӵ�·���ϸ����ڵ���ɫ�ķ�ʽ��ȷ��û��һ��·���������·����������������ǽӽ�ƽ���
//���ʣ�
//1.ÿ���ڵ�Ҫô�Ǻ�ɫ��Ҫô�Ǻ�ɫ
//2.���ڵ��Ǻ�ɫ
//3.ÿ��Ҷ�ӽڵ㣨NIL���Ǻ�ɫ��ע�������Ҷ�ӽڵ���ָ�սڵ㣩
//4.���һ���ڵ��Ǻ�ɫ����ô���������ӽڵ㶼�Ǻ�ɫ
//5.����ÿ���ڵ㣬�Ӹýڵ㵽�����к��Ҷ�ӽڵ�ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ�
//���Ҫ����·������ô�����ս����һ��·��

//����AVL���ıȽϣ�
//1.��ȻAVL�߶ȱȺ�����ͣ����Ǻ��������ת������AVL���٣����Ժ�����Ĳ���ɾ��Ч�ʱ�AVL����
//2.AVL����ɾ��������Ҫ�����ת������������ֻ��Ҫ������ת


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
	typedef _TreeIterator<T, T&,T*> iterator;//������Ϊ�˹���const������


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

	Self& operator++()//ǰ��++
	{
		//���parent���ұߴ��ڣ���ô�������ұߵ���С����
		//��������ھ��ߵ�curΪparent���λ�ã�����parent
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

	Self& operator++(int)//����++
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	//���е�endʵ������һ���ڱ�λ����������nullptr������
	//ʵ���϶���һ���ڱ�λ��ǳ��鷳����ת��ʱ��Ҫ���е���
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

	Self& operator--(int)//����--
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
	//������Ĳ���
	//1.����Ľڵ�Ĭ���Ǻ�ɫ��������Ϊ��������ɫ�ڵ㣬��ı�Ӹ��ڵ㵽�ò���ڵ�·���ϵĺ�ɫ�ڵ��������Ӷ��ƻ�������� 
	//����һ���ڵ㵽�ýڵ������ڵ������·���ϰ�����ͬ��Ŀ�ĺ�ɫ�ڵ㡱 ��һ���ʣ��޸�������Ը��ӡ��������ɫ�ڵ㣬
	//����ֻ���ƻ� �����һ���ڵ��Ǻ�ɫ�ģ������������ӽڵ㶼�Ǻ�ɫ�ġ� ��һ���ʣ��������������״���
	pair<iterator,bool> Insert(const T& t)
	{
		//��� 1������Ľڵ��Ǹ��ڵ�
			//������Ľڵ������ĸ��ڵ㣬�Ѹýڵ���ɫ��Ϊ��ɫ��������������ڵ�Ϊ��ɫ�����ʡ�
		//��� 2�����ڵ��Ǻ�ɫ
			//�����ڵ� P �Ǻ�ɫ�������ɫ�ڵ㲻���ƻ���������κ����ʣ�������ж������ɫ���������ṹ������
		//��� 3�����ڵ��Ǻ�ɫ
			//�����ڵ� P �Ǻ�ɫ�����ƻ��� �����������������ĺ�ɫ�ڵ㡱 ��һ���ʣ���ʱ��Ҫ��������ڵ� U ����ɫ��һ�����ദ��
		KeyofT k;
		//�ܹ����Է�Ϊ�������
		//1.uncle������Ϊ��ɫ����ʱ��Ҫ��parent��uncle����Ϊ��ɫ��grandparent��Ϊ��ɫ��
		// Ȼ��ݹ����ϵ���,���grandparentΪ���ڵ㣬��ô��Ҫ�����Ϊ��ɫ
		//2.uncle�����ڻ���Ϊ��ɫ����ʱ��Ҫ������ת���������ҽ�����ɫ����
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
		//����ѭ������
		while (prev && prev->_col == RED)
		{
			Node* grandparent = prev->_parent;
			if (prev == grandparent->_left)//prev��grandparent��
			{
				Node* uncle = grandparent->_right;
				//��һ�������uncle������ΪRED
				if (uncle && uncle->_col == RED)
				{
					prev->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					newnode = grandparent;
					prev = newnode->_parent;
				}
				else//��һ�������uncle�����ڻ���uncle������Ϊ��
				{
					//��Ҫ������ת������Ҫ�ı���ɫ
					//������˫��ת���ǵ���תҪ����cur����parent��λ�ö���
					if (prev->_left == newnode)
					{
						RotateR(grandparent);
						prev->_col = BLACK;
						newnode->_col=grandparent->_col = RED;
					}
					else
					{
						//������������
						RotateL(prev);
						RotateR(grandparent);
						newnode->_col = BLACK;
						prev->_col = grandparent->_col = RED;
					}
					//���������Ѿ�ƽ�⣬����ֱ������ѭ��
					break;
				}
			}
			else//prev��grandparent��
			{
				Node* uncle = grandparent->_left;
				//��һ�������uncle������ΪRED
				if (uncle && uncle->_col == RED)
				{
					prev->_col = uncle->_col = BLACK;
					grandparent->_col = RED;
					newnode= grandparent;
					prev =newnode->_parent;
				}
				else//��һ�������uncle�����ڻ���uncle������Ϊ��
				{
					//��Ҫ������ת������Ҫ�ı���ɫ
					//������˫��ת���ǵ���תҪ����cur����parent��λ�ö���
					if (prev->_right == newnode)
					{
						RotateL(grandparent);
						prev->_col = BLACK;
						newnode->_col = grandparent->_col = RED;
					}
					else
					{
						//������������
						RotateR(prev);
						RotateL(grandparent);
						newnode->_col = BLACK;
						prev->_col=grandparent->_col = RED;
					}
					//���������Ѿ�ƽ�⣬����ֱ������ѭ��
					break;
				}
			}
		}
		//���Ը�������ɫͳһ����ΪBLACK
		_root->_col = BLACK;
		return make_pair(iterator(copy), true);
	}

	//����
	void RotateL(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		Node* ppnode = parent->_parent;
		parent->_right = curleft;
		cur->_left = parent;
		//����curleft�п����ǲ����ڵģ���ô��Ҫ�����ж�һ��
		if (curleft)
		{
			curleft->_parent = parent;

		}
		//parent�п���Ϊ����㣬���ڵ���Ҫ�ı䣬�ж�һ��
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

	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		Node* ppnode = parent->_parent;
		parent->_left = curright;
		cur->_right = parent;
		//����curleft�п����ǲ����ڵģ���ô��Ҫ�����ж�һ��
		if (curright)
		{
			curright->_parent = parent;

		}
		//parent�п���Ϊ����㣬���ڵ���Ҫ�ı䣬�ж�һ��
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
			cout << root->_kv.first << "����������ɫ�ڵ�" << endl;
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
			cout << "��ɫ�ڵ���ӽڵ����Ϊ��ɫ" << endl;
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