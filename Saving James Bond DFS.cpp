#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
using namespace std;
using Point = pair<int, int>;
double Distance(Point lhs, Point rhs) { return sqrt(pow(lhs.first - rhs.first, 2) + pow(lhs.second - rhs.second, 2)); }
vector<vector<int>> gragh;
vector<int> shortestPath(200);
deque<bool> visited;
vector<Point> points;
int crocodileSize, jumpDistance;
void DFS(int fromIdx)
{
    static vector<int> path;
    if (path.size()>shortestPath.size())return;
    if (abs(points[fromIdx].first) + jumpDistance >= 50 || abs(points[fromIdx].second) + jumpDistance >= 50)
    {
        if (path.size()<shortestPath.size())shortestPath = path;
        return;
    }
    for (auto && toIdx : gragh[fromIdx])
    {
        if (!visited[toIdx])
        {
            path.push_back(toIdx);
            visited[toIdx] = true;
            DFS(toIdx);
            path.pop_back();
            visited[toIdx] = false;
        }
    }
}
int main(int argc, char* argv[])
{
    cin >> crocodileSize >> jumpDistance;
    gragh.resize(crocodileSize + 1);
    visited.resize(gragh.size());
    for (int i = 0; i < crocodileSize; ++i)
    {
        int x, y;
        cin >> x >> y;
        for (int j = 0; j < points.size(); ++j)
        {
            if (Distance(points[j], { x,y }) <= jumpDistance)
            {
                gragh[j].push_back(i);
                gragh[i].push_back(j);
            }
        }
        points.push_back({ x,y });
    }
    points.push_back({});
    const auto startIdx = gragh.size()-1;
    for (int i = 0; i < points.size(); ++i)
    {
        if (Distance(points[i], {}) <= 7.5 + jumpDistance)
        {
            gragh[startIdx].push_back(i);
            gragh[i].push_back(startIdx);
        }
    }
    sort(gragh[startIdx].begin(),gragh[startIdx].end(),
        [](int lhs,int rhs){return Distance(points[lhs], {}) < Distance(points[rhs], {});});
    visited[startIdx] = true;
    DFS(startIdx);
    if (shortestPath.size() == 200)cout << 0;
    else
    {
        cout << shortestPath.size()+1<<'\n';
        for (int i = 0; i < shortestPath.size(); ++i)
        {
            cout << points[shortestPath[i]].first << " " << points[shortestPath[i]].second << '\n';
        }
    }
}

