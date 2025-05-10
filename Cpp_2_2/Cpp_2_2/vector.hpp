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

		//拷贝构造函数
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

		vector(int n, const T& t)//不用size_t,否则会直接匹配迭代器构造函数
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

		size_t capacity()const//const能带就带不然会出错
		{
			return _end_of_storage - _start;
		}
		
		size_t size()const//const修饰的vector调用const修饰函数
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
				//这里memcpy发生的是浅拷贝，为了防止自定义类型浅拷贝，采用赋值形式，这样可以调用赋值重载
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
		//这里如果要扩容，pos指向的地址在释放空间后就失效了，所以要先记录位置
		//为了防止外部迭代器失效，返回一个迭代器指针更新外部的迭代器

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
		//删除也有迭代器失效的问题，调用erase之后就不能再对迭代器进行访问了
		//vs上直接通过断言拒绝，但g++上某些可以跑过，这里返回删除的下一个位置的迭代器

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
		//匿名对象，以便任何类型都可以调用拷贝构造
		//这里内置类型也做了处理，默认有拷贝构造函数，如int默认为0

	private:
		iterator _start;
		iterator _finish;//指向最后一个元素下一个位置
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

		// insert以后迭代器可能会失效(扩容)
		// 记住，insert以后就不要使用这个形参迭代器了，因为他可能失效了
		v1.insert(p, 300);

		// 高危行为
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

		//// erase以后，迭代器失效了，不能访问
		//// vs进行强制检查，访问会直接报错
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