#include<assert.h>
#include<iostream>
#include<vector>
#include<algorithm>//�㷨�� ����sort find reverse
#include<string>
#include"vector.hpp"
using namespace std;

void test_vector1()
{
	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	for (auto tmp : v1)
	{
		cout << tmp;
	}
	for (size_t i = 0; i < v1.size(); i++)
	{
		cout << v1[i];
	}
	vector<int>::iterator it = v1.begin();
	while(it != v1.end())
	{
		cout << *it;
		it++;
	}
}
void test_vector2()
{
	vector<string> v1;//������ʽʵ����ѡ��string��
	v1.push_back("666");//��ʽ����ת��
	v1.push_back(string("666"));//��������
}
void test_vector3()
{
	vector<int> v1(10, 1);//10��1
	vector<int> v2(v1.begin() + 4, v1.end());//�����õ�������ʼ��
	for (auto tmp : v1)
	{
		cout << tmp;
	}
	for (auto tmp : v2)
	{
		cout << tmp;
	}
	string str("hello world");
	vector<char> v4(str.begin(), str.end());
	for (auto e : v4)
	{
		cout << e << " ";
	}
	cout << endl;

	int a[] = { 16,2,77,29 };
	vector<int> v5(a, a + 4);
	for (auto e : v5)
	{
		cout << e << " ";
	}
	cout << endl;
	//�������һ���㷨sort,<��less >��greater
	less<int> ls;
	sort(v5.begin(), v5.end(), ls);
	for (auto e : v5)
	{
		cout << e << " ";
	}
	//����
	sort(v5.begin(), v5.end(), less<int>());//����lessʡ��Ҳ���� Ĭ������
	//����Ҳ���Բ���>���������������е�����´�rbegin��rend����ĩβ������������
	greater<int> gt;
	sort(v5.begin(), v5.end(), greater<int>());
	for (auto e : v5)
	{
		cout << e << " ";
	}
}
void test_vector4()
{
	vector<int> v1;
	/*v1.reserve(10);
	for (size_t i = 0; i < 10; i++)
	{
		v1[i] = i;
    }*///������10���ռ䣬����sizeΪ0����[]����ʱ����pos<size����Ӧ����resize�ȳ�ʼ��
	v1.resize(10, 1);
	for (size_t i = 0; i < 10; i++)
	{
		v1[i] = i;
	}
	for (auto e : v1)
	{
		cout << e << " ";
	}

}
void test_vector5()
{
	int a[] = { 16,2,77,29,3,33,43,3,2,3,3,2 };
	vector<int> v1(a, a + sizeof(a) / sizeof(int));//ָ�룬Ҳ������ԭʼ�ĵ�����
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// ͷɾ
	v1.erase(v1.begin());//���ﲻ�Ǵ�λ�ã����ǵ�����
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// ͷ�� 
	v1.insert(v1.begin(), 100);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// ɾ����3������
	v1.erase(v1.begin() + 2);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	// ɾ��3�����ǲ�֪��3���ĸ�λ�ã���ô�죿
	vector<int>::iterator pos = find(v1.begin(), v1.end(), 3);//find�����㷨�⣬���γ�ʼĩβ�������Լ�Ҫ���ҵ�����
	//find����ҵ����ص�һ�γ��ֵ�λ�õ�����������Ҳ����������һ��Ԫ����һ��λ�õ�����
	//auto pos = find(v1.begin(), v1.end(), 3);
	/*if (pos != v1.end())
	{
		v1.erase(pos);
	}*/

	// ɾ�����е�3 -- �漰������ʧЧ��������
	while (pos != v1.end())
	{
		v1.erase(pos);
		//pos = find(pos+1, v1.end(), 3);//ɾ��������pos�Ͳ�������
		pos = find(v1.begin(), v1.end(), 3);
	}
	//���䣺������ʧЧ��~
	//- ����ʽ����ɾ��Ԫ�أ��ڴ����������������ʧЧ��
	//- ����ʽ��������Ԫ�أ���vector��deque��������ʽ��������set��map�������������ط����ڴ棬���е�����ʧЧ��
	//- ����resize / clear���ı��С����գ�������ʧЧ��
	//- �ƶ� / ��ֵ������ԭ�������ݸı䣬����������ָ����ЧԪ�ء�
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	v1.assign(10, 1);//����������ݣ�����10��1��������
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}


int main()
{
	string s1("hello world");
	bit::vector<string> v1;
	bit::vector<string> v2;
	v1.push_back(s1);
	v2 = v1;
	/*bit::test_vector1();
	bit::test_vector2();
	bit::test_vector3();
	bit::test_vector4();
	bit::test_vector5();
	bit::test_vector6();*/
	test_vector3();
	//vector<int> v(10, 1);
	//int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	//bit::vector<int> v3(a, a + 10);
	//cout << v3.size();
	return 0;
}