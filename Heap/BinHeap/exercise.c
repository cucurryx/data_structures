#include"BinHeap.h"

int main()
{
	PriorityQueue myHeap = Initialize(15);
	int i, a[15] = {10, 12, 1, 14, 6, 5, 8, 15, 3, 9, 7, 4, 11, 13, 2};
	for(i = 0; i < 15; ++i)
		Insert(a[i], myHeap);

	for(i = 1; i <= 15; ++i)
		printf("%d ", myHeap->Items[i]);
	return 0;
}
