#include<stdio.h>
#include<stdlib.h>

typedef int Item;

typedef struct node{
	Item item;
	struct node *next;
} Node;

typedef Node* List;

List initList()
{
	Node *head;
	head = (Node*) malloc(sizeof(Node));
	head -> next = NULL;
	return head;
}

void pushBack(List list, Item item_)
{
	Node *pnode, *ptail;
	ptail = list;
	while(ptail->next != NULL)
		ptail = ptail->next;

	pnode = (Node*) malloc(sizeof(Node));
	pnode->next = NULL;
	pnode->item = item_;
	ptail->next = pnode;
}

void printList(List list)
{
	Node *pnode = list->next;
	while(pnode!=NULL)
	{
		printf("%d\n",pnode->item);
		pnode = pnode->next;
	}
}

void reverseList(List list)
{
	Node *ptail, *previous, *next;
	previous = list->next;
	next = previous->next;
	ptail = list;

	while(ptail->next != NULL)
	{
		ptail = ptail->next;
	}
	list->next = ptail;
	previous->next = NULL;

	while(next!=NULL)
	{
		Node *temp = previous;
		previous = next->next;
		next->next = temp;

		Node *t = previous;
		previous = next;
		next = t;
	}
}

void deleteList(List list)
{
	Node *pnode = list->next;
	while(list->next != NULL)
	{
		Node *pdelete = pnode;
		pnode = pnode->next;
		list->next = pnode;
		free(pdelete);
	}
	free(list);
}
