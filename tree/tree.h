#include<stdio.h>
#include<stdlib.h>

typedef int Item;
typedef struct node
{
	Item item;
	struct node *left;
	struct node *right;
}treeNode;
typedef treeNode *searchTree;
typedef treeNode *nodePosition;

void Error(int errorInfo);
searchTree CreatTree();
searchTree MakeEmpty(searchTree T);
nodePosition Find(Item X, searchTree T);
nodePosition FindMin(searchTree T);
nodePosition FindMax(searchTree T);
searchTree Insert(Item X, searchTree T);
searchTree Delete(Item X, searchTree T);
Item Retrieve(nodePosition P);
void Show(searchTree T);

void Error(int errorInfo)
{
	if(errorInfo == 0)
	{
		printf("No more space!");
		exit(0);
	}
	else if(errorInfo == 1)
	{
		printf("Program crash!");
		exit(0);
	}
}

searchTree CreatTree(Item X)
{
	searchTree T;
	T = (searchTree)malloc(sizeof(treeNode));
	T->left = NULL;
	T->right = NULL;
	T->item = X;
	return T;
}

searchTree MakeEmpty(searchTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

nodePosition Find(Item X, searchTree T)
{
	if(T == NULL)
		return NULL;
	if(X < T->item)
		return Find(X, T->left);
	else if(X > T->item)
		return Find(X, T->right);
	else
		return T;
}

nodePosition FindMin(searchTree T)
{
	if(T == NULL)
		return NULL;
	if(T->left == NULL)
		return T;
	else
		return FindMin(T->left);
}

nodePosition FindMax(searchTree T)
{
	if(T == NULL)
		return NULL;
	if(T->right == NULL)
		return T;
	else
		return FindMax(T->right);
}

searchTree Insert(Item X, searchTree T)
{
	if(T == NULL)
	{
		T = (searchTree)malloc(sizeof(treeNode));
		if(T == NULL)
			Error(0);
		else
		{
			T->item = X;
			T->left = NULL;
			T->right = NULL;
		}
	}
	else if(X < T->item)
		T->left = Insert(X, T->left);
	else if(X > T->item)
		T->right = Insert(X, T->right);
	return T;
}

searchTree Delete(Item X, searchTree T)
{
	nodePosition TmpCell;

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

	return T;
}

Item Retrieve(nodePosition P)
{
	return P->item;
}
