#include <iostream>
#include <functional>
#include <vector>
using namespace std;
template<typename BidIter>
constexpr auto Prev(BidIter iter,int N=1)
{
	--iter;
	if (N == 1)return iter;
	return Prev(iter,N-1);
}
template<typename BidIter>
constexpr auto Next(BidIter iter) { return ++iter; }
template <typename BidIter>
void InsertionSort(BidIter begin, BidIter end)
{
	for (auto i = begin; i != end; ++i)
	{
		auto temp = *i;
		auto j = i;
		for (; j != begin && temp < *Prev(j); --j)//尽量写无副作用函数
			*j = *Prev(j);
		*j = temp;
	}
}
template<typename RandIter>
void QuickSort(RandIter begin,RandIter end)
{
	using Func = function<void(RandIter, RandIter)>;
	Func Median3 = 
	[](RandIter begin, RandIter end)
	{
		auto mid = begin + (end - begin) / 2;
		if (*begin > *mid)swap(*begin, *mid);
		if (*begin > *Prev(end))swap(*begin, *Prev(end));
		if (*mid > *Prev(end))swap(*mid, *Prev(end));
		swap(*(end - 2), *mid);
		return *(end - 2);
	};
	function<RandIter(RandIter, RandIter)> Partition = 
	[&Median3](RandIter begin, RandIter end)
	{
		Median3(begin, end);
		auto i = begin, j = end - 2;
		auto pivot =*j;
		while (i<j)
		{
			while (*++i < pivot) {  }
			while (*--j > pivot) {  }
			if (i < j)swap(*i, *j);
		}
		swap(*i, *(end - 2));
		return i;
	};
	Func Sort = [&Partition,&Sort](RandIter begin, RandIter end)
	{
		if (end - begin < 11) { InsertionSort(begin, end); return; }
		auto pivot= Partition(begin, end);
		Sort(begin, pivot);
		Sort(pivot + 1, end);
	};
	Sort(begin, end);
}
int main()
{
	vector<int> a;
	for (int i = 0; i < 101; ++i)a.push_back(-i);
	QuickSort(a.begin(), a.end());
	for (auto value : a)
	{
		cout << value << " ";
	}
}
