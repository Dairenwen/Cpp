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
//这是语法规定，提前进行实例化就可以了，但是不同对象都要进行一次实例化很麻烦
//建议另一种方法，就是直接在头文件中进行声明和定义，声明可以放在前面
//也可以直接使用hpp的后缀来命名文件，最好不要用.h的后缀

