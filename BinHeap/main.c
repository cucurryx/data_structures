#include"BinHeap.h"

int main()
{
	PriorityQueue myPriQueue;
	int i;

	myPriQueue = Initialize(20);
	for(i = 0; i < 20; ++i)
		Insert(i, myPriQueue);
	DeleteMin(myPriQueue);
	printf("min %d\n", FindMin(myPriQueue));

	printf("Is empty？ %d\n", IsEmpty(myPriQueue));
	MakeEmpty(myPriQueue);
	printf("Is empty？ %d", IsEmpty(myPriQueue));
	Destroy(myPriQueue);
	return 0;
}
