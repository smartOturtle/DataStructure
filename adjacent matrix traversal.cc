#include <iostream>
#include <forward_list>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
using Gragh = vector<vector<int>>;//邻接矩阵与邻接表遍历的结果是不一样的
void DFS(Gragh& g)
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
					for (int j = 0; j < g[s.top()].size(); ++j)
					{
						if (g[s.top()][j] && !visitedVertex[j])
						{
							s.push(j);
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
void BFS(Gragh& g)
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
				for (int j = 0; j < g[q.front()].size(); ++j)
				{
					if (g[q.front()][j] && !visitedVertex[j])q.push(j);
				}
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
	Gragh gragh(vertexCount,vector<int>(vertexCount));
	for (int i = 0; i < edgeCount; ++i)
	{
		int vertex1, vertex2;
		cin >> vertex1 >> vertex2;
		gragh[vertex2][vertex1]=1;
		gragh[vertex1][vertex2]=1;
	}
	DFS(gragh);
	BFS(gragh);
}
