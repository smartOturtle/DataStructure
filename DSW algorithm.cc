#define  _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node* left=nullptr;
    Node* right=nullptr;
    explicit Node(int data):data(data){}
    Node* LeftRotate()
    {
        auto parent = left;
        left = parent->right;
        parent->right = this;
        return parent;
    }
    Node* RightRotate()
    {
        auto parent = right;
        right = parent->left;
        parent->left = this;
        return parent;
    }
    Node* RightRotateN(int n)
    {
        if (n == 0)return this;//check edge condition
        auto parent = RightRotate();
        auto iter = parent;
        for (int i = 1; i < n; ++i)
        {
            if(iter->right==nullptr)break;
            iter->right = iter->right->RightRotate();
            iter = iter->right;
        }
        return parent;
    }
};
void Insert(Node*& n, int value)
{
    if(n==nullptr)
    {
        n = new Node(value);
        return;
    }
    if (n->data < value)Insert(n->right, value);
    else Insert(n->left, value);
}
struct Tree
{
    int size = 0;
    Node* root = nullptr;
    void Insert(int value)
    {
        ::Insert(root, value);
        size++;
    }
    bool Empty()const { return root==nullptr; }
    void ToRightList()
    {
        Node n(1);
        auto iter = &n;
        iter->right = root;
        while (root->left != nullptr) { root = root->left; }
        while (iter->right != nullptr)
        {
            if (iter->right->left != nullptr)iter->right = iter->right->LeftRotate();
            else iter = iter->right;
        }
    }
    void Balance()
    {
        int difference = pow(2, floor(log2(size+1))) - 1;
        ToRightList();
        root=root->RightRotateN(size - difference);
        while (difference>1)
        {
            difference /= 2;
            root = root->RightRotateN(difference);
        }
    }
    void LevelOrderTraversal()const
    {
        if (root == nullptr)return;
        queue<Node*> q;
        q.push(root);
        cout << root->data;
        while (!q.empty())
        {
            if (q.front()->left != nullptr)q.push(q.front()->left);
            if (q.front()->right != nullptr)q.push(q.front()->right);
            q.pop();
            if (!q.empty())cout << " " << q.front()->data;
        }
    }
};

int main(int argc, char* argv[])
{
    int nodeSize;
    cin >> nodeSize;
    Tree tree;
    for (int i = 0; i < nodeSize; ++i)
    {
        int value;
        cin >> value;
        tree.Insert(value);
    }
    tree.Balance();
    tree.LevelOrderTraversal();
}
