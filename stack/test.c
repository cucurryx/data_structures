#include"stack.h"
int main()
{
	Stack myStack = CreateStack();
	char ch;

	FILE *fp = fopen("input.txt","rt");
	while(fscanf(fp,"%c",&ch) != EOF)
	{
		if(ch == '(' || ch == '[' || ch == '{')
			Push(ch, myStack);
		if(ch == ')' || ch == ']' || ch == '}')
		{
			if(Top(myStack) != ch-1 && ch == ')')
			{
				printf("this is not right!\n");
				break;
			}
			else if(Top(myStack) != ch-2)
			{
				printf("this is not right!\n");
				break;
			}
			Pop(myStack);
		}
	}
	if(IsEmpty(myStack))
		printf("this is right!\n");
	else
		printf("this is not right!\n");
	DisposeStack(myStack);

	return 0;
}
