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
		//这里带有模板的声明与定义分离是及其危险的行为，跟内联函数的声明与定义分离一样

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