#define  _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <tuple>
using namespace std;

struct Node
{
    char data;
    int left=-1;
    int right=-1;
};
pair<vector<Node>,int> InputTree()
{
    int size;
    cin >> size;
    vector<Node> nodes(size);
    deque<bool> appeared(size);
    for (int i = 0; i < size; ++i)
    {
        char c;
        string left, right;
        cin >> c >> left >> right;
        nodes[i].data = c;
        if (left.front() != '-')appeared[nodes[i].left = stoi(left)]=true;
        if (right.front() != '-')appeared[nodes[i].right = stoi(right)]=true;
    }
    int root = find(appeared.begin(), appeared.end(), false) - appeared.begin();
    return { nodes,root==size?-1:root };
}
vector<Node> lhsTree,rhsTree;
bool Cmp(int lhsRoot,int rhsRoot)
{
    if (lhsRoot ==rhsRoot&&rhsRoot == -1)return true;
    if ((lhsRoot == -1) ^ (rhsRoot == -1))return false;
    auto& lhsNode = lhsTree[lhsRoot];
    auto& rhsNode = rhsTree[rhsRoot];
    return lhsNode.data == rhsNode.data &&
        ((Cmp(lhsNode.left, rhsNode.left) && Cmp(lhsNode.right, rhsNode.right)) ||
            (Cmp(lhsNode.left, rhsNode.right) && Cmp(lhsNode.right, rhsNode.left)));
}
int main(int argc, char* argv[])
{
    int lhsRoot;
    tie(lhsTree, lhsRoot) = InputTree();
    int rhsRoot;
    tie(rhsTree, rhsRoot) = InputTree();
    if(Cmp(lhsRoot, rhsRoot))cout<<"Yes\n";
    else { cout << "No\n"; }
}
