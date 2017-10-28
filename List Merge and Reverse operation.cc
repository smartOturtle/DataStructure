#include <iostream>
#include <algorithm>
using namespace std;
class List
{
	struct Node
	{
		int data;		
		explicit  Node(int d) :data(d) {}
		Node* next{};		
	};	
	Node head_{ 0 };
public:
	struct iterator
	{
		iterator():iter(nullptr){}
		explicit iterator(Node* n) { iter = n; }
		iterator operator ++()
		{
			iter = iter->next;
			return *this;
		}
		int& operator *() const
		{
			return iter->data;
		}
		bool operator ==(iterator one) const { return one.iter == iter; }
		bool operator !=(iterator one) const { return one.iter != iter; }
	private:
		Node* iter;
	};
	void Merge(List& list)
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
	iterator  begin() {return iterator(head_.next);}
	iterator end() { return iterator(); }
	~List()
	{
		auto iter = head_.next;
		while (iter)
		{
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
