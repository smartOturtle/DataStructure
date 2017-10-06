#include <iostream>
#include <vector>
#include <string>
using namespace std;
class set_container
{
public:
	int find_root(int data)
	{
		if (container[data] < 0)return data;
		return container[data]= find_root(container[data]);
	}
	void union_set(int element1, int element2)
	{
		const int root1 = find_root(element1);
		const int root2 = find_root(element2);
		if (container[root2] > container[root1])
		{
			container[root1] += container[root2];
			container[root2] = root1;
		}
		else
		{
			container[root2] += container[root1];
			container[root1] = root2;
		}
	}
	vector<int> container;
};
int main()
{
	string str;
	set_container s;
	int count;
	cin >> count;
	s.container.resize(count);
	for (int i = 0; i < count; ++i)
	{
		s.container[i] = -1;
	}
	while (true)
	{
		char input_flag;
		cin >> input_flag;
		if (input_flag == 'C')
		{
			int one, other;
			cin >> one >> other;
			one = s.find_root(one-1);
			other = s.find_root(other-1);
			if (one == other&&one >= 0)str += "yes\n";
			else { str += "no\n"; }
		}
		else if (input_flag == 'I')
		{
			int one, other;
			cin >> one >> other;
			s.union_set(one-1, other-1);
		}
		else { break; }
	}
	int component_count{};
	for (const auto& x : s.container)
	{
		if (x<0)component_count ++;
	}
	cout << str;
	if (component_count ==1)cout << "The network is connected.";
	else { cout << "There are " <<component_count << " components."; }
}
