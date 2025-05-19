#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
//������������
//1.������������ֵ��С�ڵ�ǰ���
//2.�������������ƶ����ڵ�ǰ���
//3.������������������������Ҳ�ж���������
//������Ҵ�����logn������������n

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode* left;
	BinaryTreeNode* right;
	T val;

	BinaryTreeNode(const T& t)
	{
		left = nullptr;
		right = nullptr;
		val = t;
	}
};

template<class T>
class BinarySearchTree
{
public:
	typedef BinaryTreeNode<T> Node;

	BinarySearchTree()
		:_root(nullptr)
	{ }

	bool Insert(const T& t)
	{
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			if (t < cur->val)
			{
				prev = cur;
				cur = cur->left;
			}
			else if (t > cur->val)
			{
				prev = cur;
				cur = cur->right;
			}
			else
			{
				return false;
			}
		}
		auto newnode = new Node(t);
		//����Ҫ�Ը����Ϊ�����⴦��һ��
		if (_root == nullptr)
		{
			_root = newnode;
			return true;
		}
		if (t < prev->val)
		{
			prev->left = newnode;
		}
		if (t > prev->val)
		{
			prev->right = newnode;
		}
		return true;

	}

	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->left);
		cout << root->val << " ";
		_InOrder(root->right);
	}

	bool find(const T& t)
	{
		Node* cur = _root;
		while (cur)
		{
			if (t < cur->val)
			{
				cur = cur->left;
			}
			else if (t > cur->val)
			{
				cur = cur->right;
			}
			else
			{
				return true;
			}
		}
		return false;
	}

	bool erase(const T& t)
	{
		//��һ�������ҵ�����t�Ľ��
		Node* cur = _root;
		Node* prev = cur;//���ڼ�¼һ��ǰһ����㣬����ɾ��
		//ע��prev��������Ϊnullptr��������ڵ����Ҫɾ����ֵ��prev�ͻ�Կ�ָ���������
		while (cur)
		{
			if (t > cur->val)
			{
				prev = cur;
				cur = cur->right;
			}
			else if (t < cur->val)
			{
				prev = cur;
				cur = cur->left;
			}
			else
			{
				//�ҵ�֮���Ϊ�����������Ϊ0/1/2��
				//���ｫ��Ϊ0/1ͳһ����Ϊһ�������ֱ�ӽ�����Ľ�����prev��
				if (cur->right == nullptr)
				{
					if (cur == _root)//�Ը�������ɾ������ʱprev����cur����ָ������һ��
					{
						_root = cur->left;
					}
					else
					{
						if (prev->right == cur)
						{
							prev->right = cur->left;
						}
						else
						{
							prev->left = cur->left;
						}
					}
				}
				else if (cur->left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->right;
					}
					else
					{
						if (prev->right == cur)
						{
							prev->right = cur->right;
						}
						else
						{
							prev->left = cur->right;
						}
					}
				}
				else
				{
					//����������͸��Ӻܶ��ˣ�Ҫ�ҵ��������Ԫ�����Ľ������ұ�Ԫ����С�Ľڵ�
					//������д������������㣬�����滻��
					//�ؼ������������ҵ���ߵ����һ����㣬�������ұ�һ��Ϊ�գ������ܻ��б��������Ľ����
					Node* parent = cur;//���ﻹ��Ҫע�ⲻ��Ϊ�գ����cur��߾���leftmax�أ��ͻ�Կ�ָ���������
					Node* leftMax = cur->left;//������ڵ�һ�����ڣ���Ϊ����������û�н�����������Ѿ����۹���
					while (leftMax->right)
					{
						parent = leftMax;
						leftMax = leftMax->right;
					}
					swap(leftMax->val, cur->val);//��������ֵ�����滻
					//��ΪҪ��leftmax���������ɾ������ôһ��Ҫ��¼���׽��
					//����leftmax���п�����parent��ߣ�Ҳ�п�����parent�ұ�
					if (parent->left == leftMax)
					{
						parent->left = leftMax->left;
					}
					else
					{
						parent->right = leftMax->left;
					}
					cur = leftMax;
				}
				delete cur;
				return true;
			}
		}
		return false;
	}
private:
	Node* _root;
};

void testBST1()
{
	int arr[9] = { 1,3,6,7,10,4,8,13,14 };
	BinarySearchTree<int> BST;
	for (auto e : arr)
	{
		BST.Insert(e);
	}
	BST.InOrder();
	cout << "\n";

	for (auto e : arr)
	{
		BST.erase(e);
		cout << "\n";
		BST.InOrder();
	}

}