#include<stdio.h>
#define Cutoff (3)
typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
	ElementType t = *a;
	*a = *b;
	*b = t;
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Mid = (Left+Right)/2;

	if(A[Left] > A[Mid])
		Swap(&A[Left], &A[Mid]);
	if(A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if(A[Mid] > A[Right])
		Swap(&A[Mid], &A[Right]);

	Swap(&A[Mid], &A[Right-1]);
	return A[Right-1];
}

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

void Qsort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if(Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right -1;
		for(;;)
		{
			while(A[++i] < Pivot);
			while(A[--j] > Pivot);
			if(i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right-1]);

		Qsort(A, Left, i-1);
		Qsort(A, i+1, Right);
	}
	else
		InsertSort(A + Left, Right - Left + 1);
}

void Quicksort(ElementType A[], int N)
{
	Qsort(A, 0, N-1);
}

int main()
{
	int A[10], i;
	for(i = 0; i < 10; ++i)
		scanf("%d", &A[i]);
	Quicksort(A, 10);
	for(i = 0; i < 10; ++i)
		printf("%d ", A[i]);

	return 0;
}
