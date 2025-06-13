#include<iostream>
#include"MyClass.hpp"
using namespace std;

//void testMyclass()
//{
//	MyClass a(1, 2);
//	MyClass b(3, 4);
//	a.Print();
//	b.Print();
//}
//
//void testrectangle()
//{
//	rectangle a(20, 50);
//	rectangle b(3.6, 4.5);
//	cout << a.area() << endl;
//	cout << b.area() << endl;
//	cout << a.length() << endl;
//	cout << b.length() << endl;
//}
//
//void testIntArray()
//{
//	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	IntArray arr1(10), arr2(a, 5), arr3(arr2);
//	arr1.printAll();
//	arr2.printAll();
//	arr3.printAll();
//}
//
//void testTriangle()
//{
//	myPoint p1(0, 0);
//	myPoint p2(3, 0);
//	myPoint p3(0, 4);
//	Triangle t(p1, p2, p3);
//	cout << t.area() << endl;
//	cout << t.length() << endl;
//}
//
//void testRectangle()
//{
//	Point p(0, 0);
//	Point pt(0, 1);
//	Rectangle r(pt, 1, 1);
//	r.position(p);
//}
//
//void testCircle()
//{
//	Point p(0, 0);
//	Point pt(0, 1);
//	Circle c(p, 1);
//	c.position(pt);
//
//}
//
//void testclass()
//{
//		D12 d(1, 2, 3, 4, 5, 6, 7);
//		d.Display();
//		cout << endl;
//		d.Inc1();
//		d.Inc2(); // ��
//		d.Inc3();
//		d.Inc4();
//		d.Inc5();
//		d.D12::Inc1();
//		d.Display();
//}

void testinherit() 
{
	Geometric_shape* gs[] = { new Circle(10),new Rectangle(6,8), new
	Triangle(3,4,5), new Box(6,8,3), new Cylinder(10,3), new Cone(10,3), new
	T_pyramid(3,4,5,3), new T_prism(3,4,5,3) };
	for (int i = 0; i < 8; i++) {
		gs[i]->Show(); // ���ͼ�ε����ͣ��硰Բ�Ρ�
		cout << endl;
	}
	cout << "ƽ��ͼ�Σ�" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "ͼ���ܳ���" << gs[i]->perimeter() << '\t';
		cout << "ͼ�������" << gs[i]->area() << '\t';
		cout << "ͼ�������" << gs[i]->volume() << endl;
	}
	cout << "����ͼ�Σ�" << endl;
	for (int i = 3; i < 8; i++) {
		cout << "ͼ�ε��ܳ���" << gs[i]->perimeter() << '\t';
		cout << "ͼ�ε������" << gs[i]->area() << '\t';
		cout << "ͼ����� ��" << gs[i]->volume() << endl;
	}
}

void menu()
{
	cout << "ѡ��(1:�������� 2:������� 3:�������������� �����˳�):" ;
}

void testfile()
{
	StudentManager sm("stud.dat");
	int choose;
	while (1)
	{
		menu();
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << "��������" << endl;
			coutdata(sm);
			break;
		case 2:
			cout << "�������" << endl;
			showdata(sm);
			break;
		case 3:
			cout << "��������������" << endl;
			finddata(sm);
			break;
		default:
			return;
		}
	}
}
int main()
{
	//testMyclass();
	//testrectangle();
	//testIntArray();
	//testTriangle();
	//testclass();
	//testRectangle();
	//testCircle();
	//testinherit();
	testfile();
	return 0;
}