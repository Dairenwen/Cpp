#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
using namespace std;


void test_set1()
{
	set<int> s;
	//setӦ��������һ��ƽ��Ķ�������������Ϊ��ͨBST���ܻ���o���
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.insert(6);
	s.insert(1);
	//��һ�ֹ�����ȥ�أ���ΪBST��������������ֵͬ����
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << "\n";
	//���д�ӡ��Ҳ�൱��һ�����������������
	set<int>::iterator sit = s.begin();
	while (sit != s.end())
	{
		cout << *sit++ << " ";
	}
	cout << "\n";

	//�����ɾ���������õ�������Ҳ������ֵ
	auto pos = s.find(3);//������set�Ķ���������Ч��ologn
	auto posc = find(s.begin(), s.end(), 3);//�������㷨���������Ч�ʵ���
	if (pos != s.end())//����ҵ����ص����������û���ҵ��ͷ���last������
	{
		s.erase(pos);
		s.erase(1);
	}
	set<int>::reverse_iterator srit = s.rbegin();
	while (srit != s.rend())
	{
		cout << *srit++ << " ";
	}
	cout << "\n";

	set<int, greater<int>> sg;//��������ηº�����Ĭ�ϰ������򣬴�greaterΪ����
	sg.insert(1);
	sg.insert(2);
	sg.insert(3);
	sg.insert(4);
	sg.insert(5);
	sg.insert(6);
	sg.insert(1);
	for (auto e : sg)
	{
		cout << e << " ";
	}
	cout << "\n";

}

void test_set2()
{
	set<int> myset;
	myset.insert(11);
	myset.insert(22);
	myset.insert(33);
	myset.insert(44);
	myset.insert(55);
	myset.insert(66);
	myset.insert(77);
	if (myset.find(77)!=myset.end())
	{
		cout << "OK" << endl;
	}
	if (myset.count(77))
	{
		cout << "ok" << endl;
	}
	cout << myset.count(11) << endl;
	cout << myset.count(22) << endl;
	cout << myset.count(33) << endl;
	cout << myset.count(44) << endl;
	cout << myset.count(55) << endl;
	cout << myset.count(66) << endl;
	cout << myset.count(77) << endl;
	//count���ڼ���

	auto find1 = myset.lower_bound(11);
	auto find2 = myset.upper_bound(22);
	cout << *find1 << endl;//lower�ҵ���>=11��ֵ
	cout << *find2 << endl;//upper�ҵ���>22��ֵ

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

}

void test_mutiset1()
{
	multiset<int> ms;
	//��ͨ��set����ȥ��+����
	//multi������������ͬ��ֵ����
	ms.insert(1);
	ms.insert(2);
	ms.insert(2);
	ms.insert(2);
	ms.insert(3);
	ms.insert(3);
	ms.insert(4);
	for (auto e : ms)
	{
		cout << e << " ";
	}

	/*auto find1 = ms.lower_bound(1);
	auto find2 = ms.upper_bound(3);
	ms.erase(find1, find2);
	for (auto e : ms)
	{
		cout << e << " ";
	}*/
	auto emm = ms.equal_range(2);//����ȵ�ֵ��first���������second�ҵ�����	
	ms.erase(emm.first, emm.second);
	for (auto e : ms)
	{
		cout << e << " ";
	}
	//�����equalrange��ʵ��Ϊmultiset��Ƶģ���Ϊset��ֵ���ǵ�һ�ģ�����ǰ���ᵽ��count
	//����set�ǲ������޸ĵģ�iterator�ĵ�������ʵ�Ǿ���const_iterator��������װ�����
	//������Ҫ����map����ʵ����key valueģ��,�������޸ĵ�
}

