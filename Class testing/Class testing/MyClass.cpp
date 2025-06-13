#include"MyClass.hpp"
#include<iostream>


void IntArray::init(int* addr, int sz)
{
	size = sz;
	ia = addr;
}
IntArray::IntArray(int sz) {
	init(new int[sz], sz);
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = 0; // ��ʼ������Ԫ��
}
IntArray::IntArray(int* array, int sz) {
	init(new int[sz], sz);
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = array[ix]; // �������ݳ�Ա
}
IntArray::IntArray(const IntArray& rhs)
{
	init(new int[rhs.size], rhs.size);
	for (int ix = 0; ix < size; ix++)
		ia[ix] = rhs.ia[ix];
}
IntArray::~IntArray()
{
	delete[] ia;
	ia = nullptr;
}

void IntArray::printAll()
{
	for (int ix = 0; ix < size; ++ix)
		cout << ia[ix] << " ";
	cout << endl;
}

MyClass::MyClass(int a = 0, int b = 0)
{
	x = a;
	y = b;
}

void MyClass::Print()
{
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
}

ostream& operator<<(ostream& os, const Student& s)
{
	os << s._id << "		" << s._name << "	" << s._score;
	return os;
}

istream& operator>>(istream& is, Student& s)
{
	is >> s._id >> s._name >> s._score;
	return is;
}

void coutdata(StudentManager& sm)
{
	cout << "ѧ��������";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "��" << i + 1 << "��ѧ��(ѧ�� ���� �ɼ�)��";
		Student student;
		cin >> student;
		sm.AddStudent(student);
	}
}


void showdata(const StudentManager& sm)
{
	cout << "ѧ�� ���� �ɼ�" << endl;
	for (const auto& e : sm.stu)
	{
		cout << e.second << endl;
	}
}


void finddata(const StudentManager& sm)
{
	string str;
	cout << "����������";
	cin >> str;
	cout << "���ƥ��Ľ����" << endl;
	cout << "ѧ�� ���� �ɼ�" << endl;
	sm.PrintStudents(str);
}