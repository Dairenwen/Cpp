#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<stack>
#include<queue>
#include<assert.h>
//#include"Stack.hpp"
using namespace std;
#include"Stack.hpp"//里面需要用到std，放在展开命名空间的后面
#include"Queue.hpp"
//栈与队列练习
int GetKey(int* arr, int _left, int _right)
{
	int left = _left;
	int right = _right;
	int key = _left;
	while (left<right)
	{
		while (left < right && arr[right] >= arr[key])
		{
			right--;
		}
		while (left < right && arr[left] <= arr[key])
		{
			left++;
		}
		swap(arr[left], arr[right]);
	}
	swap(arr[left], arr[key]);
	key = left;
	return key;
}

void QuickSortNonR(int* arr, int left, int right)
{
	stack<int> st;
	st.push(right);
	st.push(left);
	while (!st.empty())
	{
		int left = st.top();
		st.pop();
		int right = st.top();
		st.pop();
		int key = GetKey(arr, left, right);
		if (key + 1 < right)
		{
			st.push(right);
			st.push(key + 1);
		}
		if (left < key - 1)
		{
			st.push(key - 1);
			st.push(left);
		}
	}
}

int test()
{
	int arr[10] = { 10,9,8,7,6,5,4,3,2,1};
	QuickSortNonR(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	for (auto e : arr)
	{
		cout << e << " ";
	}
	return 0;
}


//栈与队列经典练习
//栈的括号匹配问题
typedef char STDataType;
#define start 3
#define inc 3
typedef struct Stack
{
	STDataType* a;
	int top; // 栈顶
	int capacity; // 容量
}Stack;
void StackInit(Stack* ps)
{
	assert(ps);
	STDataType* tmp = (STDataType*)malloc(sizeof(STDataType) * start);
	if (tmp == NULL)
	{
		perror("malloc failed");
		return;
	}
	ps->a = tmp;
	ps->capacity = start;
	ps->top = 0;
}
// 入栈
void StackPush(Stack* ps, STDataType data)
{
	if (ps->capacity == ps->top)
	{
		STDataType* tmp = (STDataType*)realloc(ps->a, sizeof(STDataType) * (ps->capacity + inc));
		if (tmp == NULL)
		{
			perror("realloc failed");
			return;
		}
		printf("expand successfully\n");
		ps->a = tmp;
		ps->capacity += inc;
	}
	ps->a[ps->top] = data;
	ps->top++;
}
bool StackEmpty(Stack* ps)
{
	return ps->top == 0;
}
// 出栈
void StackPop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	ps->top--;
}
// 获取栈顶元素
STDataType StackTop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	return ps->a[ps->top - 1];
}
// 获取栈中有效元素个数
int StackSize(Stack* ps)
{
	return ps->top;
}
// 检测栈是否为空，如果为空返回非零结果，如果不为空返回0 
// 销毁栈
void StackDestroy(Stack* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->top = 0;
	ps->capacity = 0;
}
bool isValid(char* s)
{
	Stack st;
	StackInit(&st);
	while (*s)
	{
		if (*s == '(' || *s == '[' || *s == '{')
		{
			StackPush(&st, *s);
		}
		else
		{
			if (StackEmpty(&st))
			{
				return false;
			}
			char top = StackTop(&st);
			StackPop(&st);
			if ((*s == ')' && top != '(') ||
				(*s == ']' && top != '[') ||
				(*s == '}' && top != '{'))
			{
				return false;
			}
		}
		s++;
	}
	bool ret = StackEmpty(&st);
	StackDestroy(&st);
	return ret;
}

//求解中缀表达式
//思路：举例1+2*3这是一般的中缀表达式，那么我们需要将其转换为后缀表达式进行运算
// 
//步骤一：中缀表达式转后缀表达式
// 
//将中缀表达式转换为后缀表达式的核心思想是使用一个栈来存储运算符，遍历中缀表达式，根据运算符的优先级和括号的匹配情况来确定运算符的输出顺序。具体规则如下：
//初始化一个空栈用于存储运算符，一个空列表用于存储后缀表达式。
//从左到右扫描中缀表达式的每个元素：
//如果是操作数，直接添加到后缀表达式列表中。
//如果是左括号，将其压入运算符栈。
//如果是右括号，将运算符栈中的元素弹出并添加到后缀表达式列表中，直到遇到左括号，然后将左括号从栈中弹出。
//如果是运算符：
//当运算符栈不为空且当前运算符的优先级小于等于栈顶运算符的优先级时，将栈顶运算符弹出并添加到后缀表达式列表中。
//将当前运算符压入运算符栈。
//扫描结束后，将运算符栈中剩余的所有运算符依次弹出并添加到后缀表达式列表中。
// 
//步骤二：计算后缀表达式的值
//计算后缀表达式的值可以使用一个栈来存储操作数，遍历后缀表达式，根据运算符进行相应的计算。具体规则如下：
//初始化一个空栈用于存储操作数。
//从左到右扫描后缀表达式的每个元素：
//如果是操作数，将其压入操作数栈。
//如果是运算符，从操作数栈中弹出两个操作数，进行相应的运算，并将结果压入操作数栈。
//扫描结束后，操作数栈中剩下的唯一元素就是表达式的值。

//leetcode计算后缀表达式的值
class Solution1 {
public:
	int evalRPN(vector<string>& tokens) {
		int count = 0;
		stack<int> st;
		while (count < tokens.size())
		{
			if (tokens[count] == "+" || tokens[count] == "-" || tokens[count] == "*" || tokens[count] == "/")
			{
				int right = st.top(); st.pop();
				int left = st.top(); st.pop();
				int tmp = 0;
				if (tokens[count] == "+")
				{
					tmp = left + right;
				}
				else if (tokens[count] == "-")
				{
					tmp = left - right;
				}
				else if (tokens[count] == "*")
				{
					tmp = left * right;
				}
				else
				{
					tmp = left / right;
				}
				st.push(tmp);
			}
			else
			{
				st.push(stoi(tokens[count]));
			}
			count++;
		}
		return st.top();
	}
};


//二叉树的层序遍历可以采用levelsize的方式记录每一层的结点个数
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
class Solution2 {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> vv;
		int levelSize = 1;
		queue<TreeNode*> q;
		if (root)
		{
			q.push(root);
		}
		while (!q.empty())
		{
			vector<int> v;
			for (size_t i = 0; i < levelSize; i++)
			{
				TreeNode* _front = q.front();
				v.push_back(_front->val);
				q.pop();
				if (_front->left)
				{
					q.push(_front->left);
				}
				if (_front->right)
				{
					q.push(_front->right);
				}
			}
			levelSize = q.size();
			vv.push_back(v);
		}
		return vv;
	}
};

int main()
{
	bit2::test_stack();
	return 0;
}