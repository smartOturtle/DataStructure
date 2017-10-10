#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <queue>
using namespace std;
using Point = pair<int, int>;
using Gragh = vector<list<Point>>;
double GetDistance(Point p1, Point p2)
{
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}
int getIndex(Gragh g,const Point& p)
{
	for (int i = 0; i < g.size(); ++i)
	{
		if (g[i].front() == p)return i;
	}
	cout << "error";
	return -1;
}
void BFS(Gragh g,int stepSize)
{
	vector<bool> visitedVertex(g.size(), false);
	queue<int> q;
	q.push(0);
	while (!q.empty())
	{
		Point& p = g[q.front()].front();
		if (max(abs(p.first), abs(p.second)) + stepSize >= 50) { cout << "Yes"; return; }
		visitedVertex[q.front()] = true;
		for (const auto&x : g[q.front()])if (!visitedVertex[getIndex(g, x)])q.push(getIndex(g, x));
		q.pop();
	}
	cout << "No";
}
int main()
{
	const Point origin{ 0,0 };
	const int diameter = 15;
	int vertexCount,stepSize;
	cin >> vertexCount>>stepSize ;
	Gragh gragh(vertexCount);
	for (int i = 0; i < vertexCount; ++i)
	{
		int x, y;
		cin >> x >> y;
		gragh[i].push_back({ x,y });
		for(auto& iter:gragh)
		{
			if(iter.empty())break;
			if(iter!=gragh[i]&&GetDistance(gragh[i].front(),iter.front())<=stepSize)
			{
				iter.push_back(*gragh[i].begin());
				gragh[i].push_back(*iter.begin());
			}
		}
	}
	gragh.push_back(list<Point>(1));
	for (int i = 0; i < vertexCount; ++i)
	{
		if(GetDistance(gragh[i].front(),{})<=stepSize+diameter)
		{
			gragh[vertexCount].push_back(gragh[i].front());
			gragh[i].push_back(origin);
		}
	}
	gragh[vertexCount].swap(gragh[0]);
	BFS(gragh, stepSize);
}
//forward_list 只有头结点所以只能以O(1)时间插在头节点后方而无法插在最后
