
namespace bit
{
	template<class Iterator,class Ref,class Ptr>
	struct Reverseiterator
	{
		typedef Reverseiterator<Iterator, Ref, Ptr> self;
		Iterator _it;

		Reverseiterator(const Iterator& it)
			:_it(it)
		{ }

		Ref operator*()
		{
			Iterator tmp = _it;
			return *(--tmp);
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		self& operator++()
		{
			return _it--;
		}

		self& operator++(int)
		{
			self tmp = _it;
			_it--;
			return tmp;
		}

		self& operator--()
		{
			return _it++;
		}

		self& operator--(int)
		{
			Iterator tmp = _it;
			_it++;
			return tmp;
		}

		bool operator==(const self& s)
		{
			return _it == s._it;
		}

		bool operator!=(const self& s)
		{
			return _it != s._it;
		}
	};

}