#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;
using Gragh = vector<list<int>>;
Gragh gragh;
vector<bool> vertexBox;
void bfs(int i)
{
	int layer = 0, last = i;
	queue<int> q;
	q.push(i);
	vertexBox[i] = true;
	while (layer<6&&!q.empty())
	{
		for (const auto& x : gragh[q.front()])
		{
			if (!vertexBox[x])
			{
				vertexBox[x] = true;
				q.push(x);
			}
		}
		if (q.front() == last)
		{
			layer++;
			last = q.back();
		}
		q.pop();
	}
}
int main()
{
	int vertexCount, edgeCount;
	cin >> vertexCount >> edgeCount;
	gragh.resize(vertexCount);
	vertexBox.resize(vertexCount);
	for (int i = 0; i < edgeCount; ++i)
	{
		int one, other;
		cin >> one >> other;
		gragh[one - 1].push_back(other - 1);
		gragh[other - 1].push_back(one - 1);
	}
	for (int i = 0; i < vertexCount; ++i)
	{
		bfs(i);
		int relationCount = 0;
		for (auto x : vertexBox)
		{
			if (x)relationCount++;
		}
		printf("%d: %.2lf%%\n", i + 1, 100.0*relationCount / vertexCount);
		for (int j = 0; j < vertexBox.size(); ++j)
		{
			vertexBox[j] = false;
		}
	}
}
