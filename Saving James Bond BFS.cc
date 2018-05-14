#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
using Point = pair<int, int>;
using Gragh = vector<vector<int>>;
double GetDistance(Point p1, Point p2={})
{
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
stack<int> bfs(const Gragh& g)
{
	vector<int> dist(g.size(), -1);
	dist[0] = 0;
	queue<int> q;
	q.push(0);
	vector<int> path(g.size(), -1);
	while (!q.empty())
	{
		for (int i=0;i<g[q.front()].size();i++)
		{
			if (g[q.front()][i] == 1&&dist[i]==-1)
			{
				dist[i] = dist[q.front()] + 1;
				path[i] = q.front();
				q.push(i);
			}
		}
		q.pop();
	}
	stack<int> s;
	for (int i = path[g.size() - 1]; i >0; i = path[i]) { s.push(i);  }
	return s;
}
int main()
{
	const Point origin{ 0,0 };
	const auto diameter = 15;
	int vertexCount, stepSize;
	cin >> vertexCount >> stepSize;
	vector<Point> container{origin};
	container.reserve(vertexCount + 1);
	Gragh gragh(vertexCount+2,vector<int>(vertexCount+2,0));
	for (int i = 1; i < vertexCount+1; ++i)
	{
		int x, y;
		cin >> x >> y;
		container.push_back({ x,y });
	}
	sort(container.begin(), container.end(), [](Point p1, Point p2) { return GetDistance(p1) < GetDistance(p2); });
	for (int i = 1; i < container.size(); ++i)
		for (int j = 1; j < container.size(); ++j)
			if (i != j&&GetDistance(container[i], container[j]) <= stepSize) { gragh[i][j] = 1; gragh[j][i] = 1; }
	for (auto i = 1; i <container.size(); ++i)
		if (GetDistance(container[i],origin) <= diameter/2.0+stepSize)
		{
			gragh[0][i] = 1;
			gragh[i][0]=1;
		}
	if ((stepSize + diameter/2.0) >= 50)gragh[0].back() = 1;
	else for (int i = 1; i < container.size(); ++i)
	{
		if (max(abs(container[i].first), abs(container[i].second)) + stepSize >= 50)gragh[i].back() = 1;
	}
	if (gragh[0].back() == 1)cout << 1;
	else
	{
		auto s = bfs(gragh);
		int k = -1;
		if (!s.empty())k = s.top();
		if (k == -1)cout << 0;
		else
		{
			cout << s.size() + 1 << endl;
			while (!s.empty())
			{
				cout << container[s.top()].first << " " << container[s.top()].second << endl;
				s.pop();
			}
		}
	}
}
