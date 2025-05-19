#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<string>
#include"BinarySearchTreeNonR.hpp"

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};
//ǰ�����+�����ӣ���
string tree2str(TreeNode* root) 
{
    if (root == nullptr)
    {
        return "";
    }
    string ret;
    ret += to_string(root->val);
    //����ұߴ������һ��Ҫ�ӣ��ұ߲�������ߴ���ҲҪ��
    if (root->right || root->left)
    {
        ret += "(";
        ret += tree2str(root->left);
        ret += ")";
    }
    //�ұߴ�����һ��Ҫ�����ŵģ������ھͲ��ü�
    if (root->right)
    {
        ret += "(";
        ret += tree2str(root->right);
        ret += ")";
    }

    return ret;
}

//Ѱ�ҹ�������
//��������������Ǿ���������ཻ����
//����Ƕ�������
//�����������������������СȥѰ��
//��ͨ�������root����p����qֱ�ӷ��أ���ȥ�ж�pq����߻����ұߣ�һ��һ��ֱ��root

//��һ�ַ�������find�ݹ�Ѱ�ң��ܲ����Ż���
bool Find(TreeNode* root, TreeNode* x)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root == x)
    {
        return true;
    }
    else
    {
        return Find(root->left, x) || Find(root->right, x);
    }
}
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr)
        {
            return nullptr;
        }

        if (root == p || root == q)
        {
            return root;
        }

        bool pinleft, pinright, qinleft, qinright;
        pinleft = Find(root->left, p);
        pinright = !pinleft;

        qinright = Find(root->right, q);
        qinleft = !qinright;

        if (pinleft && qinleft)
        {
            return lowestCommonAncestor(root->left, p, q);
        }
        else if (pinright && qinright)
        {
            return lowestCommonAncestor(root->right, p, q);
        }
        else
        {
            return root;
        }
    }


//�Ż���ʹ��ջ��Ѱ�ң���ջ��Ѱ�ҹ�������
//ջ�б�����Ѱ�ҽ���·�������ҵ��ڵ��Ѱ��ջ�ڵ�һ�γ��ֵ���ͬ��Ԫ�ؾ��ǽ��
    bool Find(TreeNode* root, TreeNode* x, stack<TreeNode*>& s)
    {
        //��ջ���洢�ҵ��Ľ��
        if (root == nullptr)
        {
            return false;
        }

        s.push(root);

        if (root == x)
        {
            return true;
        }

        if (Find(root->left, x, s))
        {
            return true;
        }
        if (Find(root->right, x, s))
        {
            return true;
        }
        //������Ҷ������ڣ�����㲻��Ҫ����
        s.pop();
        return false;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> qstack;
        stack<TreeNode*> pstack;

        Find(root, p, pstack);
        Find(root, q, qstack);

        while (pstack.size() > qstack.size())
        {
            pstack.pop();
        }
        while (pstack.size() < qstack.size())
        {
            qstack.pop();
        }

        while (pstack.top() != qstack.top())
        {
            qstack.pop(); pstack.pop();
        }

        return pstack.top();

    }

//��BSTת��Ϊ˫����������������Ļ����Ͻ��ڵ��ָ������޸�
    void InOrder(TreeNode* root, TreeNode*& prev)
    {
        if (root == nullptr)
        {
            return;
        }
        InOrder(root->left, prev);
        root->left = prev;//������ǰһ��ָ�룬���prev��Ϊ�գ�����Ϊ��Ԥ��һ��ʼprev��Ϊ�յ��龰
        if (prev)
        {
            prev->right = root;
        }
        prev = root;
        InOrder(root->right, prev);

    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        TreeNode* root = pRootOfTree;
        TreeNode* prev = nullptr;
        InOrder(root, prev);

        TreeNode* ret = root;
        while (ret && ret->left)//ret�п���Ϊ��
        {
            ret = ret->left;
        }
        return ret;

    }

//��֪������ǰ������������ݹ鹹�������
//�ȹ����㣬prei++��ָ��ľ�����ߵĵ�һ�����
    TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int& prei, int begin, int end)
    {
        if (begin > end || prei >= preorder.size())
        {
            return nullptr;
        }
        TreeNode* newnode = new TreeNode(preorder[prei]);
        int find = begin;
        while (find <= end)
        {
            if (inorder[find] == preorder[prei])
            {
                break;
            }
            find++;
        }
        //��������ڵ㣬����������������
        prei++;
        newnode->left = _buildTree(preorder, inorder, prei, begin, find - 1);
        newnode->right = _buildTree(preorder, inorder, prei, find + 1, end);
        return newnode;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        TreeNode* ret = _buildTree(preorder, inorder, i, 0, preorder.size() - 1);
        return ret;
    }

//��֪��������������������ע������˳���ǰ��һ����һ���ˣ�
//����������desi--��ôָ��ľ����ұߵĸ����
    TreeNode* _buildTree(vector<int>& inorder, vector<int>& postorder, int& desi, int begin, int end)
    {
        if (desi<0 || begin>end)
        {
            return nullptr;
        }
        int find = end;
        while (find >= begin)
        {
            if (inorder[find] == postorder[desi])
            {
                break;
            }
            find--;
        }
        TreeNode* newnode = new TreeNode(postorder[desi]);
        desi--;
        newnode->right = _buildTree(inorder, postorder, desi, find + 1, end);
        newnode->left = _buildTree(inorder, postorder, desi, begin, find - 1);
        return newnode;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int size = inorder.size() - 1;
        TreeNode* ret = _buildTree(inorder, postorder, size, 0, inorder.size() - 1);
        return ret;
    }


//ע�����Ƿǵݹ�д����ע������
//�������ķǵݹ�д����root��cur��cur��Ϊ�վ�һֱ��ջ����������ֵ���뵽vector
//���curΪ�գ���ô��ȡ��ջ��Ԫ�أ�popջ����curָ��������
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        TreeNode* cur = root;
        stack<TreeNode*> s;
        while (cur || !s.empty())
        {
            while (cur)
            {
                ret.push_back(cur->val);
                s.push(cur);
                cur = cur->left;
            }
            TreeNode* top = s.top();
            s.pop();
            cur = top->right;
        }
        return ret;
    }

//�������������ֻ��Ҫ��ǰ������Ļ����ϣ���һ����������val�������鼴��
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (cur || !s.empty())
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            TreeNode* top = s.top();
            ret.push_back(top->val);
            s.pop();
            cur = top->right;
        }

        for (auto e : ret)
        {
            cout << e << " ";
        }
        return ret;
    }

//��������ǳ��鷳��һ��Ҫ��ͼ������
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> ret;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;//���prev�ǹؼ�
        while (cur || !s.empty())
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            TreeNode* top = s.top();
            //������������ѭ�������ܹ�����д��
            if (!top->right || top->right == prev)
            {
                prev = top;//����Ҫ���������Ƿ���ʹ���һ���жϣ����prev���ҽڵ��ֵ����ô��˵���������Ѿ��������ˣ�������pushback�ý���ֵ,���������right������ʹ�һ��Ϊprev
                ret.push_back(top->val);
                s.pop();
            }
            else
            {
                cur = top->right;
            }

        }
        return ret;
    }
int main()
{
	//testBST1();
	return 0;
}