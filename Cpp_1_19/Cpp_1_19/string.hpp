#define _CRT_SECURE_NO_WARNINGS 1
#include<string.h>
#include<assert.h>
using namespace std;
namespace drw
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])
			, _capacity(strlen(str))
			, _size(strlen(str))
		{
			//strcpy(_str, str);处理不了\0，改为memcpy
			memcpy(_str, str, sizeof(char) * (_size + 1));//多开一个留给\0
		}

		string(const string& str)
		{
			_str = new char[str._capacity + 1];
			memcpy(_str, str._str, sizeof(char) * (str._size+ 1));
			_size = str._size;
			_capacity = str._capacity;
		}
		//拷贝构造现代写法
		//string(const string& s)
		//{
		//	string tmp(s._str);//但这样像hello\0world就不行 存在缺陷
		//	swap(*this, tmp);
		//}
		

		//写时拷贝/延时拷贝
		//先默认发生浅拷贝，让两个指向同一块空间，如果不对新的string进行改动，就不深拷贝
		//同时每个字符串有引用计数，代表多少个对象共用一块空间，只有当计数为1，发生析构
		//这样避免发生多次析构

		//windows下没有延时拷贝 Linux环境下延时拷贝

		//补充：
		//windows环境下存在buffer数组，大小16，如果字符串大小<16就直接存在数组里
		//如果大于16就存在字符串中，buffer数组空间浪费掉，空间换取时间


		//深拷贝 神写法
		//浅拷贝有两种危害 1两次析构 2原string空间没有释放掉 造成内存泄露
		/*string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[s._capacity + 1];
				memcpy(tmp, s._str, s._size+1);
				delete[] _str;
				_str = tmp;

				_size = s._size;
				_capacity = s._capacity;
			}

			return *this;
		}*/
		string& operator=(const string& s)
		{
			string tmp(s);
			swap(_str, tmp._str);
			swap(_capacity, tmp._capacity);
			swap(_size, tmp._size);
			//拷贝构造临时对象tmp，交换所有成员 出函数tmp析构销毁 因为交换了成员 连带着原字符串空间释放掉了
			return *this;
		}
		//现代：
		//string& operator=(string tmp)//直接在传值时拷贝构造，形参的生成需要另外开辟空间，属于深拷贝
		//{
		//	swap(*this, tmp);
		//	return *this;
		//}

		const char* c_str()const
		{
			return _str;
		}

		size_t size()const
		{
			return _size;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		const char& operator[](size_t pos)const
		{
			assert(pos < _size);
			return _str[pos];
		}

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin()const
		{
			return _str;
		}

		const_iterator end()const
		{
			return _str + _size;
		}

		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				memcpy(tmp, _str, sizeof(char) * (_size + 1));
				_capacity = n;
				delete[] _str;
				_str = tmp;
			}
		}

		void resize(size_t n, char ch='\0')
		{
			if (n < _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				reserve(n);
				while (_size < n)
				{
					_str[_size++] = ch;
				}
				_str[_size] = '\0';
			}
		}

		void push_back(char ch)
		{
			if (_size == _capacity)//二倍扩容
			{
				reserve(_capacity == 0 ? 4 : 2 * _capacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);//至少扩size+len
			}
			memcpy(_str + _size, str,sizeof(char)*(len+1));
			_size += len;
		}

		string& operator+=(const char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}

		void insert(size_t pos, size_t n, char ch)
		{
			if (_size + n > _capacity)
			{
				reserve(_size + n);
			}
			size_t end = _size;
			while ((int)end >= (int)pos)//强制转换为了防止整型提升 陷入死循环
			{
				_str[end + n] = _str[end];
				end--;
			}
			for (size_t i = 0; i < n; i++)
			{
				_str[pos + i] = ch;
			}
			_size += n;
		}

		void insert(size_t pos, const char* str)
		{
			size_t len = strlen(str);
			if (len + _size > _capacity)
			{
				reserve(len + _size);
			}
			size_t end = _size;
			while ((int)end >= (int)pos)//强制转换为了防止整型提升 陷入死循环
			{
				_str[end + len] = _str[end];
				end--;
			}
			for (size_t i = 0; i < len; i++)
			{
				_str[pos + i] = str[i];
			}
			_size += len;
		}

		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t begin = pos + len;
				while (begin <= _size)
				{
					_str[pos++] = _str[begin++];
				}
				_size -= len;
			}
		}

		size_t find(char ch, size_t pos = 0)
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return npos;
		}

		size_t find(const char* str, size_t pos = 0)
		{
			assert(pos < _size);
			const char* ret = strstr(_str + pos, str);
			if (ret)
			{
				return ret - _str;
			}
			else
			{
				return npos;
			}
		}

		string substr(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);
			string tmp;
			size_t n = len;
			if (len == npos || pos + len >= _size)
			{
				n = _size - pos;
			}
			tmp.reserve(n);
			for (size_t i = pos; i < n + pos; i++)
			{
				tmp += _str[i];
			}
			return tmp;
		}

		bool operator>(const string& s)const
		{
			int ret = memcmp(_str, s._str, sizeof(char) * (_size > s._size ? s._size : _size));
			return ret == 0 ? _size > s._size:ret > 0;
		}

		bool operator==(const string& s)const
		{
			return _size == s._size && memcmp(_str, s._str, sizeof(char) * (_size)) == 0;
		}

		bool operator>=(const string& s)const
		{
			return *this > s || *this == s;
		}

		bool operator<(const string& s)const
		{
			return !(*this >= s);
		}

		bool operator<=(const string& s)const
		{
			return *this < s || *this == s;
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		~string()
		{
			delete[] _str;
			_capacity = 0;
			_size = 0;
			_str = nullptr;
		}
	private:
		char* _str;
		size_t _capacity;
		size_t _size;
	public:
		static size_t npos;
	};
	size_t string::npos = -1;
}
//这里必须要引用返回 不仅仅是为了提高效率 是因为io库反拷贝  后面的参数类型string
//不带上bit会和库中的string冲突！注意！
ostream& operator<<(ostream& out, const drw::string& s)
{
	/*for (size_t i = 0; i < s.size(); i++)
	{
		out << s[i];
	}*/

	for (auto ch : s)
	{
		out << ch;
	}

	return out;
}
//流提取流插入不放入类中是因为类中成员函数第一个参数是this指针，
//s1<<cout不符合使用习惯，所以在类外定义
istream& operator>>(istream& in, drw::string& s)//这里不能加const
{
	s.clear();
	char tmp;
	//in >> tmp;//这样是不行的，>>不会读取空格或者是\n，默认这些为分隔符
	tmp = in.get();//这里get相当于fget，会读取空格和\n，读完自动指向下一个位置
	//str系列函数遇到\0都会结束 包括strcpy
	while (tmp == ' ' || tmp == '\n')
	{
		tmp = in.get();
	}
	char arr[128] = { 0 };//提前开一个小空间，避免多次扩容
	int i = 0;
	while (tmp != ' ' || tmp != '\n')
	{
		if (i == 127)
		{
			arr[i] = '\0';
			s += arr;
			i = 0;
		}
		arr[i++] = tmp;
		tmp = in.get();
	}
	if (i != 0)
	{
		arr[i] = '\0';
		s += arr;
	}
	return in;
}
