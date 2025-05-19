#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
//搜索二叉树：
//1.左子树的所有值都小于当前结点
//2.右子树的所有制都大于当前结点
//3.左右子树都是搜索二叉树，也叫二叉排序树
//理想查找次数是logn，但最坏的情况是n

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
		//这里要对根结点为空特殊处理一下
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
		//第一步先来找到含有t的结点
		Node* cur = _root;
		Node* prev = cur;//用于记录一下前一个结点，用于删除
		//注意prev不能设置为nullptr，如果根节点就是要删除的值，prev就会对空指针解引用了
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
				//找到之后分为三种情况，度为0/1/2，
				//这里将度为0/1统一处理为一种情况，直接将后面的结点接在prev上
				if (cur->right == nullptr)
				{
					if (cur == _root)//对根结点进行删除，此时prev就是cur，不指向任意一边
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
					//第三种情况就复杂很多了，要找到左边所有元素最大的结点或者右边元素最小的节点
					//这里书写左子树找最大结点，进行替换法
					//关键点在于这里找到左边的最大一个结点，这个结点右边一定为空，不可能还有比这个还大的结点了
					Node* parent = cur;//这里还是要注意不能为空，如果cur左边就是leftmax呢？就会对空指针解引用了
					Node* leftMax = cur->left;//这里左节点一定存在！因为单个结点或者没有结点的情况上面已经讨论过了
					while (leftMax->right)
					{
						parent = leftMax;
						leftMax = leftMax->right;
					}
					swap(leftMax->val, cur->val);//交换两个值进行替换
					//因为要对leftmax这个结点进行删除，那么一定要记录父亲结点
					//这里leftmax就有可能在parent左边，也有可能在parent右边
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