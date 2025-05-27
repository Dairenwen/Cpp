#pragma once
#include<vector>
#include<iostream>
#include<list>
#include<map>
#include<functional>
#include<memory>
#include<unordered_map>
using namespace std;

namespace bit
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{ }

		auto_ptr(auto_ptr<T>& ptr)
			:_ptr(ptr._ptr)
		{
			ptr._ptr = nullptr;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};

	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{
		}


		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		//unique�����õ��˷�������c++98��Ҳ����ֻ������ʵ�֣��������ŵ�private��
		unique_ptr(unique_ptr<T>& ptr) = delete;

		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;

		T* _ptr;
	};

	template<class T>
	class shared_ptr
	{
		template<class T>
		friend class weak_ptr;
	public:

		template<class D>
		shared_ptr(T* ptr,D del)
			:_ptr(ptr)
			,_pcount(new int(1))
			,_del(del)
		{}

		shared_ptr(T* ptr=nullptr)
			:_ptr(ptr)
			, _pcount(new int(1))
		{}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
		{
			++(*(sp._pcount));
			_pcount = sp._pcount;
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			//�ڸı䱻��ֵ�����ָ��֮ǰ����Ҫ�����Ƿ�Ҫ�ͷű���ֵ���������ڴ���Դ
			//Ҳ����˵�ı�ָ��֮ǰҪ��ԭ�������Դ��pcount--���������0����Ҫ�ͷ�

			//����Ҫ����ָ��ͨ��һ���ڴ������ָ���໥��ֵ�������ͬ��ֻ���鷳һ�㣬���ͬ����ô�ͻ�����ͷź���ȥ���ʵ�����
			if (sp._ptr == _ptr)
			{
				return *this;
			}

			//���ڱ���ֵ��Ҫ�ǵü�ȥ���ü����������Ƿ��ͷ��ڴ棬��ֹ����ڴ�й©
			if (--(*_pcount) == 0)
			{
				delete _ptr;
				delete _pcount;
			}
			
			_ptr = sp._ptr;
			++*(sp._pcount);
			_pcount = sp._pcount;
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T* get()const//����ָ��
		{
			return _ptr;
		}

		size_t use_count()const//�������ü����ĸ���
		{
			return *_pcount;
		}

		~shared_ptr()
		{
			if (--(*_pcount) == 0)
			{
				_del(_ptr);
				delete _pcount;
			}
		}
	private:
		T* _ptr;
		//shared_ptr����֧�ֶ��ָ��ָ��ͬһ��ռ䣬��ôʵ�֣�
		//���ü��������ʵ�֣�ʹ��static int�����У���Ϊ�������ֻ����һ��static��
		//����ÿһ����Դ����Ҫһ������
		int* _pcount;

		function<void(T*)> _del;//ʹ�ð�װ�������ģ������޷��漰��������������
	};


	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()//��֧�ִ��ι���
			:_ptr(nullptr)
		{
		}

		weak_ptr(const shared_ptr<T>& sp)//֧��sharedptr����
			:_ptr(sp._ptr)
		{ }


		weak_ptr<T>& operator=(const weak_ptr<T>& wp)
		{
			_ptr = wp._ptr;
			return *this;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
	};
}