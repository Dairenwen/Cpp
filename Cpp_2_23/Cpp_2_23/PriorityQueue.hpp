#pragma once
namespace bit
{
	//两种仿函数
	template<class T>
	class Less
	{
	public:
		bool operator()(const T& a,const T& b)
		{
			return a > b;
		}
	};

	template<class T>
	class Greater
	{
	public:
		bool operator()(const T& a, const T& b)
		{
			return a < b;
		}
	};

	template<class T,class Container=vector<T>,class Compare=Less<T>>
	class priority_queue
	{
		//向下建堆
		void AdjustDown(int parent)
		{
			Compare con;
			int child = parent * 2 + 1;
			while (child < _con.size())
			{
				if (child + 1 < _con.size() && con(_con[child + 1] , _con[child]))
				{
					child++;
				}
				if (con(_con[child] , _con[parent]))
				{
					swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		//向上建堆
		void AdjustUp(int child)
		{
			Compare con;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (con(_con[child], _con[parent]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
	public:
		template<class InputIterator>
		priority_queue(InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				push(*begin);
				begin++;
			}
		}

		void push(const T& t)
		{
			_con.push_back(t);
			for (int i = (_con.size() - 2) / 2; i >= 0; i--)
			{
				AdjustDown(i);
			}
			/*for (int i = 0; i < _con.size(); i++)
			{
				AdjustUp(i);
			}*/
		}

		void pop()
		{
			swap(_con.front(), _con.back());
			_con.pop_back();
			AdjustDown(0);
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

		const T& top()const
		{
			return _con.front();
		}
	private:
		Container _con;
	};
}