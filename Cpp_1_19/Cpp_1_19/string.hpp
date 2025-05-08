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
			//strcpy(_str, str);������\0����Ϊmemcpy
			memcpy(_str, str, sizeof(char) * (_size + 1));//�࿪һ������\0
		}

		string(const string& str)
		{
			_str = new char[str._capacity + 1];
			memcpy(_str, str._str, sizeof(char) * (str._size+ 1));
			_size = str._size;
			_capacity = str._capacity;
		}
		//���������ִ�д��
		//string(const string& s)
		//{
		//	string tmp(s._str);//��������hello\0world�Ͳ��� ����ȱ��
		//	swap(*this, tmp);
		//}
		

		//дʱ����/��ʱ����
		//��Ĭ�Ϸ���ǳ������������ָ��ͬһ��ռ䣬��������µ�string���иĶ����Ͳ����
		//ͬʱÿ���ַ��������ü�����������ٸ�������һ��ռ䣬ֻ�е�����Ϊ1����������
		//�������ⷢ���������

		//windows��û����ʱ���� Linux��������ʱ����

		//���䣺
		//windows�����´���buffer���飬��С16������ַ�����С<16��ֱ�Ӵ���������
		//�������16�ʹ����ַ����У�buffer����ռ��˷ѵ����ռ任ȡʱ��


		//��� ��д��
		//ǳ����������Σ�� 1�������� 2ԭstring�ռ�û���ͷŵ� ����ڴ�й¶
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
			//����������ʱ����tmp���������г�Ա ������tmp�������� ��Ϊ�����˳�Ա ������ԭ�ַ����ռ��ͷŵ���
			return *this;
		}
		//�ִ���
		//string& operator=(string tmp)//ֱ���ڴ�ֵʱ�������죬�βε�������Ҫ���⿪�ٿռ䣬�������
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
			if (_size == _capacity)//��������
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
				reserve(_size + len);//������size+len
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
			while ((int)end >= (int)pos)//ǿ��ת��Ϊ�˷�ֹ�������� ������ѭ��
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
			while ((int)end >= (int)pos)//ǿ��ת��Ϊ�˷�ֹ�������� ������ѭ��
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
//�������Ҫ���÷��� ��������Ϊ�����Ч�� ����Ϊio�ⷴ����  ����Ĳ�������string
//������bit��Ϳ��е�string��ͻ��ע�⣡
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
//����ȡ�����벻������������Ϊ���г�Ա������һ��������thisָ�룬
//s1<<cout������ʹ��ϰ�ߣ����������ⶨ��
istream& operator>>(istream& in, drw::string& s)//���ﲻ�ܼ�const
{
	s.clear();
	char tmp;
	//in >> tmp;//�����ǲ��еģ�>>�����ȡ�ո������\n��Ĭ����ЩΪ�ָ���
	tmp = in.get();//����get�൱��fget�����ȡ�ո��\n�������Զ�ָ����һ��λ��
	//strϵ�к�������\0������� ����strcpy
	while (tmp == ' ' || tmp == '\n')
	{
		tmp = in.get();
	}
	char arr[128] = { 0 };//��ǰ��һ��С�ռ䣬����������
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
