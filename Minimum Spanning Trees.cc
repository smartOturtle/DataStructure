#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <functional>
using namespace std;

struct UnionFindSet
{
    int Find(int idx)
    {
        if (container_[idx] < 0)return idx;
        return container_[idx] = Find(container_[idx]);
    }
    void Connect(int lhs,int rhs)
    {
        auto lhsRoot = Find(lhs), rhsRoot = Find(rhs);
        if(lhsRoot==rhsRoot)return;
        if (lhsRoot > rhsRoot)swap(lhsRoot, rhsRoot);
        container_[lhsRoot] += container_[rhsRoot];
        container_[rhsRoot] = lhsRoot;
    }
    bool IsConnected(int lhs,int rhs)
    {
        auto lhsRoot = Find(lhs), rhsRoot = Find(rhs);
        return lhsRoot == rhsRoot;
    }
    int ConnectedSetSize()const
    {
        return count_if(container_.begin(), container_.end(), 
            [](int value) { return value < 0; });
    }
    explicit UnionFindSet(int size):container_(size,-1){}
    vector<int> container_;
};

struct Road
{
    int from;
    int to;
    int cost;
    Road(int from,int to,int cost):from(from),to(to),cost(cost){}
    bool operator<(const Road& road)const { return cost < road.cost; }
};
int main(int argc, char* argv[])
{
    int villageSize, edgeSize;
    cin >> villageSize >> edgeSize;
    vector<Road> roads;
    for (int i = 0; i < edgeSize; ++i)
    {
        int from, to, cost;
        cin >> from >> to >> cost;
        roads.emplace_back(from-1, to-1, cost);
    }
    sort(roads.begin(), roads.end());
    UnionFindSet ufset(villageSize);
    int totalCost=0;
    for (auto road : roads)
    {
        if (!ufset.IsConnected(road.from, road.to))
        {
            ufset.Connect(road.from, road.to);
            totalCost += road.cost;
        }
    }
    if (ufset.ConnectedSetSize() != 1)cout << -1;
    else { cout << totalCost; }
}
