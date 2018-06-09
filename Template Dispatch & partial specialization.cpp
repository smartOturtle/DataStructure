#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <type_traits>
using namespace std;

template<typename T>
void DispatchAux(T t,true_type,...)
{
	cout << "float";
}
template<typename T>
void DispatchAux(T t,false_type,true_type)
{
	cout << "int";
}
template<typename T>
void Dispatch(T t)
{
	static_assert(is_floating_point_v<T> || is_same_v<T, int>,
		"Only support floating point and int");
	DispatchAux(t, is_floating_point<T>(), is_same<T, int>());
}
template<typename T,typename Enable=void>
class Foo
{
public:
	Foo() { cout << "default"; }

};
template<typename T>
class Foo<T, enable_if_t<is_same_v<int, T>>>
{
public:
	Foo() { cout << "int"; }
};
template<typename T>
class Foo<T, enable_if_t<is_same_v<double, T>>>
{
public:
	Foo() { cout << "double"; }
};
template<typename T>
decltype(auto) Func(T a)
{
    if constexpr (is_floating_point_v<T>) return 1;
    else if constexpr (is_same_v<long, T>)return 2;
    return 3;
}
int main(int argc, char* argv[])
{
	Foo<int> a;
	Foo<float> b;
	Foo<double> c;
}
