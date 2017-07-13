#include"SkewHeap.h"

int main()
{
	PriorityQueue mySkewHeap = Initialize();
	int i;

	for(i = 0; i < 20; ++i)
		Insert(i, mySkewHeap);
	printf("Min: %d ", FindMin(mySkewHeap));
	DeleteMin(mySkewHeap);

	printf("\nBeforePrint: \n");
	BeforePrint(mySkewHeap);

	printf("\nMidPrint: \n");
	MidPrint(mySkewHeap);

	printf("\nAfterPrint: \n");
	AfterPrint(mySkewHeap);

	Destroy(mySkewHeap);
	return 0;
}
