#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Date
{
	friend ostream& operator << (ostream& out, const Date& d);
	friend istream& operator >> (istream& in, Date& d);
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
	}

	operator string()
	{
		string str;
		str += to_string(_year);
		str += ' ';
		str += to_string(_month);
		str += ' ';
		str += to_string(_day);
		return str;
	}

	operator bool()
	{
		// 这里是随意写的，假设输入_year为0，则结束
		if (_year == 0)
			return false;
		else
			return true;
	}

	int _year;
	int _month;
	int _day;
};

istream& operator >> (istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	return in;
}

ostream& operator << (ostream& out, const Date& d)
{
	out << d._year << " " << d._month << " " << d._day;
	return out;
}


//文件操作
void test5()
{
	Date tmp(2025, 4, 13);
	//将tmp以二进制写入文件
	FILE* fp1 = fopen("writein.txt", "wb");
	fwrite(&tmp, sizeof(Date), 1, fp1);
	fclose(fp1);
	//将tmp以文本形式写入文件
	string writein = tmp;
	FILE* fp2 = fopen("writein.txt", "a+");
	fputs(writein.c_str(), fp2);
	fclose(fp2);

	//那么c++中是如何处理的呢？

}


struct ServerInfo
{
	char _address[32];
	int _port;
	//二进制读写不能用string vector这样的对象存数据
	//请注意不能存在string，写入都是内存中的数据，如果字符串大于16
	//写入的将会是存储的在堆上空间的地址，这是无效存储
	Date _date;
};

struct ConfigManager
{
public:
	ConfigManager(const char* filename)
		:_filename(filename)
	{
	}

	void WriteBin(const ServerInfo& info)
	{
		ofstream ofs(_filename, ios_base::out | ios_base::binary);
		ofs.write((const char*)&info, sizeof(info));
	}

	void ReadBin(ServerInfo& info)
	{
		ifstream ifs(_filename, ios_base::in | ios_base::binary);
		ifs.read((char*)&info, sizeof(info));
	}
	// C++文件流的优势就是可以对内置类型和自定义类型，都使用
	// 一样的方式，去流插入和流提取数据
	// 当然这里自定义类型Date需要重载>> 和 <<
	// istream& operator >> (istream& in, Date& d)
	// ostream& operator << (ostream& out, const Date& d)
	void WriteText(const ServerInfo& info)
	{
		ofstream ofs(_filename);
		ofs << info._address << " " << info._port << " " << info._date;
		//请注意，这里不能省略空格，不然>>流提取按照空格会读取混乱
	}
	void ReadText(ServerInfo& info)
	{
		ifstream ifs(_filename);
		ifs >> info._address >> info._port >> info._date;
	}
private:
	string _filename; // 配置文件
};


void test6()
{
	ofstream fp("newtest.txt");//后面用|的方式来增加写入方式
	//如果文件不存在，会创建该文件；若文件已存在，其内容会被清空。
	Date tmp(2025, 4, 13);
	//二进制方式
	fp.write(reinterpret_cast<const char*>(&tmp), sizeof(Date));
	//文本方式
	fp << tmp;
	//不需要手动关闭，因为可以析构

	ifstream ifs("test.cpp");
	char ch;
	while (ifs.get(ch))//这里返回值是istream又去调用operator bool
	{
		cout << ch;
	}
}

#include<sstream>

void test7()
{
	//如果将一个结构体放到字符串中打印，你会怎么做？
	Date d(2025, 4, 13);
	//string str = d; // 调用Date的operator string
	//在C语言中可以用sprintf来实现
	char arr[128] = { 0 };
	sprintf(arr,"%d %d %d", d._year, d._month, d._day);
	cout << arr << endl;
	//而在C++中可以用ostringstream来实现
	ostringstream oss;
	oss << d;
	cout << oss.str() << endl;//这是因为ostringstream中有一个字符串string，直接储存到str中
	//调用str函数就可以得到内部的字符串
	istringstream iss(oss.str());
	Date d1;
	iss >> d1;
	cout << d1._year << " " << d1._month << " " << d1._day << endl;
	//将字符串转换为Date对象
	stringstream ss;//但是stringstream可以同时支持输入和输出
	ss << d; // 
	cout << ss.str() << endl;	
	Date d2;
	ss >> d2; 
	cout << d2._year << " " << d2._month << " " << d2._day << endl;
}


int main()
{
	test7();
	return 0;
}
