#include <iostream>
#include <functional>
#include <vector>
#include <iterator>
#include <list>
using namespace std;
template<typename BidIter>
constexpr auto Prev(BidIter iter) { return --iter; }
template<typename BidIter>
constexpr auto Next(BidIter iter) { return ++iter; }
template<typename RandIter>
constexpr auto ShiftAux(RandIter iter, int N,random_access_iterator_tag) 
{ return iter + N; }
template <typename BidIter>
auto ShiftAux(BidIter iter,int N,bidirectional_iterator_tag)
{
	bool isNagative = false;
	if (N < 0) { isNagative = true; N = -N; }
	if (isNagative)for (int i = 0; i < N; ++i)--iter;
	else for (int i = 0; i < N; ++i)++iter;
	return iter;
}
template <typename BidIter>
constexpr  BidIter Shift(BidIter iter,int N)
{
	return ShiftAux(iter,N,typename iterator_traits<BidIter>::iterator_category());
}
template <typename BidIter>
void InsertionSort(BidIter begin, BidIter end)
{
	for (auto i = begin; i != end; ++i)
	{
		auto temp = *i;
		auto j = i;
		for (; j != begin && temp < *Prev(j); --j)
			*j = *Prev(j);
		*j = temp;
	}
}
template<typename RandIter>
void QuickSort(RandIter begin, RandIter end)
{
	using Func = function<void(RandIter, RandIter)>;
	Func Median3 =
		[](RandIter begin, RandIter end)
	{
		auto mid = Shift(begin,distance(begin,end) / 2);
		if (*begin > *mid)swap(*begin, *mid);
		if (*begin > *Prev(end))swap(*begin, *Prev(end));
		if (*mid > *Prev(end))swap(*mid, *Prev(end));
		swap(*Shift(end, -2), *mid);
		return *Shift(end, -2);
	};
	function<RandIter(RandIter, RandIter)> Partition =
		[&Median3](RandIter begin, RandIter end)
	{
		Median3(begin, end);
		auto i = begin, j = Shift(end, -2);
		auto pivot = *j;
		while (true)
		{
			while (*++i < pivot) { if (i == j)break; }
			if(i==j)break;
			while (*--j > pivot) { if (i == j)break; }
			if (i == j)break;
			swap(*i, *j);
		}

		swap(*i, *Shift(end, -2));
		return i;
	};
	Func Sort = [&Partition, &Sort](RandIter begin, RandIter end)
	{
		if (distance(begin,end) < 11) { InsertionSort(begin, end); return; }
		auto pivot = Partition(begin, end);
		Sort(begin, pivot);
		Sort(Next(pivot), end);
	};
	Sort(begin, end);
}
int main()
{
	vector<int> a;
	for (int i = 0; i < 10100000; ++i)a.push_back(-i);
	//QuickSort(a.begin(), a.end());
	/*for (auto value : a)
	{
		cout << value << " ";
	}*/
}
