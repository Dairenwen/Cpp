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
		// ����������д�ģ���������_yearΪ0�������
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


//�ļ�����
void test5()
{
	Date tmp(2025, 4, 13);
	//��tmp�Զ�����д���ļ�
	FILE* fp1 = fopen("writein.txt", "wb");
	fwrite(&tmp, sizeof(Date), 1, fp1);
	fclose(fp1);
	//��tmp���ı���ʽд���ļ�
	string writein = tmp;
	FILE* fp2 = fopen("writein.txt", "a+");
	fputs(writein.c_str(), fp2);
	fclose(fp2);

	//��ôc++������δ�����أ�

}


struct ServerInfo
{
	char _address[32];
	int _port;
	//�����ƶ�д������string vector�����Ķ��������
	//��ע�ⲻ�ܴ���string��д�붼���ڴ��е����ݣ�����ַ�������16
	//д��Ľ����Ǵ洢���ڶ��Ͽռ�ĵ�ַ��������Ч�洢
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
	// C++�ļ��������ƾ��ǿ��Զ��������ͺ��Զ������ͣ���ʹ��
	// һ���ķ�ʽ��ȥ�����������ȡ����
	// ��Ȼ�����Զ�������Date��Ҫ����>> �� <<
	// istream& operator >> (istream& in, Date& d)
	// ostream& operator << (ostream& out, const Date& d)
	void WriteText(const ServerInfo& info)
	{
		ofstream ofs(_filename);
		ofs << info._address << " " << info._port << " " << info._date;
		//��ע�⣬���ﲻ��ʡ�Կո񣬲�Ȼ>>����ȡ���տո���ȡ����
	}
	void ReadText(ServerInfo& info)
	{
		ifstream ifs(_filename);
		ifs >> info._address >> info._port >> info._date;
	}
private:
	string _filename; // �����ļ�
};


void test6()
{
	ofstream fp("newtest.txt");//������|�ķ�ʽ������д�뷽ʽ
	//����ļ������ڣ��ᴴ�����ļ������ļ��Ѵ��ڣ������ݻᱻ��ա�
	Date tmp(2025, 4, 13);
	//�����Ʒ�ʽ
	fp.write(reinterpret_cast<const char*>(&tmp), sizeof(Date));
	//�ı���ʽ
	fp << tmp;
	//����Ҫ�ֶ��رգ���Ϊ��������

	ifstream ifs("test.cpp");
	char ch;
	while (ifs.get(ch))//���ﷵ��ֵ��istream��ȥ����operator bool
	{
		cout << ch;
	}
}

#include<sstream>

void test7()
{
	//�����һ���ṹ��ŵ��ַ����д�ӡ�������ô����
	Date d(2025, 4, 13);
	//string str = d; // ����Date��operator string
	//��C�����п�����sprintf��ʵ��
	char arr[128] = { 0 };
	sprintf(arr,"%d %d %d", d._year, d._month, d._day);
	cout << arr << endl;
	//����C++�п�����ostringstream��ʵ��
	ostringstream oss;
	oss << d;
	cout << oss.str() << endl;//������Ϊostringstream����һ���ַ���string��ֱ�Ӵ��浽str��
	//����str�����Ϳ��Եõ��ڲ����ַ���
	istringstream iss(oss.str());
	Date d1;
	iss >> d1;
	cout << d1._year << " " << d1._month << " " << d1._day << endl;
	//���ַ���ת��ΪDate����
	stringstream ss;//����stringstream����ͬʱ֧����������
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
