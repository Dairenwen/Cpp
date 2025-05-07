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
//����
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

Date& Date::operator+=(int day)//���������٣�����&���Ч�ʡ��ҿ�����������
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
Date Date::operator+(int day)const//�������٣����ܷ������ã�����ͻ����
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
Date Date::operator++(int)//�����Ǻ���++����ǰ��++���������أ�Ϊ����ʾ���֣�����һ�����������������һ��Ҫ���Σ�Ҳ����ֻ��һ�����ͣ��ڵ��õ�ʱ����Դ�����ֵ��
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
//	cout << _year << "��" << _month << "��" << _day << "��" << endl;
//	return out;
//}

ostream& operator<<(ostream& out, const Date& d)//����outǰ�治�ܼ�const ��Ϊ���������Ҫ��cout����д���������������������Ҳ��������
{
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}
//ostream istream���涼Ҫ����& �������������� ��IO�ⷴ����
istream& operator>>(istream& in,Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}