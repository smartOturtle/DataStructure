#include <iostream>
using namespace std;
typedef int ElementType;
typedef struct Node* PtrToNode;
struct Node
{
	ElementType Data;
	PtrToNode   Next{};
};
typedef PtrToNode List;

List Merge(List L1, List L2);

int main()
{
	Node n1, n2, n3;
	n1.Data = 1,n2.Data=2,n3.Data=6;
	n1.Next = &n2, n2.Next = &n3;
	Node m1, m2, m3;
	m1.Data = 2, m2.Data = 4, m3.Data = 5;
	m1.Next = &m2, m2.Next = &m3;
	return 0;
}

List Merge(List L1, List L2)
{
	if (!L1)return L2;
	if (!L2)return L1;
	List head = (L1->Data < L2->Data ? L1 : L2);
	L1 = head;
	L2 = (L1->Data < L2->Data ? L2 : L1);
	while (L1->Next&&L2->Next)
	{
		if (L1->Next->Data > L2->Data)
		{
			List temp = L1->Next;
			L1->Next = L2;
			L1 = L2;
			L2 = temp;
		}
		else L1 = L1->Next;
	}
	if (!L2->Next)
		while (L1->Next)
		{
			if (L1->Data <= L2->Data&&L2->Data <= L1->Next->Data)
			{
				List temp = L1->Next;
				L1->Next = L2;
				L2->Next = temp;
				break;
			}
			L1 = L1->Next;
		}
	if (!L1->Next) { L1->Next = L2; }
	return head;
}
