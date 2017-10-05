#include <iostream>
#include <vector>
using namespace std;
class heap
{
public:	
	void push(int data)
	{
		resource_.push_back(data);
		int i = resource_.size() - 1;
		for (;resource_[i/2]<data;i/=2)
		{
			resource_[i] = resource_[i / 2];
		}
		resource_[i] = data;
	}
	int pop()
	{
		const int front = resource_[1];
		swap(resource_.back(), resource_[1]);
		resource_.erase(--resource_.end());
		for(int i=1;i*2<resource_.size();)
		{
			int j = i * 2;
			if (j<resource_.size()-1&&resource_[j] < resource_[j + 1])++j;
			if (resource_[i] < resource_[j])swap(resource_[i], resource_[j]);
			else { break; }
			i = j;
		}
		return  front;
	}
	bool empty()const
	{
		return resource_.size() == 1;
	}
	heap(initializer_list<int> list)
	{
		resource_.assign(list);
		resource_.push_back(INT32_MAX);
		swap(resource_[0], resource_.back());
		for (int i = resource_.size()/2; i >0; --i)
		{
			for(int j=i;j*2<resource_.size();)
			{
				int k = j * 2;
				if (k < resource_.size() - 1 && resource_[k] < resource_[k + 1])++k;
				if(resource_[k]<resource_[j])break;
				swap(resource_[j], resource_[k]);
				j = k;
			}
		}
	}
	heap()
	{
		resource_.push_back(INT32_MAX);
	}
private:
	vector<int> resource_;
};
int main()
{
	
}
