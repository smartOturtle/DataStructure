#include <iostream>
#include <vector>
#include <list>
#include <stack>
using namespace std;
struct Node
{
	list<int> left{};
	list<int> right{};
	int data;
	Node(int d):data(d){}
};
vector<Node> inorder;
vector<int> postorder;
int FindInorderIdx(const int postorderIdx)
{
	for (int i = 0; i < inorder.size(); ++i)
	{
		if(inorder[i].data==postorder[postorderIdx])return i;
	}
	return -1;
}
void Input()
{
	int size;
	cin >> size;
	for (int i = 0; i < size; ++i)
	{
		int data;
		cin >> data;
		postorder.push_back(data);
	}
	for (int i = 0; i < size; ++i)
	{
		int data;
		cin >> data;
		inorder.push_back(data);
	}
}
void Travelsal(const Node& n)
{
	cout << " " << n.data;
	if (!n.left.empty())Travelsal(inorder[n.left.front()]);
	if (!n.right.empty())Travelsal(inorder[n.right.front()]);
}
int main()
{
	Input();	
	stack<int> prevIdxs;
	auto idx = FindInorderIdx(inorder.size() - 1);
	for (int i = 0; i < inorder.size(); ++i)
	{
		if (i < idx)inorder[idx].left.push_back(i);
		else if(i>idx) inorder[idx].right.push_back(i);
	}
	prevIdxs.push(idx);
	for (int i = inorder.size() - 2; i >= 0; --i)
	{
		idx = FindInorderIdx(i);
		list<int>* nodes;
		while(true)
		{
			const auto& top = prevIdxs.top();
			if (idx < top)nodes = &inorder[top].left;
			else nodes = &inorder[top].right;
			if (nodes->empty() || (nodes->front()>idx || nodes->back()<idx))
				prevIdxs.pop();
			else break;
		}
		for (auto&& element : *nodes)
		{
			if (element>idx)
				inorder[idx].right.push_back(element);
			else if (element<idx)
				inorder[idx].left.push_back(element);
		}
		nodes->clear();
		nodes->push_back(idx);
		prevIdxs.push(idx);
	}
	cout << "Preorder:";
	Travelsal(inorder[FindInorderIdx(inorder.size() - 1)]);
}
