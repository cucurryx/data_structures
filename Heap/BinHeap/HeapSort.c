#include"BinHeap.h"

int *HeapSort(int *BeforeSort, int Size)
{
	int *AfterSort, i;
	AfterSort = (int*)malloc(sizeof(int) * Size);

	PriorityQueue Heap = Initialize(Size);
	for(i = 0; i < Size; ++i)
		Insert(BeforeSort[i], Heap);
	for(i = 0; i < Size; ++i)
		AfterSort[i] = DeleteMin(Heap);
	Destroy(Heap);

	return AfterSort;
}

int main()
{
	int *a, i;
	a = (int*)malloc(sizeof(int) * 10);

	for(i = 0; i < 10; ++i)
		scanf("%d", &a[i]);
	a = HeapSort(a, 10);

	for(i = 0; i < 10; ++i)
		printf("%d\n", a[i]);

	return 0;
}
