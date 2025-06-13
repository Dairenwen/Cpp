#pragma once
#include<iostream>
#include<math.h>
#include<fstream>
#include<unordered_map>
#define π 3.14159265358979323846
using namespace std;

class StudentManager; // 前向声明
void coutdata(StudentManager& sm);

void showdata(const StudentManager& sm);

void finddata(const StudentManager& sm);


class MyClass
{
public:
	MyClass() { x = 0; y = 0; }
	MyClass(int a,int b);
	void Print();
private:
	int x, y;
};

class rectangle
{
public:
	rectangle(double length = 0, double width = 0)
		:_length(length)
		, _width(width)
	{}

	double area()
	{
		return _length * _width;
	}

	double length()
	{
		return 2 * (_length + _width);
	}

private:
	double _length;
	double _width;
};

class IntArray {
public:
	IntArray(int sz); // 数组初始化为 sz 个元素，初值全为 0
	IntArray(int* array, int sz); // 用静态数组 array 的前 sz 个元素初始化新数组
	IntArray(const IntArray& rhs); // 拷贝构造函数
	~IntArray();
	void init(int* addr, int sz);
	void printAll();
private:
	int* ia;
	int size;
};

class myPoint {
public:
	myPoint(double x0 = 0.0, double y0 = 0.0) :x(x0), y(y0) {}
	myPoint(myPoint& np) :x(np.x), y(np.y) {}
	double GetX() { return x; }
	double GetY() { return y; }
	void SetX(double x0) { x = x0; }
	void SetY(double y0) { y = y0; }
	void SetPoint(double x0, double y0) { x = x0; y = y0; }
	void SetPoint(myPoint& np) { x = np.x; y = np.y; }
	double GetLength(myPoint p) {
		return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
	}
	void Printit() { cout << " (" << x << "," << y << ") "; }
private:
	double x, y;
};

//class Triangle
//{
//public:
//	Triangle(myPoint p1,myPoint p2,myPoint p3)
//		:_p1(p1)
//		,_p2(p2)
//		,_p3(p3)
//	{}
//
//	double singlelength(myPoint p1,myPoint p2)
//	{
//		return sqrt(pow(p1.GetX() - p2.GetX(),2) + pow(p1.GetY() - p2.GetY(),2));
//	}
//
//	double area()
//	{
//		double s = length() / 2;
//		return sqrt(s * (s - singlelength(_p1, _p2)) * (s - singlelength(_p1, _p3)) * (s - singlelength(_p3, _p2)));
//	}
//
//	double length()
//	{
//		return singlelength(_p1, _p2) + singlelength(_p1, _p3) + singlelength(_p3, _p2);
//	}
//	~Triangle()
//	{
//
//	}
//private:
//	myPoint _p1;
//	myPoint _p2;
//	myPoint _p3;
//
//};
//
//class Point
//{
//public:
//	Point() { x = 0; y = 0; }
//	Point(double xv,double yv) { x = xv; y = yv; }
//	Point(Point & pt) { x = pt.x; y = pt.y; }
//	double getx() { return x; }
//	double gety() { return y; }
//	double Area() { return 0; }
//	void Show() { cout << "x=" << x << ' ' << "y=" << y << endl; }
//private:
//	double x,y;
//};
//
//class Rectangle :public Point
//{
//public:
//	Rectangle(Point p,double length,double width)
//		:Point(p)
//		,_length(length)
//		,_width(width)
//	{ }
//
//	void position(Point& pt)
//	{
//		double px = pt.getx();
//		double py = pt.gety();
//		double x = getx();
//		double y = gety();
//		if (px < x || px > x + _length)
//		{
//				printf("坐标点在图形外");
//		}
//		else if (px > x && px < x + _length)
//		{
//			if (py > y || py < y - _width)
//			{
//				printf("坐标点在图形外");
//			}
//			else if (py<y && py>y - _width)
//			{
//				printf("坐标点在图形内");
//			}
//			else
//			{
//				printf("坐标点在图形边缘上");
//			}
//		}
//		else
//		{
//			if (py > y || py < y - _width)
//			{
//				printf("坐标点在图形外");
//			}
//			else
//			{
//				printf("坐标点在图形边缘上");
//			}
//		}
//		
//	}
//
//	~Rectangle()
//	{ }
//
//private:
//	double _length;
//	double _width;
//};
//
//class Circle :public Point
//{
//public:
//	Circle(Point p, double r)
//		:Point(p)
//		, _r(r)
//	{
//
//	}
//	double singlelength(Point p2)
//	{
//		return sqrt(pow(getx() - p2.getx(), 2) + pow(gety() - p2.gety(), 2));
//	}
//
//	void position(Point& pt)
//	{
//		double d = singlelength(pt);
//		if(d<_r) printf("坐标点在图形内");
//		else if (d == _r) printf("坐标点在图形边缘上");
//		else printf("坐标点在图形外");
//	}
//
//	~Circle()
//	{}
//
//private:
//	double _r;
//};
//
//
//class Base
//{
//public:
//	Base(int p1=0, int p2=0) { data1 = p1; data2 = p2; }
//	int Inc1() { return ++data1; }
//	int Inc2() { return ++data2; }
//	void Display()
//	{
//		cout << "data1 = " << data1 << " data2 = " << data2 << endl;
//	}
//protected:
//	int data1, data2;
//};
//class D1 : virtual public Base 
//{
//public:
//	D1(int p1, int p2, int p3) : Base(p1, p2) { data3 = p3; }
//	int Inc1() { return Base::Inc1(); }
//	int Inc3() { return ++data3; }
//	void Display()
//	{
//		cout << "data1 = " << data1 << " data2 = " << data2 << " data3 = " << data3 << endl;
//		cout << "Base::Display() ----";
//		Base::Display();
//	}
//protected:
//	int data3;
//};
//class D2 : virtual public Base 
//{
//public:
//	D2(int p1, int p2, int p4) : Base(p1, p2) { data4 = p4; }
//	int Inc1()
//	{
//		Base::Inc1(); Base::Inc2();
//		return Base::Inc1();
//	}
//	int Inc4() { return ++data4; }
//	void Display()
//	{
//		cout << "data1 = " << data1 << " data2 = " << data2 << " data4 = " << data4 << endl;
//		cout << "Base::Display() ----";
//		Base::Display();
//	}
//protected:
//	int data4;
//};
//class D12 : public D1, public D2 {
//public:
//	D12(int p11, int p12, int p13, int p21, int p22, int p23, int p)
//		: D1(p11, p12, p13), D2(p21, p22, p23)
//	{
//		data5 = p;
//	}
//	int Inc1()
//	{
//		D1::Inc1(); D2::Inc1();
//		return D1::Inc1();
//	}
//	int Inc5() { return ++data5; }
//
//
//	void Display()
//	{
//		cout << "data1 = " << data1 << " data2 = " << data2 << endl; // ①
//		cout << " data3 = " << data3 << "data4 = " << data4 << " data5 = " << data5 << endl;
//		cout << "D1::Display( )----";
//		D1::Display();
//		cout << "D2::Display( )----";
//		D2::Display();
//	}
//private:
//	int data5;
//};


