#include"template.hpp"

template<class T, class Container>
void test::stack<T, Container>::push(const T& t)
{
	_con.push_back(t);
}

template<class T, class Container>
void test::stack<T, Container>::pop()
{
	_con.pop_back();
}
//
//template
//class test::stack<int>;
//
//template
//class test::stack<double>;
//�����﷨�涨����ǰ����ʵ�����Ϳ����ˣ����ǲ�ͬ����Ҫ����һ��ʵ�������鷳
//������һ�ַ���������ֱ����ͷ�ļ��н��������Ͷ��壬�������Է���ǰ��
//Ҳ����ֱ��ʹ��hpp�ĺ�׺�������ļ�����ò�Ҫ��.h�ĺ�׺

