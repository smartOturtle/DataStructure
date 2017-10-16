#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;
using Point = pair<int, int>;
using Gragh = vector<list<Point>>;
double GetDistance(const Point& p1, const Point& p2)
{
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
int GetIndex(const Gragh& g, const Point& p)
{
	for (int i = 0; i < g.size(); ++i)
	{
		if (g[i].front() == p)return i;
	}
	cout << "error";
	return -1;
}
void BFS(const Gragh& g, int stepSize)
{
	vector<bool> visitedVertex(g.size(), false);
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		const auto& p = g[q.front()].front();
		if (max(abs(p.first), abs(p.second)) + stepSize >= 50) { cout << "Yes"; return; }
		visitedVertex[q.front()] = true;
		for (const auto&x : g[q.front()])if (!visitedVertex[GetIndex(g, x)])q.push(GetIndex(g, x));
		q.pop();
	}
	cout << "No";
}
int main()
{
	const Point origin{ 0,0 };
	const int diameter = 15;
	int vertexCount, stepSize;
	cin >> vertexCount >> stepSize;
	Gragh gragh(vertexCount);
	for (int i = 0; i < vertexCount; ++i)
	{
		int x, y;
		cin >> x >> y;
		gragh[i].push_back({ x,y });
		for (auto& iter : gragh)
		{
			if (iter.empty())break;
			if (iter != gragh[i] && GetDistance(gragh[i].front(), iter.front()) <= stepSize)
			{
				iter.push_back(gragh[i].front());
				gragh[i].push_back(iter.front());
			}
		}
	}
	gragh.push_back(list<Point>(1, origin));
	for (int i = 0; i < vertexCount; ++i)
	{
		if (GetDistance(gragh[i].front(), {}) <= stepSize + diameter)
		{
			gragh[vertexCount].push_back(gragh[i].front());
			gragh[i].push_back(origin);
		}
	}
	gragh[vertexCount].swap(gragh[0]);
	BFS(gragh, stepSize);
}
