#include<stdio.h>
typedef int ElementType;

void ShellSort(ElementType A[], int ArraySize)
{
	int i, j, Increment;
	ElementType Tmp;

	for(Increment = ArraySize/2; Increment > 0; Increment/=2)
	{
		for(i = Increment; i < ArraySize; ++i)
		{
			Tmp = A[i];
			for(j = i; j >= Increment; j -= Increment)
			{
				if(Tmp < A[j-Increment])
					A[j] = A[j-Increment];
				else
					break;
			}
			A[j] = Tmp;
		}
	}
}

int main()
{
	int A[10], i;
	for(i = 0; i < 10; ++i)
		scanf("%d", &A[i]);
	ShellSort(A, 10);
	for(i = 0; i < 10; ++i)
		printf("%d ", A[i]);

	return 0;
}
