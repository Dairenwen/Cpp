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
	//set应该类似于一种平衡的二叉搜索树，因为普通BST可能会有o深度
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);
	s.insert(5);
	s.insert(6);
	s.insert(1);
	//有一种功能是去重，因为BST不允许有两个相同值存在
	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << "\n";
	//进行打印，也相当于一种中序遍历，即排序
	set<int>::iterator sit = s.begin();
	while (sit != s.end())
	{
		cout << *sit++ << " ";
	}
	cout << "\n";

	//如果是删除，可以用迭代器，也可以是值
	auto pos = s.find(3);//这里是set的二叉搜索，效率ologn
	auto posc = find(s.begin(), s.end(), 3);//这里是算法库的搜索，效率低下
	if (pos != s.end())//如果找到返回迭代器，如果没有找到就返回last迭代器
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

	set<int, greater<int>> sg;//如果不传参仿函数，默认按照升序，传greater为降序
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
	//count用于计数

	auto find1 = myset.lower_bound(11);
	auto find2 = myset.upper_bound(22);
	cout << *find1 << endl;//lower找的是>=11的值
	cout << *find2 << endl;//upper找的是>22的值

	std::pair<std::set<int>::const_iterator, std::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

}

void test_mutiset1()
{
	multiset<int> ms;
	//普通的set可以去重+排序
	//multi可以允许多个相同的值存在
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
	auto emm = ms.equal_range(2);//找相等的值，first左迭代器，second右迭代器	
	ms.erase(emm.first, emm.second);
	for (auto e : ms)
	{
		cout << e << " ";
	}
	//这里的equalrange其实是为multiset设计的，因为set中值都是单一的，包括前面提到的count
	//而且set是不允许修改的，iterator的迭代器其实是经过const_iterator迭代器包装过后的
	//而下面要讲的map中其实就是key value模型,是允许修改的
}

void test_map1()
{
	//map在python中也叫字典，那么如何使用呢？
	map<string, string> m;
	//构造一个map需要pair，
	pair<string, string> p("insert", "插进去");
	m.insert(p);
	m.insert(pair<string, string>("secret", "秘密"));//匿名对象
	//或者也可以这样
	m.insert(make_pair("take_out", "拔出来"));
	//m.insert("take_away", "拿走");//这样可以吗？不支持单参数的隐式类型转换
	m.insert({ "take_away", "拿走" });//这样是c++11，支持多个参数的隐式类型转换

	//如何遍历？
	map<string, string>::iterator mit = m.begin();
	while (mit != m.end())
	{
		//cout << *mit << " ";//这样可以？解引用得到pair，应该访问pair
		cout << mit->first << " " << mit->second << "\n";
		cout << (*mit).first << " " << (*mit).second<< "\n";

		mit++;
	}
	//在map中key是不可以修改的，但是value是可以修改的

}

void test_map2()
{
	//统计重复次数
	string arr[] = { "apple","apple","banana","orange","dumpling","trump","kimi" };
	//如果insert去查找已经有相同的key了，那么就不会插入
	//介绍一下insert的返回值，返回值为一个pair，如果这个数据的key已经存在，那么就返回pair<已经存在的数据的iterator，false>
	//否则返回pair<插入成功地址，true>,
	//operator[]底层通过pair<iterator,bool> ret=insert make_pair(key,T()),实现，T()匿名对象，
	//return ret.first->second的引用来返回value的引用
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
		m[e]++;//如果不存在就插入++，如果存在就++
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
	//multimap不支持[]operator，支持多个相同的value
	//map和set是基于红黑树实现的,ologn
	//而unordered_map和unordered_set是基于哈希表实现的，理想情况o1
}
//补充一下：list，map，set都不能直接使用库中的sort函数进行排序，因为底层是快排，涉及到三数取中
//而他们的迭代器类型为双向迭代器不支持随机迭代器的功能
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
		//先来遍历统计次数，再来用pair去插入vector，这里涉及pair的比较方式
		vector<pair<string, int>> v(m.begin(), m.end());
		//stable_sort(v.begin(),v.end(),Greater());//单纯的sort使用快排不稳定，那么应该使用stable_sort
		sort(v.begin(), v.end(), Greater());
		for (size_t i = 0; i < k; i++)
		{
			ret.push_back(v[i].first);
		}

		return ret;
	}
};
//pair其实是可以比较的，首先按照key的值相比较，如果key相同，再去比较value，相同必须kv都相同
//排序补充：如果真的要稳定排序,stable_sort将是你的不二选择
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