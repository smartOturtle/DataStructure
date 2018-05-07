#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std;
template<typename Contain>
void Sort(Contain& c, int begin, int end, Contain& copy)
{
    auto Merge = [&c, &copy](int begin, int middle, int end)
    {
        int temp = begin, leftBegin = begin, rightBegin = middle + 1;
        while (leftBegin <= middle && rightBegin <= end)
        {
            if (c[leftBegin] < c[rightBegin])copy[temp++] = c[leftBegin++];
            else { copy[temp++] = c[rightBegin++]; }
        }
        while (leftBegin <= middle)copy[temp++] = c[leftBegin++];
        while (rightBegin <= end)copy[temp++] = c[rightBegin++];
        for (int i = begin; i <= end; ++i)
            c[i] = copy[i];
    };
    int const size = c.size();
    for (int length = 1; length < size; length *= 2)
        for (int i = 0; i < size - length; i += length * 2)
        {
            Merge(i, i + length - 1, min(size - 1, i + 2 * length - 1));
        }
}
template<typename Contain>
void MergeSort(Contain& c)
{
    Contain copy(c.size());
    Sort(c, 0, c.size() - 1, copy);
}
int main(int argc, char* argv[])
{
    int size;
    cin >> size;
    vector<int> container;
    for (int i = 0; i < size; ++i)
    {
        int data;
        cin >> data;
        container.push_back(data);
    }
    MergeSort(container);
    cout << container.front();
    for (auto iter = ++container.begin(); iter != container.end(); ++iter)
    {
        cout << " " << *iter;
    }
}
