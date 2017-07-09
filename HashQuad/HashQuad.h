#include<stdio.h>
#include<stdlib.h>
#define MinTableSize 10

typedef unsigned int Index;
typedef Index Position;
typedef int Item;

enum KindOfEntry {Legitimate, Empty, Deleted};
struct HashEntry;
struct HashTbl;
typedef struct HashEntry Cell;
typedef struct HashTbl *HashTable;

struct HashEntry
{
	Item item;
	enum KindOfEntry info;
};
struct HashTbl
{
	Cell *TheCells;
	int TableSize;
};

HashTable InitializeTable(int TableSize);
void DestroyTable(HashTable H);
Position Find(Item Key, HashTable H);
void Insert(Item Key, HashTable H);
void Print(HashTable H);
Item Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);
void Error(int ErrorInfo);
int NextPrime(int x);
int IsPrime(int x);
int Hash(Item Key, int TableSize);
int NeedRehash(HashTable H);

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
	{
		printf("Error: Table size is too small!");
		return NULL;
	}

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if(H == NULL)
		Error(0);

	H->TableSize = NextPrime(TableSize);
	H->TheCells = (Cell*)malloc(sizeof(Cell) * H->TableSize);
	if(H->TheCells == NULL)
		Error(0);

	for(i = 0; i < H->TableSize; ++i)
		H->TheCells[i].info = Empty;

	return H;
}

void DestroyTable(HashTable H)
{
	if(H == NULL)
		Error(1);
	if(H->TheCells != NULL)
		free(H->TheCells);
	printf("Hash table destroy.........\n");
	free(H);
}

Position Find(Item Key, HashTable H)
{
	Position CurrentPos;
	int CountNum;

	CountNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	while(H->TheCells[CurrentPos].info != Empty &&
		  H->TheCells[CurrentPos].item != Key)
	{
		CurrentPos += 2 * ++CountNum - 1;
		if(CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}

	return CurrentPos;
}

void Insert(Item Key, HashTable H)
{
	Position Pos;

	Pos = Find(Key, H);
	if(H->TheCells[Pos].info != Legitimate)
	{
		H->TheCells[Pos].info = Legitimate;
		H->TheCells[Pos].item = Key;
	}
}

void Print(HashTable H)
{
	int i;
	if(H == NULL)
		Error(1);

	printf("Your hash table:\n");
	for(i = 0; i < H->TableSize; ++i)
	{
		if(H->TheCells[i].info == Legitimate)
			printf("%d \n", H->TheCells[i].item);
	}
}

Item Retrieve(Position P, HashTable H)
{
	return H->TheCells[P].item;
}

HashTable Rehash(HashTable H)
{
	int i, OldSize;
	Cell *OldCells;

	OldSize = H->TableSize;
	OldCells = H->TheCells;

	H = InitializeTable(OldSize * 2);

	for(i = 0; i < OldSize; ++i)
		if(OldCells[i].info == Legitimate)
			Insert(OldCells[i].item, H);
	free(OldCells);

	return H;
}

void Error(int ErrorInfo)
{
	if(ErrorInfo == 0)
	{
		printf("No more memory!");
		exit(0);
	}
	else if(ErrorInfo == 1)
	{
		printf("Empty! Can't destory it!");
		exit(0);
	}
}

int NextPrime(int TableSize)
{
	int i = TableSize;

	while(!IsPrime(i))
	{
		if(i % 2) i += 2;
		else  i++;
	}
	return i;
}

int IsPrime(int n)
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

int NeedRehash(HashTable H)
{
	int ItemCount, i;

	ItemCount = 0;
	for(i = 0; i < H->TableSize; ++i)
	{
		if(H->TheCells[i].info == Legitimate)
			++ItemCount;
	}

	if(ItemCount >= H->TableSize / 2)
		return 1;
	else
		return 0;
}
