#include"HashSep.h"

int main()
{
	int i;
	HashTable myHash;
	myHash = InitializeTable(1000);

	for(i = 0; i<1000; ++i)
		Insert(i, myHash);
	//printf("%p %p")
	Print(myHash);
	DestroyTable(myHash);
	return 0;
}
