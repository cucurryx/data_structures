#include<stdio.h>
#include<stdlib.h>

#ifndef _SkewHeap_H

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PriorityQueue;

PriorityQueue Initialize();
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);
void MidPrint(PriorityQueue H);
void BeforePrint(PriorityQueue H);
void AfterPrint(PriorityQueue H);
void Destroy(PriorityQueue H);

#define Insert(X, H) (H = Insert1(X, H))
#define DeleteMin(H) (H = DeleteMin1(H))
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

#endif

struct TreeNode
{
	ElementType Element;
	struct TreeNode *Left;
	struct TreeNode *Right;
};

PriorityQueue Initialize()
{
	PriorityQueue Heap;
	Heap = NULL;
	return Heap;
}

ElementType FindMin(PriorityQueue H)
{
	return H->Element;
}

int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}

PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap, RightHeap;
	LeftHeap = H->Left;
	RightHeap = H->Right;
	free(H);
	return Merge(LeftHeap, RightHeap);
}

void SwapChildren(PriorityQueue H)
{
	PriorityQueue LeftChildren = H->Left;
	H->Left = H->Right;
	H->Left = LeftChildren;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if(H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = Merge(H1->Right, H2);
		SwapChildren(H1);
	}
	return H1;
}

PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2)
{
	if(H1 == NULL)
		return H2;
	if(H2 == NULL)
		return H1;
	if(H1->Element < H2->Element)
		return Merge1(H1, H2);
	else
		return Merge1(H2, H1);
}

PriorityQueue Insert1(ElementType X, PriorityQueue H)
{
	PriorityQueue NewHeap;
	NewHeap = (PriorityQueue)malloc(sizeof(struct TreeNode));
	if(NewHeap == NULL)
	{
		printf("Error: Out of space!");
		return H;
	}

	NewHeap->Element = X;
	NewHeap->Left = NULL;
	NewHeap->Right = NULL;
	H = Merge(NewHeap, H);
	return H;
}

static void PrintElement(ElementType Element)
{
	printf("%d ", Element);
}

void MidPrint(PriorityQueue H)
{
	if(H == NULL)
		return;
	MidPrint(H->Left);
	PrintElement(H->Element);
	MidPrint(H->Right);
}

void BeforePrint(PriorityQueue H)
{
	if(H == NULL)
		return;
	PrintElement(H->Element);
	BeforePrint(H->Left);
	BeforePrint(H->Right);
}

void AfterPrint(PriorityQueue H)
{
	if(H == NULL)
		return;
	AfterPrint(H->Left);
	AfterPrint(H->Right);
	PrintElement(H->Element);
}

void Destroy(PriorityQueue H)
{
	if(H == NULL)
		return;
	Destroy(H->Left);
	Destroy(H->Right);
	free(H);
}
