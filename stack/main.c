#include"stack_array.h"

int main()
{
	Stack myStack = CreateStack(50);
	int i;
	for(i = 0; i<30; ++i)
		Push(i, myStack);

	for(i = 0; i<29; ++i)
	{
		printf("%d\n", Top(myStack));
		Pop(myStack);
	}

	int last = TopAndPop(myStack);
	MakeEmpty(myStack);
	Push(111, myStack);
	printf("%d", Top(myStack));
	DisposeStack(myStack);

	printf("hello world\n");
	printf("**%d**", last);
	return 0;
}
