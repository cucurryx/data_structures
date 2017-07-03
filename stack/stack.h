#include<stdio.h>
#include<stdlib.h>

typedef char Item;
typedef struct node
{
	Item item;
	struct node * next;
}Node;
typedef Node* Stack;

int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Item it, Stack S);
Item Top(Stack S);
void Pop(Stack S);
void Error(int errorInfo);

Stack CreateStack()
{
	Stack s;

	s = (Stack)malloc(sizeof(Node));
	if(s == NULL)
		Error(2);
	s->next = NULL;
	MakeEmpty(s);
	return s;
}

void Error(int errorInfo)
{
	printf("%d\n",errorInfo);
	exit(0);
}

int IsEmpty(Stack S)
{
	return S->next == NULL;
}

void DisposeStack(Stack S)
{
	MakeEmpty(S);
	free(S);
}

void MakeEmpty(Stack S)
{
	if(S == NULL)
		Error(0);
	else
		while(!(IsEmpty(S)))
			Pop(S);
}

void Push(Item it, Stack S)
{
	Node* pnode;

	pnode = (Stack)malloc(sizeof(Node));
	if(pnode == NULL)
		Error(4);
	else
	{
		pnode->item = it;
		pnode->next = S->next;
		S->next = pnode;
	}
}

Item Top(Stack S)
{
	if(!IsEmpty(S))
		return S->next->item;
}

void Pop(Stack S)
{
	Node *FirstCell;

	if(IsEmpty(S))
		Error(1);
	else
	{
		FirstCell = S->next;
		S->next = S->next->next;
		free(FirstCell);
	}
}
