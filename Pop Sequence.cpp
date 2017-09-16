#include <iostream>
#include <deque>
#include <vector>
using namespace std;
int main()
{
	int capacity, seq_length, row_count;
	cin >>capacity >>seq_length >> row_count;
	vector<vector<int>> collection(row_count);
	for (int i = 0; i < row_count; ++i)
	{
		for (int j = 0; j < seq_length; ++j)
		{
			int a;
			cin >> a;
			collection[i].push_back(a);
		}
	}
	deque<int> stack;
	for (auto& list:collection)
	{
		int current_num{0};
		bool is_right{true};
		stack.clear();
		for (int i = 0; i < seq_length; ++i)
		{
			int k = list[i];
			while(k>current_num)
			{
				stack.push_front(++current_num);
			}
			if (stack.size() > capacity) { is_right = false;break; }
			if(stack.front()==k)stack.pop_front();
			else { is_right = false;break; }
		}
		if (is_right)cout << "YES\n";
		else  cout << "NO\n";
	}
	return 0;
}
