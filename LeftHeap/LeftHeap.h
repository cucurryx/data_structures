#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PriorityQueue;

PriorityQueue Initialize();
ElementType FindMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Merge(PriorityQueue H1, PriorityQueue H2);

#define Insert(X, H) (H = Insert1(X, H))
#define DeleteMin(H) (H = DeleteMin1(H), FindMin(H))  //wrong DeleteMin
PriorityQueue Insert1(ElementType X, PriorityQueue H);
PriorityQueue DeleteMin1(PriorityQueue H);

struct TreeNode
{
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl; // null path length
};

PriorityQueue Initialize()
{
	PriorityQueue LeftHeap;
	LeftHeap = NULL;
	return LeftHeap;
}

ElementType FindMin(PriorityQueue H)
{
	if(H == NULL)
	{
		printf("Error: Empty heap!");
		exit(0);
	}
	return H->Element;
}

int IsEmpty(PriorityQueue H)
{
	return H == NULL;
}

PriorityQueue SwapChildren(PriorityQueue H)
{
	PriorityQueue LeftChild = H->Left;
	H->Left = H->Right;
	H->Right = LeftChild;

	return H;
}

static PriorityQueue Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if(H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = Merge(H1->Right, H2);
		if(H1->Left->Npl < H1->Right->Npl)
			H1 = SwapChildren(H1);
		H1->Npl = H1->Right->Npl + 1;
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
	PriorityQueue SingleNode;

	SingleNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
	if(SingleNode == NULL)
	{
		printf("Error: Out of Space!");
		exit(0);
	}
	else
	{
		SingleNode->Element = X;
		SingleNode->Left = NULL;
		SingleNode->Right = NULL;
		SingleNode->Npl = 0;
		H = Merge(SingleNode, H);
	}
	return H;
}

PriorityQueue DeleteMin1(PriorityQueue H)
{
	PriorityQueue LeftHeap, RightHeap;

	if(IsEmpty(H))
	{
		printf("Error: Delete empty heap.");
		return NULL;
	}

	LeftHeap = H->Left;
	RightHeap = H->Right;
	free(H);
	return Merge(LeftHeap, RightHeap);
}
