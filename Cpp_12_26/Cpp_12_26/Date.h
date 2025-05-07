//void Func(int a,int b=20);

//typedef int DataType;
//class Stack
//{
//public:
//	void Init(size_t capacity);
//
//	void Push(const DataType& data)
//	{
//		// ����
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
	friend ostream& operator<<(ostream& out, const Date& d);//��Ԫ���������е�˽�г�Ա�����������ⲿ�������з���
	friend istream& operator>>(istream& in,  Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1);

	void Print() const//�������const���ε���*this�����鲻�޸ĳ�Ա�����ĳ�Ա�������涼����const���ô���࣬��ͨ�����const��������
	{//ֻҪ��Ա�����ڲ����޸ĳ�Ա�����������Լ���const��const���κ���ͨ�����������á�
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
	//���ﲻ��д�����еĳ�Ա��������ΪĬ�ϵ�һ�����ز�����thisָ�룬��ô�ͱ���d1<<out��
	//ʹ�÷ǳ���Ť������д����Ԫ��������������˽�г�Ա����
private:
	int _year;
	int _month;
	int _day;
};

