#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <unordered_map>
using namespace std;
using Gragh = vector<vector<pair<int,int>>>;
//O(1) get the value,O(logN) get the least pair
class Heap
{
	using key_type = int;
	//first is length,second is price
	using mapped_type = pair<int,int>;	
	unordered_map<key_type, mapped_type> container_;
	using value_type = decltype(container_)::value_type;
	using reference_type = reference_wrapper<value_type>;
	priority_queue<reference_type, vector<reference_type>, greater<value_type>> heap_;
public:
	explicit Heap(){}
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
	value_type Peek() const { return heap_.top(); }
	bool Empty() const { return heap_.empty(); }
	mapped_type& operator [](key_type index) {return container_.at(index);}
};
pair<int,int> dijkstra(Gragh g,int begin,int end)
{
	Heap dist;
	for (int i = 0; i < g.size(); ++i)
	{
		dist.Push({ i,g[begin][i] });
	}
	vector<bool> collected(g.size(),false);
	while(!dist.Empty())
	{
		const auto temp = dist.Pop().first;
		collected[temp] = true;
		for (int i = 0;  i< g.size(); i++)
		{
			if(g[temp][i].first<INT16_MAX&&!collected[i])
			{
				if (dist[i].first > dist[temp].first + g[temp][i].first
					||dist[i].first==dist[temp].first + g[temp][i].first
					&&dist[i].second>dist[temp].second + g[temp][i].second)
				{
					dist[i].first = dist[temp].first + g[temp][i].first;
					dist[i].second = dist[temp].second + g[temp][i].second;
				}
			}
		}
	}
	return dist[end];
}
int main()
{
	int citySize,edgeSize,begin,end;
	cin >> citySize >> edgeSize >> begin >> end;
	Gragh gragh(citySize,vector<pair<int,int>>(citySize,{INT16_MAX,INT16_MAX}));
	for (int i = 0; i < citySize; ++i)gragh[i][i] = {};
	for (int i = 0; i < edgeSize; ++i)
	{
		int city1, city2, length, price;
		cin >> city1 >> city2 >> length >> price;
		gragh[city1][city2] = {length,price};
		gragh[city2][city1] = {length,price};
	}
	auto x = dijkstra(gragh, begin, end);
	cout << x.first << " " << x.second;
}
