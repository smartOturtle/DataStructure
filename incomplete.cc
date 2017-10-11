#include <iostream>
#include <list>
#include <vector>
using namespace std;
using Gragh = vector<list<int>>;
Gragh gragh;
vector<bool> vertexBox;
void six_degrees_search(int i,int layer)
{
	if(layer==6)return;
	for (const auto& x : gragh[i])
	{
		vertexBox[x] = true;
		if(x!=i)six_degrees_search(x, layer + 1);
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
		gragh[one-1].push_back(other-1);
		gragh[other - 1].push_back(one - 1);
	}
	for (int i = 0; i < vertexCount; ++i)
	{
		int relationCount=0;
		six_degrees_search(i, 0);
		for(auto x:vertexBox)
		{
			if (x)relationCount++;
		}
		printf("%d: %.2lf%%\n", i+1,100.0*relationCount / vertexCount);
		for (int j = 0; j < vertexBox.size(); ++j)
		{
			vertexBox[j] = false;
		}
	}
}
