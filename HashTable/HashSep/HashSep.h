#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MinTableSize 10
typedef int Item;
struct ListNode
{
	Item item;
	struct ListNode *next;
};
typedef struct ListNode *Position;
typedef struct ListNode *List;
struct HashTbl
{
	int TableSize;
	List *TheLists;
};
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
void DestroyList(List L);
Position Find(Item Key, HashTable H);
void Insert(Item Key, HashTable H);
void Delete(Item Key, HashTable H);
void Print(HashTable H);
Item Retrieve(Position P);
int NextPrime(int TableSize);
int isPrime(int n);
int Hash(Item Key, int TableSize);
void Error(int errorInfo)
{
	if(errorInfo == 0)
	{
		printf("Table Size too small!");
		exit(0);
	}
	else if(errorInfo == 1)
	{
		printf("Out of space!!");
		exit(0);
	}
	else if(errorInfo == 2)
	{
		printf("This is an empty table!");
		exit(0);
	}
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
	{
		Error(0);
	}

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if(H == NULL)
		Error(1);
	H->TableSize = NextPrime(TableSize);
	H->TheLists = (List*)malloc(sizeof(List) * H->TableSize);
	if(H->TheLists == NULL)
		Error(1);

	for(i = 0; i<H->TableSize; ++i)
	{
		H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
		if(H->TheLists[i] == NULL)
			Error(1);
		else
			H->TheLists[i]->next = NULL;
	}

	return H;
}

void DestroyTable(HashTable H)
{
	int i;
	if(H == NULL)
		Error(2);
	for(i = 0; i < H->TableSize; ++i)
	{
		DestroyList(H->TheLists[i]);
	}
	free(H);
}

void DestroyList(List L)
{
	Position pnode;

	if(L == NULL)
		Error(2);

	while(L->next != NULL)
	{
		pnode = L->next->next;
		free(L->next);
		L->next = pnode;
	}
	free(L);
}

Position Find(Item Key, HashTable H)
{
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->next;
	while(P != NULL && P->item != Key)
		P = P->next;
	return P;
}

void Insert(Item Key, HashTable H)
{
	Position Pos, NewCell;
	List L;

	Pos = Find(Key, H);
	if(Pos == NULL)
	{
		NewCell = (List)malloc(sizeof(struct ListNode));
		if(NewCell == NULL)
			Error(1);
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->next = L->next;
			NewCell->item = Key;
			L->next = NewCell;
		}
	}
}

void Delete(Item Key, HashTable H)
{
	Position Pos, BeforePos;
	List L;

	Pos = Find(Key, H);
	if(Pos != NULL)
	{
		L = H->TheLists[Hash(Key, H->TableSize)];
		BeforePos = L;
		while(BeforePos->next != Pos)
			BeforePos = BeforePos->next;
		BeforePos->next = Pos->next;
		free(Pos);
	}
}

void Print(HashTable H)
{
	int i;
	for(i = 0; i < H->TableSize; ++i)
	{
		Position P;
		P = H->TheLists[i]->next;

		printf("\nList %d: ", i);
		while(P != NULL)
		{
			printf("%d ", Retrieve(P));
			P = P->next;
		}
	}
}

Item Retrieve(Position P)
{
	return P->item;
}

int NextPrime(int TableSize)
{
	int i = TableSize;

	while(!isPrime(i))
	{
		if(i % 2) i += 2;
		else  i++;
	}
	return i;
}

int isPrime(int n)
{
	int i;
	for(i = 2; i < n/2; ++i)
	{
		if(n%i == 0)
			return 0;
	}
	return 1;
}

int Hash(Item Key, int TableSize)
{
	return Key % NextPrime(TableSize);
}
