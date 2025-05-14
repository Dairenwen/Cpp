#pragma once

namespace bit1
{
	template<class T, class Container = deque<T>>//����ʹ��deque����ͷ��ͷɾβ��βɾЧ�ʸ���
	class queue
	{
	public:
		bool empty()
		{
			return _con.empty();
		}

		size_t size()
		{
			return _con.size();
		}

		void push(const T& t)
		{
			_con.push_back(t);
		}

		void pop()
		{
			_con.pop_front();
		}

		T& front()
		{
			return _con.front();
		}

		T& back()
		{
			return _con.back();
		}
	private:
		Container _con;
	};
}