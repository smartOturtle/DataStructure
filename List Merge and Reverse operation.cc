#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
	int data;
	Node* next{};
	explicit  Node(int d):data(d){}
	Node& operator ++()
	{
		*this = *this->next;
		return *this;
	}
	Node operator ++(int)//后置的自增自减运算符应该以传值的形式返回
	{
		auto temp = *this;
		*this = *this->next;
		return temp;
	}
};
class List
{
	Node head_{ 0 };
public:
	void Merge(List list)
	{
		if(list.Empty())return;
		auto iter = &head_, listTemp = list.head_.next, thisTemp = head_.next;
		list.head_.next = nullptr;
		while (listTemp&&thisTemp)
		{
			if(listTemp->data>thisTemp->data)
			{
				iter->next = thisTemp;
				thisTemp = thisTemp->next;
			}
			else
			{
				iter->next = listTemp;
				listTemp = listTemp->next;
			}
			iter = iter->next;
		}
		if (listTemp)iter->next = listTemp;
		else { iter->next = thisTemp; }
	}
	void Reverse()
	{
		auto old_head = head_.next;
		Node* new_head = nullptr;
		while (old_head)
		{
			auto temp = old_head->next;
			old_head->next = new_head;
			new_head= old_head;
			old_head = temp;
		}
		head_.next = new_head;
	}
	void PushFront(int data)
	{
		auto temp = head_.next;
		head_.next = new Node(data);
		head_.next->next = temp;
	}
	bool Empty()const { return head_.next==nullptr; }
	Node* Front()
	{
		return head_.next;
	}
	~List()
	{
		auto iter = head_.next;
		while (iter)
		{
			cout << iter->data;
			auto temp = iter->next;
			delete iter;
			iter = temp;
		}
	}
};
int main(int argc, char* argv[])
{
	List l1;
	for (int i = 1; i < 5; ++i)
	{
		l1.PushFront(-i);
	}
	l1.Reverse();
	for (auto iter = l1.Front(); iter != nullptr; iter = iter->next)cout << iter->data;
}
