#include"AVLtree.h"
int main()
{
	AvlTree myTree = CreatTree(5);
	int i = 0;
	for(; i<100; ++i)
		myTree = Insert(i, myTree);

	printf("Height:%d\n", Height(myTree));
	Position root = myTree;
	printf("Max:%d Min:%d Root:%d\n", Retrieve(FindMax(myTree)),
	Retrieve(FindMin(myTree)), Retrieve(root));

	return 0;
}
