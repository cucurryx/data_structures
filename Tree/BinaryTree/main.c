#include"tree.h"

int main()
{
	searchTree myTree = CreatTree(5);
	int i;

	for(i=0; i<100; ++i)
		myTree = Insert(i, myTree);
	printf("Max:%d  Min:%d\n",Retrieve(FindMax(myTree)), Retrieve(FindMin(myTree)));
	printf("Root:%d",Retrieve(myTree));

	return 0;
}
