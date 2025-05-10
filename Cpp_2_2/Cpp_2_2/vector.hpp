#include<iostream>
#include<string.h>
#include<vector>
#include<assert.h>
#include<algorithm>
using namespace std;

namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
		}

		//�������캯��
		vector(const vector<T>& t)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			_start = new T[t.capacity()];
			for (size_t i = 0; i < t.size(); i++)
			{
				*(_start + i) = t[i];
			}
			_finish = _start + t.size();
			_end_of_storage = _start + t.capacity();
		}

		vector(int n, const T& t)//����size_t,�����ֱ��ƥ����������캯��
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			resize(n, t);
		}

		template<class Inputiterator>
		vector(Inputiterator begin, Inputiterator end)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (begin != end)
			{
				push_back(*begin++);
			}
		}

		vector<T>& operator=(vector<T> t)
		{
			swap(_start,t._start);
			swap(_finish, t._finish);
			swap(_end_of_storage, t._end_of_storage);
			return *this;
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin()const
		{
			return _start;
		}

		const_iterator end()const
		{
			return _finish;
		}

		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		size_t capacity()const//const�ܴ��ʹ���Ȼ�����
		{
			return _end_of_storage - _start;
		}
		
		size_t size()const//const���ε�vector����const���κ���
		{
			return _finish - _start;
		}

		T& operator[](size_t pos)
		{
			assert(_start + pos < _finish);
			return *(_start + pos);
		}

		const T& operator[](size_t pos)const
		{
			assert(_start + pos < _finish);
			return *(_start + pos);
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				iterator newstart = new T[n];
				//memcpy(newstart, _start, sizeof(T) * size());
				//����memcpy��������ǳ������Ϊ�˷�ֹ�Զ�������ǳ���������ø�ֵ��ʽ���������Ե��ø�ֵ����
				size_t sz = size();
				if (_start)
				{
					for (size_t i = 0; i < size(); i++)
					{
						*(newstart + i) = *(_start + i);
					}
					delete[] _start;
				}
				_start = newstart;
				_finish = _start + sz;
				_end_of_storage = _start + n;
			}
		}

		void push_back(const T& t)
		{
			if (_finish == _end_of_storage)
			{
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish++ = t;
		}

		void pop_back()
		{
			_finish--;
		}

		iterator insert(iterator pos, const T& t)
		{
			assert(_start <= pos && pos < _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
				pos = _start + len;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = t;
			_finish++;
			return pos;
		}
		//�������Ҫ���ݣ�posָ��ĵ�ַ���ͷſռ���ʧЧ�ˣ�����Ҫ�ȼ�¼λ��
		//Ϊ�˷�ֹ�ⲿ������ʧЧ������һ��������ָ������ⲿ�ĵ�����

		iterator erase(iterator pos)
		{
			assert(_start <= pos && pos < _finish);
			iterator it = pos + 1;
			while (it != _finish)
			{
				*(it - 1) = *it;
				it++;
			}
			_finish--;
			return pos;
		}
		//ɾ��Ҳ�е�����ʧЧ�����⣬����erase֮��Ͳ����ٶԵ��������з�����
		//vs��ֱ��ͨ�����Ծܾ�����g++��ĳЩ�����ܹ������ﷵ��ɾ������һ��λ�õĵ�����

		void resize(size_t n, const T& t = T())
		{
			if (n <= size())
			{
				_finish = _start + n;
			}
			else
			{
				reserve(n);
				while (_finish != _start + n)
				{
					*_finish++ = t;
				}
			}
		}
		//���������Ա��κ����Ͷ����Ե��ÿ�������
		//������������Ҳ���˴���Ĭ���п������캯������intĬ��Ϊ0

	private:
		iterator _start;
		iterator _finish;//ָ�����һ��Ԫ����һ��λ��
		iterator _end_of_storage;
	};

	template<class T>
	void print(const T& v)
	{
		for (auto tmp : v)
		{
			cout << tmp;
		}
	}

	void test_vector1()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		for (size_t i = 0; i < v1.size(); i++)
		{
			v1[i]++;
		}

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		print(v1);
	}

	void test_vector2()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(5);
		v1.push_back(5);
		v1.push_back(5);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		v1.insert(v1.begin(), 100);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		/*vector<int>::iterator p = v1.begin() + 3;
		v1.insert(p, 300);*/

		vector<int>::iterator p = v1.begin() + 3;
		//v1.insert(p+3, 300);

		// insert�Ժ���������ܻ�ʧЧ(����)
		// ��ס��insert�Ժ�Ͳ�Ҫʹ������βε������ˣ���Ϊ������ʧЧ��
		v1.insert(p, 300);

		// ��Σ��Ϊ
		// *p += 10;

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector3()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.push_back(6);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		auto it = v1.begin();
		while (it != v1.end())
		{
			if (*it % 2 == 0)
			{
				it = v1.erase(it);
			}
			else
			{
				++it;
			}
		}

		//v1.erase(v1.begin());
		//auto it = v1.begin()+4;
		//v1.erase(it);

		//// erase�Ժ󣬵�����ʧЧ�ˣ����ܷ���
		//// vs����ǿ�Ƽ�飬���ʻ�ֱ�ӱ���
		//cout << *it << endl;
		//++it;
		//cout << *it << endl;

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector4()
	{
		vector<int> v;
		v.resize(10, 0);

		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;


		int i = 0;
		int j = int();
		int k = int(1);
	}

	void test_vector5()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		vector<int> v1(v);

		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;

		vector<int> v2;
		v2.resize(10, 1);

		v1 = v2;
		for (auto e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector6()
	{
		vector<string> v;
		v.push_back("111111111111111111");
		v.push_back("222222222222222222");
		v.push_back("333333333333333333");
		v.push_back("444444444444444444");
		v.push_back("555555555555555555");

		for (auto& e : v)
		{
			cout << e << " ";
		}
		cout << endl;

		vector<string> v1(v);
		for (auto& e : v1)
		{
			cout << e << " ";
		}
		cout << endl;
	}

	void test_vector7()
	{
		vector<int> v(10u, 1);
		vector<string> v1(10, "1111");

		vector<int> v2(10, 1);



		// vector<int> v;

		//for (auto e : v)
		//{
		//	cout << e << " ";
		//}
		//cout << endl;


		//vector<int> v3(v.begin(), v.end());
		//for (auto e : v3)
		//{
		//	cout << e << " ";
		//}
		//cout << endl;

		//string str("hello world");
		//vector<char> v4(str.begin(), str.end());
		//for (auto e : v4)
		//{
		//	cout << e << " ";
		//}
		//cout << endl;

		//int a[] = { 16,2,77,29 };
		//vector<int> v5(a, a + 4);
		//for (auto e : v5)
		//{
		//	cout << e << " ";
		//}
		//cout << endl;
	}
}