#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

void Merge(ElementType A[], ElementType TmpArray[], int LeftBgn, int RightBgn, int RightEnd)
{
	int i, LeftEnd, TmpPos, TotalCount;

	LeftEnd = RightBgn-1;
	TmpPos = LeftBgn;
	TotalCount = RightEnd - LeftBgn + 1;

	while(LeftBgn <= LeftEnd && RightBgn <= RightEnd)
	{
		if(A[LeftBgn] <= A[RightBgn])
			TmpArray[TmpPos++] = A[LeftBgn++];
		else
			TmpArray[TmpPos++] = A[RightBgn++];
	}

	while(LeftBgn <= LeftEnd)
		TmpArray[TmpPos++] = A[LeftBgn++];
	while(RightBgn <= RightEnd)
		TmpArray[TmpPos++] = A[RightBgn++];

	for(i = 0; i < TotalCount; i++, RightEnd--)  //copy TmpArray to A
		A[RightEnd] = TmpArray[RightEnd];
}

void Msort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	if(Left < Right)
	{
		int Mid = (Left + Right)/2;
		Msort(A, TmpArray, Left, Mid);
		Msort(A, TmpArray, Mid+1, Right);
		Merge(A, TmpArray, Left, Mid+1, Right);
	}
}

void Mergesort(ElementType A[], int N)
{
	ElementType *TmpArray;
	TmpArray = (ElementType*)malloc(sizeof(ElementType) * N);

	if(TmpArray == NULL)
	{
		printf("Error: out of space!");
		exit(0);
	}
	else
	{
		Msort(A, TmpArray, 0, N-1);
		free(TmpArray);
	}
}

int main()
{
	FILE * fpIn = fopen("input.txt", "rt");
	FILE * fpOut = fopen("output.txt", "wt");
	int i, a[1000000];

	for(i = 0; i < 100000; ++i)
		fscanf(fpIn, "%d", &a[i]);
	Mergesort(a, 100000);
	for(i = 0; i < 100000; ++i)
		fprintf(fpOut, "%d ", a[i]);
	printf("Finished");

	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
/*
int main()
{
	int A[10], i;
	for(i = 0; i < 10; ++i)
		scanf("%d", &A[i]);
	Mergesort(A, 10);
	for(i = 0; i < 10; ++i)
		printf("%d ", A[i]);

	return 0;
}
*/
