#include<stdio.h>
#include<stdlib.h>
#define MinPQSSize 10
#define MinData -1

typedef int Item;
struct HeapStruct
{
	int Capacity;
	int Size;
	Item *Items;
};
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(Item X, PriorityQueue H);
Item DeleteMin(PriorityQueue H);
Item FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);
void Error(int ErrorInfo);

PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;

	if(MaxElements < MinPQSSize)
		Error(0);

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	if(H == NULL)
		Error(1);

	H->Items = (Item*)malloc(sizeof(Item) * (MaxElements+1));
	if(H->Items == NULL)
		Error(1);

	H->Capacity = MaxElements;
	H->Size = 0;
	H->Items[0] = MinData;

	return H;
}

void Destroy(PriorityQueue H)
{
	if(H == NULL)
		Error(2);
	if(H->Items != NULL)
		free(H->Items);
	free(H);
}

void MakeEmpty(PriorityQueue H)
{
	int i;
	if(IsEmpty(H))
		return;

	for(i = 1; i < H->Capacity; ++i)
		H->Items[i] = 0;
	H->Size = 0;
}

void Insert(Item X, PriorityQueue H)
{
	int i;

	if(IsFull(H))
	{
		Error(3);
		return;
	}

	for(i = ++H->Size; H->Items[i/2] > X; i /= 2)
	{
		H->Items[i] = H->Items[i/2];
	}
	H->Items[i] = X;
}

Item DeleteMin(PriorityQueue H)
{
	int i, Child;
	Item MinItem, LastItem;

	if(IsEmpty(H))
	{
		Error(4);
		return H->Items[0];
	}
	MinItem = H->Items[1];
	LastItem = H->Items[H->Size--];

	for(i = 1; i*2 <= H->Size; i = Child)
	{
		Child = 2 * i;
		if(Child != H->Size && H->Items[Child] > H->Items[Child+1])
			++Child;

		if(LastItem > H->Items[Child])
			H->Items[i] = H->Items[Child];
		else
			break;
	}
	H->Items[i] = LastItem;
	
	return MinItem;
}

Item FindMin(PriorityQueue H)
{
	return H->Items[1];
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

void Error(int ErrorInfo)
{
	printf("Error: ");
	if(ErrorInfo == 0)
	{
		printf("Priority queue size is too small!");
		exit(0);
	}
	else if(ErrorInfo == 1)
	{
		printf("Out of space!");
		exit(0);
	}
	else if(ErrorInfo == 2)
	{
		printf("Free empty space!");
		exit(0);
	}
	else if(ErrorInfo == 3)
	{
		printf("Priority queue is full");
	}
	else if(ErrorInfo == 4)
	{
		printf("Priority queue is empty");
	}
}
