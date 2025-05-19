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



//关于BST的几种模型，可以来搜索单一k模型，也可以是k，value模型，即每个数字都对应的有相应信息
//对于第二种模型，则需要增加一个模板参数，将部分函数返回值修改为指针类型即可，类似于迭代器，可能要访问地址
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

	~BinaryTreeNode()
	{
		left = nullptr;
		right = nullptr;
		val = 0;
	}
};

template<class T>
class BinarySearchTree
{
public:
	typedef BinaryTreeNode<T> Node;

	BinarySearchTree()
		:_root(nullptr)
	{}

	BinarySearchTree(const BinarySearchTree<T>& BST)
	{
		_root=Copy(BST._root);
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

	bool Insert(const T& t)//必须要写一个子函数，不然没有办法递归传参root，只能使用成员变量_root
	{
		return _Insert(_root, t);
	}

	bool find(const T& t)
	{
		return _find(_root,t);
	}

	bool erase(const T& t)
	{
		return _erase(_root, t);
	}

	BinarySearchTree<T>& operator=(BinarySearchTree<T> BST)
	{
		swap(_root, BST._root);
		return *this;
	}

	~BinarySearchTree()
	{
		Destroy(_root);
	}
private:
	Node* Copy(const Node* root)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		Node* newnode = new Node(root->val);//这里类似于前序遍历，但是不可以用insert函数，中序遍历+insert函数，那么数据的顺序就会发生变化
		newnode->left = Copy(root->left);
		newnode->right = Copy(root->right);
		return newnode;
	}

	bool _find(Node*& root,const T& t)
	{
		if (root == nullptr)
		{
			return false;
		}
		if (t < root->val)
		{
			return _find(root->left, t);
		}
		else if (t > root->val)
		{
			return _find(root->right, t);
		}
		else
		{
			return true;
		}
	}

	bool _Insert(Node*& root, const T& t)//非常巧妙的是，这里指针加了引用,可以对上一个指针进行修改，类似于二级指针，由于引用不可以改变指向，但递归是不停创建栈帧，因此不会改变只指向
	{
		if (root == nullptr)
		{
			Node* newnode = new Node(t);
			root = newnode;
			return true;
		}
		if (t > root->val)
		{
			return _Insert(root->right, t);
		}
		else if (t < root->val)
		{
			return _Insert(root->left, t);
		}
		else
		{
			return false;
		}
	}

	bool _erase(Node*& root, const T& t)
	{
		if (root == nullptr)
		{
			return false;
		}
		//这里也不需要记录父亲结点的地址了，引用非常的巧妙嗷！
		if (t > root->val)
		{
			return _erase(root->right, t);
		}
		else if (t < root->val)
		{
			return _erase(root->left, t);
		}
		else
		{
			Node* del = root;//要删除的结点的地址还是要记录一下的
			//还是分为三种情况，将度为0/1归为一种
			//1.左为空
			//2.右为空
			//3.左右都不为空
			if (root->left == nullptr)
			{
				root = root->right;
			}
			else if (root->right == nullptr)
			{
				root = root->left;
			}
			else
			{
				Node* leftMax = root->left;
				while (leftMax->right)
				{
					leftMax = leftMax->right;
				}
				swap(leftMax->val, root->val);//替换法

				return _erase(root->left, t);//直接去左边找要删除的这个数
				//注意这里不可以找leftMax,因为如果直接对leftMax这个结点的指针区别名会出错，正确做法是对指向左边的指针取别名
			}
			delete del;
			return true;
		}
	}

	void Destroy(Node*& root)
	{
		if (root == nullptr)
		{
			return;
		}
		//析构就要进行二叉树后序遍历
		//左子树 → 右子树 → 根节点。这种顺序确保了在访问当前节点时，其左右子树已经被完全处理。
		//不可以使用其他遍历方式了！
		Destroy(root->left);
		Destroy(root->right);
		erase(root->val);
	}
	Node* _root;
};

void testBST1()
{
	int arr[9] = { 1,3,6,7,10,4,8,13,14 };
	BinarySearchTree<int> BST;
	BinarySearchTree<int> BSTcopy;

	for (auto e : arr)
	{
		BST.Insert(e);
	}
	BST.InOrder();
	cout << "\n";

	BSTcopy = BST;
	BSTcopy.InOrder();
	cout << "\n";

	for (auto e : arr)
	{
		BST.erase(e);
		cout << "\n";
		BST.InOrder();
	}

	BinarySearchTree<int> BSTccopy(BSTcopy);
	BSTccopy.InOrder();
}