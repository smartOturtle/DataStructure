#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;
template<typename T>
using Gragh = vector<list<T>>;
Gragh<int> inGragh;
using act = pair<int, int>;
Gragh<act> outGragh;
void KeyRoad(Gragh<int> in,Gragh<act> out,vector<int> earlist)
{
	queue<int> q;
	int maxTime{}, ending{};
	vector<int> latest(in.size(), -1);//the -1 is the initial and must be assigned
	for (int i = 0; i < earlist.size(); ++i)
		if (maxTime < earlist[i])
		{
			maxTime = earlist[i];
			ending = i;
		}
	latest[ending] = maxTime;
	q.push(ending);
	while (!q.empty())
	{
		for (auto i : in[q.front()])
		{
			q.push(i);
			using value_type = decltype(out)::value_type::value_type;
			auto x = *find_if(out[i].begin(), out[i].end(), [&q](value_type one) { return one.first == q.front(); });
			if (latest[i] == -1 || latest[i] >latest[q.front()] - x.second)latest[i] = latest[q.front()] - x.second;//key point
		}
		q.pop();
	}
	cout << maxTime << endl;
	for (int i = 0; i < in.size(); ++i)
		for (auto iter = out[i].rbegin(); iter != out[i].rend(); ++iter)
		{
			auto const j = *iter;
			if ((latest[j.first] - earlist[i] - j.second) == 0)cout << i + 1 << "->" << j.first + 1 << endl;//key point
		}
}
void TopSort(Gragh<int> in, Gragh<act> out)
{
	queue<int> q;
	int cnt{};
	for (int i = 0; i < in.size(); ++i)
		if (in[i].empty())q.push(i);
	vector<int> earlist(in.size());
	while (!q.empty())
	{
		for (auto x : out[q.front()])
		{
			auto& inList = in[x.first];
			using value_type = decltype(in)::value_type::value_type;
			inList.erase(find_if(inList.begin(), inList.end(), [&q](value_type one) { return one == q.front(); }));
			if (inList.empty())q.push(x.first);
			if (earlist[x.first] < x.second + earlist[q.front()])earlist[x.first] = x.second + earlist[q.front()];
		}
		q.pop();
		++cnt;
	}
	if (cnt < in.size())cout << "0";
	else KeyRoad(inGragh, outGragh, earlist);
	
}
int main(int argc, char* argv[])
{
	int pointCount, actCount;
	cin >> pointCount >> actCount;
	inGragh.resize(pointCount);
	outGragh.resize(pointCount);
	for (int i = 0; i < actCount; ++i)
	{
		int start, ending, duration;
		cin >> start >> ending >> duration;
		inGragh[ending-1].push_back(start-1);
		outGragh[start-1].push_back({ ending-1,duration });
	}
	TopSort(inGragh,outGragh);
}
