#include<stdio.h>
#include<stdlib.h>

typedef int Item;
typedef struct avlNode
{
	Item item;
	struct avlNode *left;
	struct avlNode *right;
	int height;
}AvlNode;
typedef AvlNode *AvlTree;
typedef AvlNode *Position;

AvlTree MakeEmpty(AvlTree T);
Position Find(Item X, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(Item X, AvlTree T);
AvlTree Delete(Item X, AvlTree T);
Item Retrieve(Position P);

int Max(int a, int b)
{
	return a>b ? a : b;
}
static int Height(Position P)
{
	if(P == NULL)
		return -1;
	else
		return P->height;
}
static Position SingleRotateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;

	K2->height = Max(Height(K2->left), Height(K2->right)) + 1;
	K1->height = Max(Height(K1->left), K2->height) + 1;
	return K1;
}
static Position SingleRotateWithRight(Position K2)
{
	Position K1;

	K1 = K2->right;
	K2->right = K1->left;
	K1->left = K2;

	K2->height = Max(Height(K2->right), Height(K2->left)) + 1;
	K1->height = Max(Height(K1->right), K2->height) + 1;
	return K1;
}
static Position DoubleRotateWithLeft(Position K3)
{
	K3->left = SingleRotateWithRight(K3->left);
	return SingleRotateWithLeft(K3);
}
static Position DoubleRotateWithRight(Position K3)
{
	K3->right = SingleRotateWithLeft(K3->right);
	return SingleRotateWithRight(K3);
}
void Error(int errorInfo)
{
	if(errorInfo == 0)
	{
		printf("Out of sapce!!");
		exit(0);
	}
	else
	{
		printf("Some error!");
		exit(0);
	}
}
AvlTree Insert(Item X, AvlTree T)
{
	if(T == NULL)
	{
		T = (AvlTree)malloc(sizeof(AvlNode));
		if(T == NULL)
			Error(0);
		else
		{
			T->item = X;
			T->height = 0;
			T->left = NULL;
			T->right = NULL;
		}
	}
	else if(X < T->item)
	{
		T->left = Insert(X, T->left);
		if(Height(T->left) - Height(T->right) == 2)
		{
			if(X < T->left->item)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
		}
	}
	else if(X > T->item)
	{
		T->right = Insert(X, T->right);
		if(Height(T->right) - Height(T->left) == 2)
		{
			if(X > T->right->item)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
		}
	}

	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}
//not complete
/*
AvlTree Delete(Item X, AvlTree T)
{
	Position TmpCell;

	if(T == NULL)
		Error(0);
	else if(X < T->item)
		T->left = Delete(X, T->left);
	else if(X > T->item)
		T->right = Delete(X, T->right);
	else if(T->left && T->right)
	{
		TmpCell = FindMin(T->right);
		T->item = TmpCell->item;
		T->right = Delete(T->item, T->right);
	}
	else
	{
		TmpCell = T;
		if(T->left == NULL)
			T = T->right;
		else if(T->right == NULL)
			T = T->left;
		free(TmpCell);
	}

	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}
*/
AvlTree CreatTree(Item X)
{
	AvlTree T;
	T = (AvlTree)malloc(sizeof(AvlNode));
	T->left = NULL;
	T->right = NULL;
	T->item = X;
	T->height = 1;
	return T;
}

AvlTree MakeEmpty(AvlTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

Position Find(Item X, AvlTree T)
{
	if(T == NULL)
		return NULL;
	else if(X < T->item)
		return Find(X, T->left);
	else if(X > T->item)
		return Find(X, T->right);
	else
		return T;
}

Position FindMin(AvlTree T)
{
	if(T == NULL)
		return NULL;
	if(T->left == NULL)
		return T;
	else
		return FindMin(T->left);
}

Position FindMax(AvlTree T)
{
	if(T == NULL)
		return NULL;
	if(T->right == NULL)
		return T;
	else
		return FindMax(T->right);
}

Item Retrieve(Position P)
{
	return P->item;
}

void printItem(Item item)
{
	printf("%d ", item);
}

void PrintTree(AvlTree T)
{
	if(T != NULL)
	{
		PrintTree(T->left);
		printItem(T->item);
		PrintTree(T->right);
	}
}
