#pragma once
#include<deque>
using namespace std;

namespace test
{
	template<class T,class Container=deque<T>>
	class stack
	{
	public:
		void push(const T& t);
		void pop();
		//�������ģ��������붨������Ǽ���Σ�յ���Ϊ�������������������붨�����һ��

		T& top()
		{
			return _con.back();
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}