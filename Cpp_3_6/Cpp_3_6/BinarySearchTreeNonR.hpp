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



//����BST�ļ���ģ�ͣ�������������һkģ�ͣ�Ҳ������k��valueģ�ͣ���ÿ�����ֶ���Ӧ������Ӧ��Ϣ
//���ڵڶ���ģ�ͣ�����Ҫ����һ��ģ������������ֺ�������ֵ�޸�Ϊָ�����ͼ��ɣ������ڵ�����������Ҫ���ʵ�ַ
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

	bool Insert(const T& t)//����Ҫдһ���Ӻ�������Ȼû�а취�ݹ鴫��root��ֻ��ʹ�ó�Ա����_root
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
		Node* newnode = new Node(root->val);//����������ǰ����������ǲ�������insert�������������+insert��������ô���ݵ�˳��ͻᷢ���仯
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

	bool _Insert(Node*& root, const T& t)//�ǳ�������ǣ�����ָ���������,���Զ���һ��ָ������޸ģ������ڶ���ָ�룬�������ò����Ըı�ָ�򣬵��ݹ��ǲ�ͣ����ջ֡����˲���ı�ָֻ��
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
		//����Ҳ����Ҫ��¼���׽��ĵ�ַ�ˣ����÷ǳ�������໣�
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
			Node* del = root;//Ҫɾ���Ľ��ĵ�ַ����Ҫ��¼һ�µ�
			//���Ƿ�Ϊ�������������Ϊ0/1��Ϊһ��
			//1.��Ϊ��
			//2.��Ϊ��
			//3.���Ҷ���Ϊ��
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
				swap(leftMax->val, root->val);//�滻��

				return _erase(root->left, t);//ֱ��ȥ�����Ҫɾ���������
				//ע�����ﲻ������leftMax,��Ϊ���ֱ�Ӷ�leftMax�������ָ���������������ȷ�����Ƕ�ָ����ߵ�ָ��ȡ����
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
		//������Ҫ���ж������������
		//������ �� ������ �� ���ڵ㡣����˳��ȷ�����ڷ��ʵ�ǰ�ڵ�ʱ�������������Ѿ�����ȫ����
		//������ʹ������������ʽ�ˣ�
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