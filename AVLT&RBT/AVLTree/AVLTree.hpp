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
//其中，Node里面比起BST多了parent和bf，其中要有parent的原因是要不断沿着parent
//去调整bf平衡因子
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
		//建议还是采用非递归的写法，不要使用递归或者指针引用，一方面是防止栈溢出
		//stack overflow warning!一方面是锻炼代码能力
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
		//插入完成后要调整父亲的平衡因子
		//要满足以下规则：
		//1.新增在左，parent平衡因子--
		//2.新增在右，parent平衡因子++
		//3.更新后parent平衡因子==0，说明parent所在的子树高度不变，不会再影响祖先，不用再继续沿着到root的路径往上更新
		//4.更新后parent平衡因子==1/-1，说明parent所在的子树的高度变化，会影响祖先，需要继续沿着到root的路径更新
		//5.更新后parent平衡因子==2/-2，说明parent所在的子树高度变化并且不平衡，对parent所在子树进行旋转调整
		//6.如果更新到根节点，插入结束
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
				//更新结束
				break;
			}
			else if (prev->_bf == 1 || prev->_bf == -1)
			{
				//继续向上更新
				newnode = prev;
				prev = prev->_parent;
			}
			else if (prev->_bf == 2 || prev->_bf == -2)
			{
				//不平衡的AVL，需要旋转
				//旋转需要注意的问题：
				//1.旋转的同时还要满足是搜索树
				//2.变成平衡树且降低这个子树的高度
				//3.变成平衡树后就无需向上更新了，旋转后根节点的平衡因子为0
				//旋转调整分为四种情况：
				//1.左单旋
				//2.右单旋
				//3.左右双旋
				//4.右左双旋
				//如果是左单旋，需要判断插入的节点是否位于右子树的右子树
				//如果位于右子树的左子树，需要先对右子树进行右单旋，再对根节点进行左单旋，也就是右左双旋
				//如果是右单旋，需要判断插入的节点是否位于左子树的左子树
				//如果位于左子树的右子树，需要先对左子树进行左单旋，再对根节点进行右单旋，也就是左右双旋
				//代码：
				if (prev->_bf == 2 && newnode->_bf == 1)
				{
					//说明插入的节点在右子树的右子树
					//进行左单旋
					RotateL(prev);
				}
				else if (prev->_bf == -2 && newnode->_bf == -1)
				{
					//说明插入的节点在左子树的左子树
					//进行右单旋
					RotateR(prev);
				}
				else if (prev->_bf == 2 && newnode->_bf == -1)
				{
					//说明插入的节点在右子树的左子树
					//进行右左双旋
					RotateRL(prev);
				}
				else
				{
					//最后一种情况，说明插入的节点在左子树的右子树
					//进行左右双旋转；
					RotateLR(prev);
				}
				//注意这里旋转完成后，平衡因子满足-1/0/1，不需要再向上更新
				break;
			}
			else
			{
				assert(false);//用来调试的，如果出现这种情况，说明代码有问题
				//插入之前AVL就出现了问题
			}
		}
		return true;
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
		cur->_bf=0;
		parent->_bf=0;
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
		cur->_bf=0;
		parent->_bf=0;
		//其实这里cur和parent的_bf一定为0了
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		//这里要更新平衡因子，分为三种情况
		//1.插入在左子树的右子树第一个，此前没有右子树
		//2.插入在左子树的右子树的右子树
		//3.插入在左子树的右子树的左子树
		Node* cur = parent->_left;
		Node* curright = cur->_right;
		int _bf = curright->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (_bf == 0)
		{
			
			//最后curright，cur，parent的平衡因子都为0
			cur->_bf = 0;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (_bf == 1)
		{
			
			//说明插入在左子树的右子树的右子树
			cur->_bf = -1;
			parent->_bf = 0;
			curright->_bf = 0;
		}
		else if (_bf == -1)
		{
			
			//说明插入在左子树的右子树的左子树
			cur->_bf = 0;
			parent->_bf = 1;
			curright->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	//右左双旋
	void RotateRL(Node* parent)
	{
		//这里要更新平衡因子，分为三种情况
		//1.插入在右子树的左子树第一个，此前没有左子树
		//2.插入在右子树的左子树的左子树
		//3.插入在右子树的左子树的右子树
		Node* cur = parent->_right;
		Node* curleft = cur->_left;
		int _bf = curleft->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (_bf == 0)
		{
			
			//最后curleft，cur，parent的平衡因子都为0
			cur->_bf = 0;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else if (_bf == 1)
		{
			//说明插入在右子树的左子树的右子树
			cur->_bf = 0;
			parent->_bf = -1;
			curleft->_bf = 0;
		}
		else if (_bf == -1)
		{
			//说明插入在右子树的左子树的左子树
			cur->_bf = 1;
			parent->_bf = 0;
			curleft->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	//AVL树的删除非常复杂，因为删除后要保持平衡，所以要分情况讨论
	//1.按照搜索的规则找到要删除的节点
	//2.更新平衡因子，不管平衡因子是多少，都要向上更新
	//3.出现异常情况，需要旋转调整
	void InOrder()
	{
		_InOrder(_root);
	}

	//为了方便测试AVL是否平衡，写一个判断函数
	bool IsBalance()
	{
		//这里可不能直接判断平衡因子，因为平衡因子有可能出错
		//选择计算两边的高度差，如果高度差小于2，说明平衡
		//但是这只能说明当前节点的平衡，不能说明整棵树的平衡
		//所以要递归判断
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