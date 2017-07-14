#include<stdio.h>
#define LeftChild(i) ( 2*(i) + 1)
typedef int ElementType;

void Swap(ElementType *a, ElementType *b)
{
	ElementType t = *a;
	*a = *b;
	*b = t;
}

void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;

	for(Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if(Child != N-1 && A[Child] < A[Child+1])
			Child++;
		if(A[Child] > Tmp)
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}

void Heapsort(ElementType A[], int N)
{
	int i;
	for(i = N/2; i >= 0; i--)
		PercDown(A, i, N);
	for(i = N-1; i > 0; --i)
	{
		Swap(&A[0], &A[i]);   //删除最大并放在数组末尾
		PercDown(A, 0, i);    //重新排列最大值的位置
	}
}

int main()
{
	int A[10], i;
	for(i = 0; i < 10; ++i)
		scanf("%d", &A[i]);
	Heapsort(A, 10);
	for(i = 0; i < 10; ++i)
		printf("%d ", A[i]);

	return 0;
}
