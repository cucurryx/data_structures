#include"BinHeap.h"

int main()
{
	PriorityQueue myPriQueue;
	int i;

	myPriQueue = Initialize(20);
	for(i = 0; i < 20; ++i)
		Insert(i,  myPriQueue);
	DeleteMin(myPriQueue);
	printf("min %d\n", FindMin(myPriQueue));

	return 0;
}
