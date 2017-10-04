#include <iostream>
#include <algorithm>
#include <queue>
#include <memory>
using namespace std;
class node
{
public:
	int data;
	node* left{};
	node* right{};
	int height{};
	explicit  node(int d):data{d}{}
	int get_height()const
	{
		int left_height{}, right_height{};
		if (left != nullptr)
		{
			left_height = left->get_height();
			left->height = left_height;
		}
		if (right != nullptr)
		{
			right_height = right->get_height();
			right->height = right_height;
		}
		return max(left_height, right_height)+1;
	}
	node* insert(int data)
	{
		node* temp{this};
		if (data < this->data)
		{
			if(left!=nullptr)
			{
				left=left->insert(data);
				temp=rebalance(data);
			}
			else left = new node(data);
		}
		else
		{
			if(right!=nullptr)
			{
				right=right->insert(data);
				temp = rebalance(data);
			}
			else	right = new node(data);
		}
		return temp;
	}
private:
	node* single_right_rotate()
	{
		node* right = this->right;
		this->right = right->left;
		right->left = this;
		return right;
	}
	node* single_left_rotate()
	{
		node* left{ this->left };
		this->left = left->right;
		left->right = this;
		return left;
	}
	node* right_left_rotate()
	{
		right = right->single_left_rotate();
		return single_right_rotate();
	}
	node* left_right_rotate()
	{
		left = left->single_right_rotate();
		return  single_left_rotate();
	}
	node* rebalance(int data)
	{
		node* temp{this};
		height = this->get_height();
		int balance_factor;
		if (left == nullptr)balance_factor = -right->height;
		else if (right == nullptr)balance_factor = left->height;
		else balance_factor = left->height - right->height;
		if(balance_factor==2)
		{
			if(data<left->data)
			{
				temp = single_left_rotate();
			}
			else temp = left_right_rotate();
		}
		else if(balance_factor==-2)
		{
			if (data > right->data)temp = single_right_rotate();
			else temp = right_left_rotate();
		}
		temp->get_height();
		return temp;
	}
};
void traversal(node* n)
{
	queue<node*>q;
	q.push(n);
	while (!q.empty())
	{
		n = q.front();
		if (n->left)q.push(n->left);
		if (n->right)q.push(n->right);
		cout << n->data<<endl;
		q.pop();
		delete n;
	}
}
int main()
{
	int count;
	cin >> count;
	int data;
	cin >> data;
	node* n = new node(data);
	for (int i = 1; i < count; ++i)
	{
		cin >> data;
		n=n->insert(data);
	}
	shared_ptr<node> x{ n,traversal };
}
