#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<stack>
#include<queue>
#include<assert.h>
//#include"Stack.hpp"
using namespace std;
#include"Stack.hpp"//������Ҫ�õ�std������չ�������ռ�ĺ���
#include"Queue.hpp"
//ջ�������ϰ
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


//ջ����о�����ϰ
//ջ������ƥ������
typedef char STDataType;
#define start 3
#define inc 3
typedef struct Stack
{
	STDataType* a;
	int top; // ջ��
	int capacity; // ����
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
// ��ջ
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
// ��ջ
void StackPop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	ps->top--;
}
// ��ȡջ��Ԫ��
STDataType StackTop(Stack* ps)
{
	assert(ps);
	assert(!StackEmpty(ps));
	return ps->a[ps->top - 1];
}
// ��ȡջ����ЧԪ�ظ���
int StackSize(Stack* ps)
{
	return ps->top;
}
// ���ջ�Ƿ�Ϊ�գ����Ϊ�շ��ط������������Ϊ�շ���0 
// ����ջ
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

//�����׺���ʽ
//˼·������1+2*3����һ�����׺���ʽ����ô������Ҫ����ת��Ϊ��׺���ʽ��������
// 
//����һ����׺���ʽת��׺���ʽ
// 
//����׺���ʽת��Ϊ��׺���ʽ�ĺ���˼����ʹ��һ��ջ���洢�������������׺���ʽ����������������ȼ������ŵ�ƥ�������ȷ������������˳�򡣾���������£�
//��ʼ��һ����ջ���ڴ洢�������һ�����б����ڴ洢��׺���ʽ��
//������ɨ����׺���ʽ��ÿ��Ԫ�أ�
//����ǲ�������ֱ����ӵ���׺���ʽ�б��С�
//����������ţ�����ѹ�������ջ��
//����������ţ��������ջ�е�Ԫ�ص�������ӵ���׺���ʽ�б��У�ֱ�����������ţ�Ȼ�������Ŵ�ջ�е�����
//������������
//�������ջ��Ϊ���ҵ�ǰ����������ȼ�С�ڵ���ջ������������ȼ�ʱ����ջ���������������ӵ���׺���ʽ�б��С�
//����ǰ�����ѹ�������ջ��
//ɨ������󣬽������ջ��ʣ���������������ε�������ӵ���׺���ʽ�б��С�
// 
//������������׺���ʽ��ֵ
//�����׺���ʽ��ֵ����ʹ��һ��ջ���洢��������������׺���ʽ�����������������Ӧ�ļ��㡣����������£�
//��ʼ��һ����ջ���ڴ洢��������
//������ɨ���׺���ʽ��ÿ��Ԫ�أ�
//����ǲ�����������ѹ�������ջ��
//�������������Ӳ�����ջ�е���������������������Ӧ�����㣬�������ѹ�������ջ��
//ɨ������󣬲�����ջ��ʣ�µ�ΨһԪ�ؾ��Ǳ��ʽ��ֵ��

//leetcode�����׺���ʽ��ֵ
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


//�������Ĳ���������Բ���levelsize�ķ�ʽ��¼ÿһ��Ľ�����
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