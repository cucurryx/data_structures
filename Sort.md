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
