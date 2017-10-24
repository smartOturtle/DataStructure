#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

struct Set
{
	bool Union(int i,int j)
	{
		int rootI = Find(i), rootJ = Find(j);
		if (rootI == rootJ)return false;
		if (set[rootI] < set[rootJ])
		{
			set[rootJ] += set[rootI];
			set[rootI] = rootJ;
		}
		else
		{
			set[rootI] += set[rootJ];
			set[rootJ] = rootI;
		}
		return true;
	}
	int Find(int i)
	{
		if (set[i] < 0)return i;
		return  set[i]= Find(set[i]);
	}
	vector<int> set;
};
using Edge = pair<int, pair<int, int>>;
priority_queue<Edge,vector<Edge>,greater<Edge>> heap;
int Kruskal(int villageCount)
{
	int cnt{},totalPrice{};
	Set s;
	s.set.assign(villageCount, -1);
	while (cnt<villageCount-1&&!heap.empty())
	{
		auto indexPair = heap.top().second;
		if (s.Union(indexPair.first, indexPair.second))
		{
			cnt++;
			totalPrice += heap.top().first;
		}
		heap.pop();
	}
	if (cnt < villageCount - 1)return -1;
	return totalPrice;
}
int main(int argc, char* argv[])
{
	int villageCount, roadCount;
	cin >> villageCount >> roadCount;
	for (int i = 0; i < roadCount; ++i)
	{
		int x, y, weight;
		cin >> x >> y >> weight;
		heap.push({ weight,{x-1,y-1} });
	}
	cout << Kruskal(villageCount);
}