class Geometric_shape
{
public:
	Geometric_shape()
	{}

	virtual void Show()
	{
		cout << "几何图形" << endl;
	}

	virtual double perimeter()
	{
		cout << "几何图形周长" << endl;
		return 0;
	}

	virtual double area()
	{
		cout << "几何图形面积" << endl;
		return 0;
	}

	virtual double volume()
	{
		cout << "几何图形体积" << endl;
		return 0;
	}

	virtual ~Geometric_shape() 
	{}
private:

};

class Rectangle : public Geometric_shape
{
public:
	Rectangle(double length = 0, double width = 0)
		:Geometric_shape()
		,_length(length)
		,_width(width)
	{
	}

	double perimeter()
	{
		return 2 * (_length + _width);
	}
	double area()
	{
		return _length * _width;
	}
	double volume()
	{
		return 0;
	}

	double getLength()
	{
		return _length;
	}
	double getWidth()
	{
		return _width;
	}
	void Show()
	{
		cout << "矩形" << endl;
	}

	~Rectangle()
	{}
private:
	double _length;
	double _width;

};


class Circle : public Geometric_shape
{
public:
	Circle(double radius=0)
		:Geometric_shape()
		, _radius(radius)
	{
	}

	double perimeter()
	{
		return 2 * π * _radius;
	}
	double area()
	{
		return π * _radius * _radius;
	}
	double volume()
	{
		return 0;
	}
	void Show()
	{
		cout << "圆形" << endl;
	}

	double getRadius()
	{
		return _radius;
	}
private:
	double _radius;
};

class Triangle : public Geometric_shape
{
public:
	Triangle(double first = 0, double second = 0,double third=0)
		:Geometric_shape()
		,_first(first)
		,_second(second)
		, _third(third)
	{
	}

	double perimeter()
	{
		return _first + _second + _third;
	}
	double area()
	{
		double s = perimeter() / 2;
		return sqrt(s * (s - _first) * (s - _second) * (s - _third));// 海伦公式
	}
	double volume()
	{
		return 0;
	}

	double getFirst()
	{
		return _first;
	}
	double getSecond()
	{
		return _second;
	}
	double getThird()
	{
		return _third;
	}

	void Show()
	{
		cout << "三角形" << endl;
	}
private:
	double _first;
	double _second;
	double _third;

};

