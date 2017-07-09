#include"HashQuad.h"

int main()
{
	HashTable myHash;
	myHash = InitializeTable(100);

	Insert(12, myHash);
	Insert(10, myHash);
	printf("%d ", Retrieve(Find(10, myHash), myHash));

	int i;
	for(i = 0; i<1000; ++i)
	{
		if(NeedRehash(myHash))
			myHash = Rehash(myHash);
		Insert(i, myHash);
	}
	//myHash = Rehash(myHash);
	//myHash = Rehash(myHash);

	printf("%d \n", myHash->TableSize);
	Print(myHash);
	DestroyTable(myHash);
	return 0;
}
