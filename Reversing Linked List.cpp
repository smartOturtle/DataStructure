#include <iostream>
#include <unordered_map>
using namespace std;

struct Node
{
	int data_;
	int next_;
	Node(int data, int next) :data_(data), next_(next) {}
};
unordered_map<int, Node> ad;
int Reverse(int begin, int k,int size)
{
	if (size < k)return begin;
	int oldHead = begin, newHead = -1;
	for (int i = 0; i<k; i++)
	{
		int temp = ad.at(oldHead).next_;
		ad.at(oldHead).next_ = newHead;
		newHead = oldHead;
		oldHead = temp;
	}
	ad.at(begin).next_ = Reverse(oldHead,k,size-k);
	return newHead;
}
void PrintAddress(int address)
{
	if (address >= 0)printf("%05d", address);
	else { cout << address; }
}
int main()
{
	int begin, num, k;
	cin >> begin >> num >> k;
	for (int i = 0; i < num; ++i)
	{
		int address, data, next;
		cin >> address >> data >> next;
		ad.insert({ address,Node(data,next) });
	}
	num = 0;
	for (int i = begin; i != -1; i = ad.at(i).next_, num++);
	begin = Reverse(begin, k, num);
	while (begin != -1)
	{
		auto temp = *ad.find(begin);
		PrintAddress(temp.first);
		cout << " " << temp.second.data_ << " ";
		PrintAddress(temp.second.next_);
		cout << '\n';
		begin = ad.at(begin).next_;
	}
}
