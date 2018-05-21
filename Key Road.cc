#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
using namespace std;
int main(int argc, char* argv[])
{
    int vertexSize, edgeSize;
    cin >> vertexSize >> edgeSize;
    vector<int> indegree(vertexSize);
    vector<vector<int>> outEdges(vertexSize);
    vector<vector<int>> inEdges(vertexSize);
    map<pair<int, int>, int> edgeWeights;
    for (int i = 0; i < edgeSize; ++i)
    {
        int from, to, weight;
        cin >> from >> to >> weight;
        from--, to--;
        outEdges[from].push_back(to);
        inEdges[to].push_back(from);
        indegree[to]++;
        edgeWeights[{from, to}] = weight;
    }
    queue<int> q;
    for (int i = 0; i < vertexSize; ++i)if (indegree[i] == 0)q.push(i);
    vector<int> earliest(vertexSize);
    vector<int> latest(vertexSize, INT16_MAX);
    for (int cnt = 0;; ++cnt)
    {
        if (q.empty())
        {
            if (cnt < vertexSize) { cout << "0"; return 0; }
            auto maxElem = max_element(earliest.begin(), earliest.end());
            latest[maxElem - earliest.begin()] = *maxElem;
            q.push(maxElem - earliest.begin());
            cout << *maxElem << '\n';
            break;
        }
        for (auto idx : outEdges[q.front()])
        {
            earliest[idx] = max(earliest[idx], earliest[q.front()] + edgeWeights[{q.front(), idx}]);
            indegree[idx]--;
            if (indegree[idx] == 0)q.push(idx);
        }
        q.pop();
    }
    while (!q.empty())
    {
        for (auto idx : inEdges[q.front()])
        {
            latest[idx] = min(latest[idx], latest[q.front()] - edgeWeights[{idx, q.front()}]);
            q.push(idx);
        }
        q.pop();
    }
    for (int from = 0; from < outEdges.size(); ++from)
    {
        reverse(outEdges[from].begin(), outEdges[from].end());
        for (auto to : outEdges[from])
        {
            if (latest[to] - earliest[from] - edgeWeights[{from, to}] == 0)
                cout << from + 1 << "->" << to + 1 << '\n';
        }
    }
}
