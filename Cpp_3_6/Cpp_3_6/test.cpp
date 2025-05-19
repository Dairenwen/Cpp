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
//前序遍历+子树加（）
string tree2str(TreeNode* root) 
{
    if (root == nullptr)
    {
        return "";
    }
    string ret;
    ret += to_string(root->val);
    //如果右边存在左边一定要加，右边不存在左边存在也要加
    if (root->right || root->left)
    {
        ret += "(";
        ret += tree2str(root->left);
        ret += ")";
    }
    //右边存在是一定要加括号的，不存在就不用加
    if (root->right)
    {
        ret += "(";
        ret += tree2str(root->right);
        ret += ")";
    }

    return ret;
}

//寻找公共祖先
//如果是三叉链表：那就是链表的相交问题
//如果是二叉链表：
//搜索二叉树：根据两个点大小去寻找
//普通树：如果root就是p或者q直接返回，再去判断pq在左边还是右边，一左一右直接root

//第一种方法依靠find递归寻找，能不能优化？
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


//优化后：使用栈来寻找，用栈来寻找公共祖先
//栈中保存了寻找结点的路径，再找到节点后寻找栈内第一次出现的相同的元素就是结点
    bool Find(TreeNode* root, TreeNode* x, stack<TreeNode*>& s)
    {
        //用栈来存储找到的结点
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
        //如果左右都不存在，这个点不需要保存
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

//将BST转换为双向链表，在中序遍历的基础上将节点的指针进行修改
    void InOrder(TreeNode* root, TreeNode*& prev)
    {
        if (root == nullptr)
        {
            return;
        }
        InOrder(root->left, prev);
        root->left = prev;//抱保存前一个指针，如果prev不为空，这是为了预防一开始prev还为空的情景
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
        while (ret && ret->left)//ret有可能为空
        {
            ret = ret->left;
        }
        return ret;

    }

//已知二叉树前序中序遍历，递归构造二叉树
//先构造结点，prei++，指向的就是左边的第一个结点
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
        //先来构造节点，再来构造左右子树
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

//已知中序后序，来构造二叉树，注意这里顺序和前面一个不一样了！
//这里后序遍历desi--那么指向的就是右边的根结点
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


//注意这是非递归写法！注意听！
//二叉树的非递归写法：root给cur，cur不为空就一直入栈左子树，将值插入到vector
//如果cur为空，那么就取出栈顶元素，pop栈顶，cur指向右子树
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

//这是中序遍历，只需要在前序遍历的基础上，晚一步进行数据val的如数组即可
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

//后序遍历非常麻烦，一定要画图分析！
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> ret;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;//这个prev是关键
        while (cur || !s.empty())
        {
            while (cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            TreeNode* top = s.top();
            //这里陷入了死循环，不能够这样写，
            if (!top->right || top->right == prev)
            {
                prev = top;//这里要对右子树是否访问过做一个判断，如果prev是右节点的值，那么就说明右子树已经被访问了，接下来pushback该结点的值,而且这里的right如果访问过一定为prev
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