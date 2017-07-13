#include"LeftHeap.h"

int main()
{
	PriorityQueue myHeapOne, myHeapTwo;
	int i;

	myHeapOne = Initialize();
	myHeapTwo = Initialize();

	for(i = 0; i < 10; ++i)
	{
		Insert(i, myHeapOne);
		Insert(i*i, myHeapTwo);
	}
	myHeapOne = DeleteMin1(myHeapOne);
	myHeapOne = DeleteMin1(myHeapOne);
	DeleteMin(myHeapOne);
	printf("%d ", DeleteMin(myHeapOne));
	printf("%d \n", myHeapOne->Npl);

	myHeapOne = Merge(myHeapOne, myHeapTwo);
	printf("%d ", DeleteMin(myHeapOne));
	printf("%d \n", myHeapOne->Npl);

	printf("\nMidPrint: ");
	MidPrint(myHeapTwo);

	printf("\nBeforePrint: ");
	BeforePrint(myHeapTwo);

	printf("\nAfterPrint: ");
	AfterPrint(myHeapTwo);

	return 0;
}
