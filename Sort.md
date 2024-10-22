# 常见排序算法


## Insertsort
**插入排序** 就是比较前面的值，然后找到合适的位置插入。
```
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
```

## Shellsort
>N个互异数的数组的平均逆序数是N(N-1)/4，因为反序的逆序数是N(N-1)/2

所以任何通过交换相邻元素进行的排序算法平均需要Ω(N*N)时间
所以我们如果要得到一个突破二次时间的排序算法，需要对相距较远的元素进行比较和交换，这样才能保证每次交换删除不止一个逆序。

**希尔排序(Shellsort)** 就是这样的一类算法，通过比较一定间隔的元素来工作，各趟比较所用的距离随着算法的进行而减小，因此希尔排序也称为 **缩小增量排序**
Shell建议的增量序列是H[1] = N/2, H[k] = H[k+1]/2。希尔排序的性能很大的程度取决于增量序列的选取，有些增量序列可以保证最坏情形O(N^1.5)。

```
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
```

## Heapsort
**堆排序(Heapsort)** 利用建立二叉堆的基本方法，然后执行DeleteMin的操作。建立二叉堆是O(N),而每次DeleteMin操作的时间花费是O(logN)，因此总的运行时间是O(N logN)。这个算法是用数组来模拟二叉堆，然后将DeleteMin的结果放在数组的结尾，最后可以得到一个有序数列。

堆排序总是使用至少NlogN - O(N)次比较，平均情形2NlogN - O(N)，不过平均情形还没有得到证明。

```
void Heapsort(ElementType A[], int N)
{
	int i;
	for(i = N/2; i >= 0; i--)
		PercDown(A, i, N);    //整理i位置的子堆，使其具有堆序性
	for(i = N-1; i > 0; --i)
	{
		Swap(&A[0], &A[i]);   //删除最大并放在数组末尾
		PercDown(A, 0, i);    //整理删除最大元素后的堆，使其具有堆序性
	}
}
```

## Mergesort
**归并排序(Mergesort)** 以O(NlogN)最坏情形运行时间运行，几乎是最优的，采用了递归算法来实现。基本操作就是合并两个已排序的表，得到一个排序了的序列。合并两个已排序的表的时间是线性的。

```
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
```

## Quicksort
**快速排序(Quicksort)** 是已知最快的排序算法，和归并排序一样，都是分治的策略。基本算法由四个简单的步骤组成：

1. 如果数列中元素的个数是0或者1，则返回
2. 数列中任取元素作为枢纽元
3. 将数列（除去枢纽元）分为两个部分，分别是大于枢纽元的部分和小于枢纽元的部分
4. 递归求解

```
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
```
