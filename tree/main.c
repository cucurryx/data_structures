#include"tree.h"

int main()
{
	searchTree myTree = CreatTree(5);
	int i;

	for(i=0; i<10; ++i)
		Insert(i, myTree);
	printf("%d  %d\n",Retrieve(Find(9,myTree)), Retrieve(FindMin(myTree)));
	printf("%d",Retrieve(myTree));
	return 0;
}
