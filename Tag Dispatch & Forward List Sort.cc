#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <list>
#include <forward_list>
using namespace std;
template<typename Iterator>
void Sort(Iterator begin, Iterator end,
	function<bool(typename  Iterator::value_type,
		typename  Iterator::value_type)> pred ,...)
{
	for(auto dist=--end;dist!=begin;--dist)
		for(auto i=begin;i!=dist;++i)
		{
			auto temp = i++;
			if (pred(*i, *temp))swap(*i, *temp);
			i = temp;
		}
}
template<typename Iterator>
void Sort(Iterator begin, Iterator end,
	function<bool(typename  Iterator::value_type,
		typename  Iterator::value_type)> pred, forward_iterator_tag)
{
	auto currentEnd = end;
	while (currentEnd != begin)
	{
		auto i = begin;
		while (true)
		{
			auto temp = i++;
			if (i == currentEnd)
			{
				currentEnd = temp;
				break;
			}
			if (pred(*i, *temp))swap(*i, *temp);
		}
	}
}
template<typename Iterator>
void BubbleSort(Iterator begin, Iterator end,
	function<bool(typename  Iterator::value_type,
		typename  Iterator::value_type)> pred = less<typename  Iterator::value_type>())
{
	Sort(begin, end, pred, iterator_traits<Iterator>::iterator_category());
}
int main(int argc, char* argv[])
{
	list<int> a{ 3,2,1,5,4 };
	BubbleSort(begin(a), end(a), [](int a, int b) { return a < b; });
	for (auto x : a) { cout << x; };
}
