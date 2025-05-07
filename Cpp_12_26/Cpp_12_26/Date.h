//void Func(int a,int b=20);

//typedef int DataType;
//class Stack
//{
//public:
//	void Init(size_t capacity);
//
//	void Push(const DataType& data)
//	{
//		// 扩容
//		_array[_size] = data;
//		++_size;
//	}
//	DataType* _array;
//	size_t _capacity;
//	size_t _size;
//};

#pragma once
#include<iostream>
using namespace std;

class Date
{
	friend ostream& operator<<(ostream& out, const Date& d);//友元函数：类中的私有成员变量可以由外部函数进行访问
	friend istream& operator>>(istream& in,  Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1);

	void Print() const//这里加上const修饰的是*this，建议不修改成员变量的成员函数后面都加上const，好处多多，普通对象和const对象都适用
	{//只要成员函数内部不修改成员变量，都可以加上const，const修饰和普通变量都可以用·
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	Date(const Date& d)   
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	bool operator<(const Date& x);
	bool operator==(const Date& x);
	bool operator<=(const Date& x);
	bool operator>(const Date& x);
	bool operator>=(const Date& x);
	bool operator!=(const Date& x);

	int GetMonthDay(int year, int month);

	// d1 + 100
	Date& operator+=(int day);
	Date operator+(int day)const;
	Date& operator-=(int day);
	Date operator-(int day)const;
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);

	int operator-(const Date& d);
	//ostream& operator<<(ostream& out);
	//这里不能写成类中的成员函数是因为默认第一个隐藏参数是this指针，那么就必须d1<<out，
	//使用非常别扭，所以写成友元函数，访问类中私有成员变量
private:
	int _year;
	int _month;
	int _day;
};

