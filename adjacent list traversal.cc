#include <iostream>
#include <forward_list>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
using Gragh = vector<forward_list<int>>;
void DFS(Gragh g)
{
	vector<bool> visitedVertex(g.size(),false);
	stack<int> s;
	for (int i = 0; i < g.size(); ++i)
	{
		if (!visitedVertex[i])
		{
			s.push(i);
			cout << "{ " <<s.top() << " ";
			visitedVertex[s.top()] = true;
			while (!s.empty())
			{
				while (!s.empty())
				{
					int temp = s.top();
					for (const auto&x : g[s.top()])
					{
						if (!visitedVertex[x])
						{
							s.push(x);
							cout << s.top() << " ";
							visitedVertex[s.top()] = true;
							break;
						}
					}
					if (s.top() == temp)s.pop();
					else { break; }
				}
			}
			cout << "}\n";
		}
	}
}
void BFS(Gragh g)
{
	vector<bool> visitedVertex(g.size(), false);
	queue<int> q;
	for (int i = 0; i < g.size(); ++i)
	{
		if (!visitedVertex[i])
		{
			q.push(i);
			cout << "{ ";
			while (!q.empty())
			{
				if(!visitedVertex[q.front()])cout << q.front()<<" ";
				visitedVertex[q.front()] = true;
				for (const auto&x : g[q.front()]) if (!visitedVertex[x])q.push(x);
				q.pop();
			}
			cout << "}\n";
		}
	}
}
int main()
{
	int vertexCount, edgeCount;
	cin >> vertexCount >> edgeCount;
	Gragh gragh(vertexCount);
	for (int i = 0; i < edgeCount; ++i)
	{
		int vertex1, vertex2;
		cin >> vertex1 >> vertex2;
		gragh[vertex2].push_front(vertex1);
		gragh[vertex1].push_front(vertex2);
	}
	DFS(gragh);
	BFS(gragh);
}
