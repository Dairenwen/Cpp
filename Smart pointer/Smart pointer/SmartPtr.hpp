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
		//unique这里用到了反拷贝，c++98中也可以只声明不实现，将声明放到private中
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
			//在改变被赋值对象的指针之前，先要考虑是否要释放被赋值对象管理的内存资源
			//也就是说改变指针之前要对原理管理资源的pcount--，如果减到0就需要释放

			//首先要考虑指向通过一块内存的两个指针相互赋值，如果不同名只是麻烦一点，如果同名那么就会造成释放后再去访问的问题
			if (sp._ptr == _ptr)
			{
				return *this;
			}

			//对于被赋值的要记得减去引用计数来决定是否释放内存，防止造成内存泄漏
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

		T* get()const//返回指针
		{
			return _ptr;
		}

		size_t use_count()const//返回引用计数的个数
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
		//shared_ptr可以支持多个指针指向同一块空间，怎么实现？
		//引用计数，如何实现？使用static int不可行，因为多个对象只能有一个static，
		//但是每一块资源都需要一个计数
		int* _pcount;

		function<void(T*)> _del;//使用包装器来解决模板参数无法涉及析构函数的问题
	};


	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()//不支持传参构造
			:_ptr(nullptr)
		{
		}

		weak_ptr(const shared_ptr<T>& sp)//支持sharedptr构造
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