void test_map1()
{
	//map��python��Ҳ���ֵ䣬��ô���ʹ���أ�
	map<string, string> m;
	//����һ��map��Ҫpair��
	pair<string, string> p("insert", "���ȥ");
	m.insert(p);
	m.insert(pair<string, string>("secret", "����"));//��������
	//����Ҳ��������
	m.insert(make_pair("take_out", "�γ���"));
	//m.insert("take_away", "����");//���������𣿲�֧�ֵ���������ʽ����ת��
	m.insert({ "take_away", "����" });//������c++11��֧�ֶ����������ʽ����ת��

	//��α�����
	map<string, string>::iterator mit = m.begin();
	while (mit != m.end())
	{
		//cout << *mit << " ";//�������ԣ������õõ�pair��Ӧ�÷���pair
		cout << mit->first << " " << mit->second << "\n";
		cout << (*mit).first << " " << (*mit).second<< "\n";

		mit++;
	}
	//��map��key�ǲ������޸ĵģ�����value�ǿ����޸ĵ�

}

void test_map2()
{
	//ͳ���ظ�����
	string arr[] = { "apple","apple","banana","orange","dumpling","trump","kimi" };
	//���insertȥ�����Ѿ�����ͬ��key�ˣ���ô�Ͳ������
	//����һ��insert�ķ���ֵ������ֵΪһ��pair�����������ݵ�key�Ѿ����ڣ���ô�ͷ���pair<�Ѿ����ڵ����ݵ�iterator��false>
	//���򷵻�pair<����ɹ���ַ��true>,
	//operator[]�ײ�ͨ��pair<iterator,bool> ret=insert make_pair(key,T()),ʵ�֣�T()��������
	//return ret.first->second������������value������
	map<string, int> m;
	/*for (const auto& e:arr)
	{
		auto find = m.find(e);
		if (find == m.end())
		{
			m.insert(make_pair(e, 1));
		}
		else
		{
			find->second++;
		}
	}*/
	for (const auto& e : arr)
	{
		m[e]++;//��������ھͲ���++��������ھ�++
	}
	for (const auto& e : m)
	{
		cout << e.first << " " << e.second << "\n";
	}
}

void test_map3()
{
	map<string, int> m;
	m.insert(make_pair("string", 1));
	m["string"] = 2;
	m["openCV"];
	//multimap��֧��[]operator��֧�ֶ����ͬ��value
	//map��set�ǻ��ں����ʵ�ֵ�,ologn
	//��unordered_map��unordered_set�ǻ��ڹ�ϣ��ʵ�ֵģ��������o1
}
//����һ�£�list��map��set������ֱ��ʹ�ÿ��е�sort��������������Ϊ�ײ��ǿ��ţ��漰������ȡ��
//�����ǵĵ���������Ϊ˫���������֧������������Ĺ���
class Solution {
	struct Greater
	{
	public:
		bool operator()(const pair<string, int>& p1, const pair<string, int>& p2)
		{
			return (p1.second > p2.second || (p1.second == p2.second && p1.first < p2.first));
		}
	};
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> m;
		vector<string> ret;
		for (const auto& e : words)
		{
			m[e]++;
		}
		//��������ͳ�ƴ�����������pairȥ����vector�������漰pair�ıȽϷ�ʽ
		vector<pair<string, int>> v(m.begin(), m.end());
		//stable_sort(v.begin(),v.end(),Greater());//������sortʹ�ÿ��Ų��ȶ�����ôӦ��ʹ��stable_sort
		sort(v.begin(), v.end(), Greater());
		for (size_t i = 0; i < k; i++)
		{
			ret.push_back(v[i].first);
		}

		return ret;
	}
};
//pair��ʵ�ǿ��ԱȽϵģ����Ȱ���key��ֵ��Ƚϣ����key��ͬ����ȥ�Ƚ�value����ͬ����kv����ͬ
//���򲹳䣺������Ҫ�ȶ�����,stable_sort������Ĳ���ѡ��
//int main()
//{
//	//test_set1();
//	//test_set2();
//	//test_mutiset1();
//	//test_map3();
//	//Solution s;
//	//s.topKFrequent(["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"],4)
//	return 0;
//}