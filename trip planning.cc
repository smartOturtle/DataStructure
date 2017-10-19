#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;
using LengthPrice = pair<int, int>;
using Gragh = vector<vector<LengthPrice>>;
//O(1) get the value,O(logN) get the least pair
class Heap
{
	using key_type = int;
	using mapped_type = LengthPrice;	
	unordered_map<key_type, mapped_type> container_;
	using value_type = decltype(container_)::value_type;
	using reference_type = reference_wrapper<value_type>;
	function<bool(const value_type&, const value_type&)> cmp_
	{ [](const value_type&one,const value_type& other) 
		{ return greater<mapped_type>{}(one.second,other.second); } };
	priority_queue<reference_type, vector<reference_type>, decltype(cmp_)> heap_{cmp_};
public:
	void Push(value_type weight)
	{
		heap_.push( *container_.insert(weight).first);
	}
	const value_type& Pop()
	{
		const auto x = heap_.top();
		heap_.pop();
		return x;
	}
	const value_type& Peek() const { return heap_.top(); }
	bool Empty() const { return heap_.empty(); }
	mapped_type& operator [](key_type index) {return container_.at(index);}
};
LengthPrice dijkstra(Gragh g,int start,int destination)
{
	Heap dist;
	for (int i = 0; i < g.size(); ++i)
	{
		dist.Push({ i,g[start][i] });
	}
	vector<bool> collected(g.size(),false);
	while(!dist.Empty())
	{
		const auto temp = dist.Pop().first;
		collected[temp] = true;
		for (int i = 0;  i< g.size(); i++)
			if(g[temp][i].first<INT16_MAX&&!collected[i]
				&&dist[i].first > dist[temp].first + g[temp][i].first
				|| (dist[i].first == dist[temp].first + g[temp][i].first
				&&dist[i].second>dist[temp].second + g[temp][i].second))
				{
					dist[i].first = dist[temp].first + g[temp][i].first;
					dist[i].second = dist[temp].second + g[temp][i].second;
				}
	}
	return dist[destination];
}
int main()
{
	int citySize, edgeSize, begin, end;
	cin >> citySize >> edgeSize >> begin >> end;
	Gragh gragh(citySize, vector<pair<int, int>>(citySize, { INT16_MAX,INT16_MAX }));
	for (int i = 0; i < citySize; ++i)gragh[i][i] = {};
	for (int i = 0; i < edgeSize; ++i)
	{
		int city1, city2, length, price;
		cin >> city1 >> city2 >> length >> price;
		gragh[city1][city2] = { length,price };
		gragh[city2][city1] = { length,price };
	}
	auto x = dijkstra(gragh, begin, end);
	cout << x.first << " " << x.second;
}
