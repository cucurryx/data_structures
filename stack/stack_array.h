#include<stdlib.h>
#include<stdio.h>

typedef int Item;
struct StackRecord
{
	int Capacity;
	int TopOfStack;
	Item *Array;
};

typedef struct StackRecord* Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Pop(Stack S);
Item Top(Stack S);
Item TopAndPop(Stack S);
#define EmptyTOS (-1)
#define MinStackSize (5)
void Error(int errorInfo)
{
	printf("%d\n",errorInfo);
	exit(0);
}

Stack CreateStack(int MaxElements)
{
	Stack S;

	S = (Stack)malloc(sizeof(struct StackRecord));
	if(S == NULL)
		Error(1);
	S->Array = (Item*)malloc(sizeof(Item) * MaxElements);
	if(S->Array == NULL)
		Error(1);
	S->Capacity = MaxElements;
	MakeEmpty(S);

	return S;
}

void DisposeStack(Stack S)
{
	if(S != NULL)
	{
		free(S->Array);
		free(S);
	}
}

int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyTOS;
}

int IsFull(Stack S)
{
	return S->TopOfStack == S->Capacity;
}
void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyTOS;
}

void Push(Item it, Stack S)
{
	if(IsFull(S))
		Error(0);
	else
		S->Array[++S->TopOfStack] = it;
}

Item Top(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[S->TopOfStack];
	Error(0);
	return 0;
}

void Pop(Stack S)
{
	if(IsEmpty(S))
		Error(0);
	else
		S->TopOfStack--;
}

Item TopAndPop(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[--S->TopOfStack];
	Error(0);
	return 0;
}
