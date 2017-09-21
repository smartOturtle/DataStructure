#include <iostream>
#include <vector>
using namespace std;
struct node
{
	int left{'-'};
	int right{'-'};
	char data;
	node(int left,int right,char data)
	{
		this->data = data;
		if(right!='-')this->right = right-'0';
		if(left!='-')this->left = left-'0';
	}
};
vector<node> nodes_first, nodes_second;
bool cmp(node& n1,node& n2)
{

	if(n1.data==n2.data)
	{
		if(n1.left==n1.right)
		{
			if (n2.left == n2.right)return true;
			return false;
		}
		if(n1.left=='-')
		{
			if (n2.left != '-')swap(n2.left, n2.right);
			if (n2.left != '-')return false;
			return cmp(nodes_first[n1.right], nodes_second[n2.right]);
		}
		if (n1.right == '-')
		{
			if (n2.right != '-')swap(n2.left, n2.right);
			if (n2.right != '-')return false;
			return cmp(nodes_first[n1.left], nodes_second[n2.left]);
		}
		if (n2.left == n2.right)
		{
			if (n1.left == n1.right)return true;
			return false;
		}
		if (n2.left == '-')
		{
			if (n1.left != '-')swap(n1.left, n1.right);
			if (n1.left != '-')return false;
			return cmp(nodes_first[n1.right], nodes_second[n2.right]);
		}
		if (n2.right == '-')
		{
			if (n1.right != '-')swap(n1.left, n1.right);
			if (n1.right != '-')return false;
			return cmp(nodes_first[n1.left], nodes_second[n2.left]);
		}
		if (nodes_first[n1.left].data == nodes_second[n2.left].data&&nodes_first[n1.right].data == nodes_second[n2.right].data)
			return cmp(nodes_first[n1.left], nodes_second[n2.left])&&cmp(nodes_first[n1.right], nodes_second[n2.right]);
		swap(n2.left, n2.right);
		if (nodes_first[n1.left].data == nodes_second[n2.left].data&&nodes_first[n1.right].data == nodes_second[n2.right].data)
			return cmp(nodes_first[n1.left], nodes_second[n2.left]) && cmp(nodes_first[n1.right], nodes_second[n2.right]);
		return false;
	}
	return false;
}
int main()
{
	int count;
	cin >> count;
	char left, right,data;
	for (int i = 0; i < count; ++i)
	{
		cin >>data>> left >> right;
		nodes_first.push_back({ left,right,data });
	}
	cin >> count;
	for (int i = 0; i < count; ++i)
	{
		cin >> data >> left >> right;
		nodes_second.push_back({ left,right,data });
	}
	if (nodes_first.size() == 0 && nodes_second.size() == 0)
	{
		cout << "Yes";
		return 0;
	}
	if (nodes_first.size() != nodes_second.size())
	{
		cout << "No";
		return 0;
	}
	int first_root{}, second_root{};
	vector<int> check_box1(count), check_box2(count);
	for(auto& x:nodes_first)
	{
		if(x.left!='-')check_box1[x.left] = 1;
		if(x.right!='-')check_box1[x.right] = 1;
	}
	for (auto& x : nodes_second)
	{
		if (x.left != '-')check_box2[x.left] = 1;
		if (x.right != '-')check_box2[x.right] = 1;
	}
	for (int i = 0; i < count; ++i)
	{
		if (!check_box1[i])
		{
			first_root = i;
			break;
		}
	}
	for (int i = 0; i < count; ++i)
	{
		if (!check_box2[i])
		{
			second_root = i;
			break;
		}
	}
	if (cmp(nodes_first[first_root], nodes_second[second_root]))cout << "Yes";
	else cout << "No";
	return 0;
}
