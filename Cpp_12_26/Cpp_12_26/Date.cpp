#include"Date.h"
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
}
bool Date::operator<(const Date& x)
{
	if (_year < x._year)
	{
		return true;
	}
	else if (_year == x._year && _month < x._month)
	{
		return true;
	}
	else if (_year == x._year && _month == x._month && _day < x._day)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Date::operator==(const Date& x)
{
	return _year == x._year && _month == x._month && _day == x._day;
}
//复用
bool Date::operator<=(const Date& x)
{
	return *this == x || *this < x;
}
bool Date::operator>(const Date& x)
{
	return !(*this <= x);
}
bool Date::operator>=(const Date& x)
{
	return *this > x || *this == x;
}
bool Date::operator!=(const Date& x)
{
	return !(*this == x);
}

int Date::GetMonthDay(int year, int month)
{
	static int daysArr[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	else
	{
		return daysArr[month];
	}
}

Date& Date::operator+=(int day)//变量不销毁，返回&提高效率。且可以连续操作
{
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year, _month);
		if (_month == 12)
		{
			_month = 1;
			_year++;
		}
		else
		{
			_month++;
		}
	}
	return *this;
}
Date Date::operator+(int day)const//变量销毁，不能返回引用，否则就会出错
{
	Date tmp(*this);
	tmp += day;
	return tmp;
}

Date& Date::operator++()
{
	*this += 1;
	return *this;
}
Date Date::operator++(int)//这里是后置++，与前置++不构成重载，为了以示区分，加上一个参数，这个参数不一定要传参，也可以只是一个类型，在调用的时候可以传任意值！
{
	Date tmp(*this);
	*this += 1;
	return tmp;
}

Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_month = 12;
			_year--;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}
Date Date::operator-(int day)const
{
	Date tmp(*this);
	tmp -= day;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}

Date Date::operator--(int)
{
	Date tmp(*this);
	*this -= 1;
	return tmp;
}

int Date::operator-(const Date& d)
{
	int flag = 1;
	Date max = d;
	Date min = *this;
	if (*this > d)
	{
		flag = -1;
		max = *this;
		min = d;
	}
	int n = 0;
	while (min < max)
	{
		min += 1;
		n++;
	}
	return flag * n;
}

//ostream& Date::operator<<(ostream& out)
//{
//	cout << _year << "年" << _month << "月" << _day << "日" << endl;
//	return out;
//}

ostream& operator<<(ostream& out, const Date& d)//这里out前面不能加const 因为输出的内容要往cout里面写，输出流是这样，输入流也是这样！
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}
//ostream istream后面都要加上& 否则发生拷贝构造 但IO库反拷贝
istream& operator>>(istream& in,Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}