#include<iostream>
using namespace std;
int main()
{
	int max_sum{}, current_sum{};
	int count;
	cin >> count;
	int current_begin{}, max_sequence_begin{}, max_sequence_end{};
	int* a= new int[count];
	bool all_is_nagative = true;
	for (size_t i = 0; i < count; i++)
	{
		cin >> a[i];
		if (a[i] >= 0)all_is_nagative = false;
	}
	current_begin = a[0];
	for(int i=0;i<count;i++)
	{
		current_sum += a[i];
		if (current_sum > max_sum)
		{
			max_sum = current_sum;
			max_sequence_begin = current_begin;
			max_sequence_end = a[i];
		}
		else if (current_sum < 0)
		{
			current_sum = 0;
			current_begin = a[i+1<count-1?i+1:count-1];
		}
	}
	if (all_is_nagative)cout << 0<<" "<<a[0]<<" "<<a[count-1] ;
	else cout << max_sum<<" "<<max_sequence_begin<<" "<<max_sequence_end;
	delete[] a;
	return 0;
}