class Box :public Rectangle
{
public:
	Box(double length = 0, double width = 0, double height = 0)
		:Rectangle(length, width)
		,_height(height)
	{
	}

	double perimeter()
	{
		return Rectangle::perimeter();
	}
	double area()
	{
		return Rectangle::area();
	}
	double volume()
	{
		return getLength() * getWidth() * _height;
	}

	void Show()
	{
		cout << "长方体" << endl;
	}

private:
	double _height;
};

class Cylinder:public Circle
{
public:
	Cylinder(double radius = 0, double height = 0)
		:Circle(radius)
		,_height(height)
	{
	}
	void Show()
	{
		cout << "圆柱体" << endl;
	}

	double perimeter()
	{
		return Circle::perimeter();
	}
	double area()
	{
		return Circle::area();
	}
	double volume()
	{
		return Circle::area() * _height;
	}

private:
	double _height;
};

class Cone:public Circle
{
public:
	Cone(double radius = 0, double height = 0)
		:Circle(radius)
		,_height(height)
	{
	}
	void Show()
	{
		cout << "圆锥体" << endl;
	}

	double perimeter()
	{
		return Circle::perimeter();
	}
	double area()
	{
		return Circle::area();
	}
	double volume()
	{
		return Circle::area() * _height / 3;
	}

private:
	double _height;
};	

class T_pyramid:public Triangle
{
public:
	T_pyramid(double first = 0, double second = 0, double third = 0,double height=0)
		:Triangle(first, second, third)
		, _height(height)
	{}
	void Show()
	{
		cout << "三棱锥" << endl;
	}

	double perimeter()
	{
		return Triangle::perimeter();
	}
	double area()
	{
		return Triangle::area();
	}
	double volume()
	{
		return Triangle::area() * _height / 3;
	}
private:
	double _height;
};

class T_prism:public Triangle
{
public:
	T_prism(double first = 0, double second = 0, double third = 0,double height=0)
		:Triangle(first, second, third)
		, _height(height)
	{
	}

	void Show()
	{
		cout << "三棱柱" << endl;
	}

	double perimeter()
	{
		return Triangle::perimeter();
	}
	double area()
	{
		return Triangle::area();
	}
	double volume()
	{
		return Triangle::area() * _height;
	}

private:
	double _height;
};


class Student
{
	friend ostream& operator<<(ostream& os, const Student& s);
	friend istream& operator>>(istream& is, Student& s);
	friend class StudentManager; 
public:
	Student(string id="",string name="",double score=0)
		:_id(id), _name(name), _score(score)
	{}


	Student(const Student& rhs)
		:_id(rhs._id), _name(rhs._name), _score(rhs._score)
	{
	}

	Student& operator=(const Student& rhs)
	{
		if (this != &rhs) {
			_id = rhs._id;
			_name = rhs._name;
			_score = rhs._score;
		}
		return *this;
	}


private:
	string _id;
	string _name;
	double _score;
};

ostream& operator<<(ostream& os, const Student& s);


istream& operator>>(istream& is, Student& s);


class StudentManager
{
	friend void showdata(const StudentManager& sm);
public:
	StudentManager(string filename="")
		: _filename(filename)
	{
		ifstream ifs(_filename, ios_base::binary | ios_base::in);
		Student s;
		while (ifs >> s) {
			stu[s._id] = s; // 从文件中读取学生信息
		}
	}

	void AddStudent(const Student& s) 
	{
		stu[s._id] = s; // 使用学生ID作为键存储学生信息
	}

	void RemoveStudent(const string& id) 
	{
		stu.erase(id); // 根据学生ID删除学生信息
	}

	void UpdateStudent(const Student& s) 
	{
		stu[s._id] = s; // 更新学生信息
	}

	void PrintStudents(const string& str) const 
	{
		int sz = str.size();
		for (const auto& e : stu)
		{
			if(memcmp(e.second._name.c_str(), str.c_str(), sizeof(char)*sz) == 0) // 匹配前缀
			{
				cout << e.second << endl; // 输出学生信息
			}
		}
	}

	void SaveToFile(const string& filename) const 
	{
		ofstream ofs(filename,ios_base::binary|ios_base::out);
		for (const auto& e : stu) {
			ofs << e.second << endl; // 保存学生信息到文件
		}
	}

	void LoadFromFile(const string& filename) 
	{
		ifstream ifs(filename,ios_base::binary|ios_base::in);
		Student s;
		while (ifs >> s) {
			stu[s._id] = s; // 从文件中读取学生信息
		}
	}

	~StudentManager() 
	{
		ofstream ofs(_filename, ios_base::binary | ios_base::out);
		for (const auto& e : stu) {
			ofs << e.second << endl; // 保存学生信息到文件
		}
	}
private:
	unordered_map <string, Student> stu; // 学生信息存储
	string _filename; // 文件名
};

