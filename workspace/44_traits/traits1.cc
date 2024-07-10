#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>

using namespace std;

template<typename T>
struct my_is_pointer {
    static const bool value = false;
};

template<typename T>
struct my_is_pointer<T*> {
    static const bool value = true;
};

template<typename T>
typename T::value_type top(const T &c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}

template<class IterT>
struct my_iterator_traits {
    typedef typename IterT::value_type value_type;
};

template<class IterT>
struct my_iterator_traits<IterT*> {
    typedef IterT value_type;
};

void fun(int a) {
    cout << "fun(int) is called" << endl;
}

void fun(double a) {
    cout << "fun(double) is called" << endl;
}

void fun(char a) {
    cout << "fun(char) is called" << endl;
}

int main()
{
	my_is_pointer<int> p1;
	cout << p1.value << endl;  // 输出 0，使用原始模板
	my_is_pointer<int*> p2;
	cout << p2.value << endl;  // 输出 1，使偏特化模板，因为指定了 int * 类型的参数

	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	cout << top<vector<int> >(vec) << endl;  // 输出3

	vector<int> vec2;
	cout << top<vector<int> >(vec2) << endl;  // 输出3

	my_iterator_traits<vector<int>::iterator>::value_type a;
	fun(a);  // 输出 fun(int) is called
	my_iterator_traits<vector<double>::iterator>::value_type b;
	fun(b);  // 输出 fun(double) is called
	my_iterator_traits<char*>::value_type c;
	fun(c);  // 输出 fun(char) is called

	return 0;
}
