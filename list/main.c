#include<stdio.h>
#include"list.h"

int main()
{
	int i;
	List list = initList();

	for(i=0; i<12; ++i)
		pushBack(list, i);
	printList(list);
	printf("after reverse:\n");
	reverseList(list);
	printList(list);
	deleteList(list);
	
	return 0;
}
