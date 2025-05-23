#include<iostream>
#include<set>
#include<map>
#include<list>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	pair<K, V> _kv;
	int _bf;

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{
	}
};
//���У�Node�������BST����parent��bf������Ҫ��parent��ԭ����Ҫ��������parent
//ȥ����bfƽ������
template<class K, class V>
class AVLTree
{
public:
	typedef AVLTreeNode<K, V> Node;
	AVLTree()
		:_root(nullptr)
	{
	}

	bool Insert(const pair<K, V>& kv)
	{
		//���黹�ǲ��÷ǵݹ��д������Ҫʹ�õݹ����ָ�����ã�һ�����Ƿ�ֹջ���
		//stack overflow warning!һ�����Ƕ�����������
		Node* cur = _root;
		Node* prev = nullptr;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		Node* newnode = new Node(kv);
		if (_root == nullptr)
		{
			_root = newnode;
			return true;
		}
		if (kv.first > prev->_kv.first)
		{
			prev->_right = newnode;
		}
		else
		{
			prev->_left = newnode;
		}
		newnode->_parent = prev;
		//������ɺ�Ҫ�������׵�ƽ������
		//Ҫ�������¹���
		//1.��������parentƽ������--
		//2.�������ң�parentƽ������++
		//3.���º�parentƽ������==0��˵��parent���ڵ������߶Ȳ��䣬������Ӱ�����ȣ������ټ������ŵ�root��·�����ϸ���
		//4.���º�parentƽ������==1/-1��˵��parent���ڵ������ĸ߶ȱ仯����Ӱ�����ȣ���Ҫ�������ŵ�root��·������
		//5.���º�parentƽ������==2/-2��˵��parent���ڵ������߶ȱ仯���Ҳ�ƽ�⣬��parent��������������ת����
		//6.������µ����ڵ㣬�������
		while (prev)
		{
			if (prev->_left == newnode)
			{
				prev->_bf--;
			}
			else
			{
				prev->_bf++;
			}

			if (prev->_bf == 0)
			{
				//���½���
				break;
			}
			else if (prev->_bf == 1 || prev->_bf == -1)
			{
				//�������ϸ���
				newnode = prev;
				prev = prev->_parent;
			}
			else if (prev->_bf == 2 || prev->_bf == -2)
			{
				//��ƽ���AVL����Ҫ��ת
				//��ת��Ҫע������⣺
				//1.��ת��ͬʱ��Ҫ������������
				//2.���ƽ�����ҽ�����������ĸ߶�
				//3.���ƽ��������������ϸ����ˣ���ת����ڵ��ƽ������Ϊ0
				//��ת������Ϊ���������
				//1.����
				//2.�ҵ���
				//3.����˫��
				//4.����˫��
				//�������������Ҫ�жϲ���Ľڵ��Ƿ�λ����������������
				//���λ��������������������Ҫ�ȶ������������ҵ������ٶԸ��ڵ����������Ҳ��������˫��
				//������ҵ�������Ҫ�жϲ���Ľڵ��Ƿ�λ����������������
				//���λ��������������������Ҫ�ȶ������������������ٶԸ��ڵ�����ҵ�����Ҳ��������˫��
				//���룺
				if (prev->_bf == 2 && newnode->_bf == 1)
				{
					//˵������Ľڵ�����������������
					//��������
					RotateL(prev);
				}
				else if (prev->_bf == -2 && newnode->_bf == -1)
				{
					//˵������Ľڵ�����������������
					//�����ҵ���
					RotateR(prev);
				}
				else if (prev->_bf == 2 && newnode->_bf == -1)
				{
					//˵������Ľڵ�����������������
					//��������˫��
					RotateRL(prev);
				}
				else
				{
					//���һ�������˵������Ľڵ�����������������
					//��������˫��ת��
					RotateLR(prev);
				}
				//ע��������ת��ɺ�ƽ����������-1/0/1������Ҫ�����ϸ���
				break;
			}
			else
			{
				assert(false);//�������Եģ�����������������˵������������
				//����֮ǰAVL�ͳ���������
			}
		}
		return true;
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
		cur->_bf=0;
		parent->_bf=0;
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
		cur->_bf=0;
		parent->_bf=0;
		//��ʵ����cur��parent��_bfһ��Ϊ0��
	}

	//����˫��
	void RotateLR(Node* parent)
	{
		//����Ҫ����ƽ�����ӣ���Ϊ�������
		//1.����������������������һ������ǰû��������
		//2.����������������������������
		//3.����������������������������
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		int _bf = curright->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (_bf == 0)
		{
			
			//���curright��cur��parent��ƽ�����Ӷ�Ϊ0
			cur->_bf = 0;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (_bf == 1)
		{
			
			//˵������������������������������
			cur->_bf = -1;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (_bf == -1)
		{
			
			//˵������������������������������
			cur->_bf = 0;
			parent->_bf = 1;
			curright->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	//����˫��
	void RotateRL(Node* parent)
	{
		//����Ҫ����ƽ�����ӣ���Ϊ�������
		//1.����������������������һ������ǰû��������
		//2.����������������������������
		//3.����������������������������
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		int _bf = curleft->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (_bf == 0)
		{
			
			//���curleft��cur��parent��ƽ�����Ӷ�Ϊ0
			cur->_bf = 0;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else if (_bf == 1)
		{
			//˵������������������������������
			cur->_bf = 0;
			parent->_bf = -1;
			curleft->_bf = 0;
		}
		else if (_bf == -1)
		{
			//˵������������������������������
			cur->_bf = 1;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	//AVL����ɾ���ǳ����ӣ���Ϊɾ����Ҫ����ƽ�⣬����Ҫ���������
	//1.���������Ĺ����ҵ�Ҫɾ���Ľڵ�
	//2.����ƽ�����ӣ�����ƽ�������Ƕ��٣���Ҫ���ϸ���
	//3.�����쳣�������Ҫ��ת����
	void InOrder()
	{
		_InOrder(_root);
	}

	//Ϊ�˷������AVL�Ƿ�ƽ�⣬дһ���жϺ���
	bool IsBalance()
	{
		//����ɲ���ֱ���ж�ƽ�����ӣ���Ϊƽ�������п��ܳ���
		//ѡ��������ߵĸ߶Ȳ����߶Ȳ�С��2��˵��ƽ��
		//������ֻ��˵����ǰ�ڵ��ƽ�⣬����˵����������ƽ��
		//����Ҫ�ݹ��ж�
		return _IsBalance(_root);
	}

	int Height()
	{
		return _Height(_root);
	}
private:
	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
		{
			return true;
		}
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (root->_bf != rightHeight - leftHeight)
		{
			return false;
		}
		return abs(rightHeight - leftHeight) < 2 &&_IsBalance(root->_left) && _IsBalance(root->_right);
	}

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

	/*void RotateLm(Node* parent)
	{
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		Node* ppnode = parent->_parent;
		cur->_left = parent;
		parent->_right = curleft;
		parent->_parent = cur;
		if (curleft)
		{
			curleft->_parent = parent;
		}
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
		cur->_parent = ppnode;
		cur->_bf = 0; parent->_bf = 0;
	}

	void RotateRm(Node* parent)
	{
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_left = curright;
		parent->_parent = cur;
		if (curright)
		{
			curright->_parent = parent;
		}
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
		cur->_parent = ppnode;
		cur->_bf = 0; parent->_bf = 0;
	}*/
	Node* _root;
};