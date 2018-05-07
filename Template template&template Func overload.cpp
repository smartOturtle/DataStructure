#define  _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <functional>
#include <iostream>
#include <list>
template<typename T,
    template<typename E, typename Alloc = std::allocator<E>> class Cont = std::vector>
void Func(Cont<T>& a)
{
    for (auto && value : a)
    {
        std::cout << value;
        value = 2;
    }
}
template<typename T,
    template<typename E, typename Alloc = std::allocator<E>> class Cont = std::vector>
void Func(Cont<std::reference_wrapper<T>>& a)
{
    for (T& value : a)
    {
        std::cout << value;
        value = 3;
    }
    for (T& value : a)
    {
        std::cout << value;
        value = 3;
    }
}
int main(int argc, char* argv[])
{
    std::list<int> a{1,2,3};
    std::vector<std::reference_wrapper<int>> b(a.begin(), a.end());
    Func(a);
    Func(b);
    Func(a);
}
