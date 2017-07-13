#include<stdio.h>
typedef int ElementType;

void InsertSort(ElementType A[], int ArraySize)
{
	int i, j;
	for(i = 1; i < ArraySize; ++i)
	{
		int Tmp = A[i];
		for(j = i; j > 0 && A[j-1] > Tmp; --j)
			A[j] = A[j-1];
		A[j] = Tmp;
	}
}

int main()
{
	int A[10], i;
	for(i = 0; i < 10; ++i)
		scanf("%d", &A[i]);
	InsertSort(A, 10);
	for(i = 0; i < 10; ++i)
		printf("%d ", A[i]);

	return 0;
}
