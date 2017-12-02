#include <iostream>
#include <functional>
#include <iterator>
#include <list>
#include <vector>
using namespace std;
template<typename Iterator>
constexpr  Iterator NextPosition(Iterator iter) { return ++iter; }
template<typename Iterator>
constexpr  Iterator PrevPosition(Iterator iter) { return --iter; }
template<typename Iterator>
constexpr  Iterator Offset(Iterator iter, int offset) { advance(iter, offset); return iter; }
template<typename Iterator>
void ShellSort(Iterator begin, 
	       Iterator end,
	       function<bool(typename  Iterator::value_type,
		             typename  Iterator::value_type)> pred = 
	                     less<typename Iterator::value_type>())
{
	int k = 1,dist=distance(begin,end);
	while (k * 3 < dist)k = k * 3 + 1;
	while (k>=1)
	{
		int j=k;
		for (auto p = Offset(begin,k); j+k<=dist; advance(p,k),j+=k)
		{
			int x = j;
			auto Tmp = *p;
			auto i = p;
			for (; x>=k &&*Offset(i,-k)>Tmp; advance(i, -k),x-=k)
				*i = *Offset(i, -k);
			*i = Tmp;
		}
		k /= 3;
	}
}
int main(int argc, char* argv[])
{
	int size;
	cin >> size;
	vector<int> container;
	container.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		int data;
		cin >> data;
		container.push_back(data);
	}
	ShellSort(container.begin(), container.end());
	cout << container.front();
	for (auto iter = ++container.begin(); iter != container.end(); ++iter)
	{
		cout << " " << *iter;
	}
}
