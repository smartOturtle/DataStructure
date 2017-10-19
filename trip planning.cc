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
	priority_queue<reference_type, vector<reference_type>, greater<value_type>> heap_;
public:
	void Push(value_type weight)
	{
		heap_.push( *container_.insert(weight).first);
	}
	value_type& Pop()
	{
		const auto x = heap_.top();
		heap_.pop();
		return x;
	}
	value_type& Peek() const { return heap_.top(); }
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
				|| dist[i].first == dist[temp].first + g[temp][i].first
				&&dist[i].second>dist[temp].second + g[temp][i].second)
				{
					dist[i].first = dist[temp].first + g[temp][i].first;
					dist[i].second = dist[temp].second + g[temp][i].second;
				}
	}
	return dist[destination];
}
int main()
{
	int cityCount,roadCount,start,destination;
	cin >> cityCount >> roadCount >> start >> destination;
	Gragh gragh(cityCount,vector<pair<int,int>>(cityCount,{INT16_MAX,INT16_MAX}));
	for (auto i = 0; i < cityCount; ++i)gragh[i][i] = {};
	for (auto i = 0; i < roadCount; ++i)
	{
		int city1, city2, length, price;
		cin >> city1 >> city2 >> length >> price;
		gragh[city1][city2] = {length,price};
		gragh[city2][city1] = {length,price};
	}
	const auto x = dijkstra(gragh, start, destination);
	cout << x.first << " " << x.second;
}
