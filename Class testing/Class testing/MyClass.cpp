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
		ia[ix] = 0; // 初始化数组元素
}
IntArray::IntArray(int* array, int sz) {
	init(new int[sz], sz);
	for (int ix = 0; ix < size; ++ix)
		ia[ix] = array[ix]; // 拷贝数据成员
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
	cout << "学生人数：";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "第" << i + 1 << "个学生(学号 姓名 成绩)：";
		Student student;
		cin >> student;
		sm.AddStudent(student);
	}
}


void showdata(const StudentManager& sm)
{
	cout << "学号 姓名 成绩" << endl;
	for (const auto& e : sm.stu)
	{
		cout << e.second << endl;
	}
}


void finddata(const StudentManager& sm)
{
	string str;
	cout << "输入姓名：";
	cin >> str;
	cout << "输出匹配的结果：" << endl;
	cout << "学号 姓名 成绩" << endl;
	sm.PrintStudents(str);
}