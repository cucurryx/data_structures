# code of Data Structures
部分基础数据结构以及基本操作函数-c代码实现
包括 list, stack, queue, tree, AvlTree, HashTable(HashQuad and HashSep), heap

> for example, The **Insert()** of AvlTree

  ```
  AvlTree Insert(Item X, AvlTree T)
  {
	  if(T == NULL)
	  {
		  T = (AvlTree)malloc(sizeof(AvlNode));
		  if(T == NULL)
			  Error(0);
		  else
		  {
			  T->item = X;
			  T->height = 0;
			  T->left = NULL;
			  T->right = NULL;
		  }
	  }
	  else if(X < T->item)
	  {
		  T->left = Insert(X, T->left);
		  if(Height(T->left) - Height(T->right) == 2)
		  {
			  if(X < T->left->item)
				  T = SingleRotateWithLeft(T);
			  else
				  T = DoubleRotateWithLeft(T);
		  }
	  }
	  else if(X > T->item)
	  {
		  T->right = Insert(X, T->right);
		  if(Height(T->right) - Height(T->left) == 2)
		  {
			  if(X > T->right->item)
				  T = SingleRotateWithRight(T);
			  else
				  T = DoubleRotateWithRight(T);
		  }
	  }

	  T->height = Max(Height(T->left), Height(T->right)) + 1;
	  return T;
  }
  ```

  在**散列**（hash table）的实现中，为了解决冲突的问题，采用了两种方法
  - 使用链表的方法，将被哈希函数分到同一个cell中的元素放在一个链表中。所以该数据结构涉及到两种数据结构的实现。
  - 使用开放定址法，在遇到冲突后，再进行探测（包含线性探测和平方探测），如果填的太满，则rehash

> 方法1的insert（）函数

  ```
  Position Find(Item Key, HashTable H)
  {
  	Position P;
  	List L;

  	L = H->TheLists[Hash(Key, H->TableSize)];
  	P = L->next;
  	while(P != NULL && P->item != Key)
  		P = P->next;
  	return P;
  }

  ```

  > 方法2的Find（）函数

  ```
  Position Find(Item Key, HashTable H)
  {
  	Position CurrentPos;
  	int CountNum;

  	CountNum = 0;
  	CurrentPos = Hash(Key, H->TableSize);
  	while(H->TheCells[CurrentPos].info != Empty &&
  		  H->TheCells[CurrentPos].item != Key)
  	{
  		CurrentPos += 2 * ++CountNum - 1;
  		if(CurrentPos >= H->TableSize)
  			CurrentPos -= H->TableSize;
  	}

  	return CurrentPos;
  }
  ```

  >二叉堆(heap)指的是完全二叉树，即每个节点都有两个儿子。

  **二叉堆的实现实际上是通过线性的整块内存，而不是指针实现**，因为元素之间存在很强的规律性，比如位置i的父亲一定是在i/2位置，而这个节点的左、右儿子分别是在 2*i、 2*i+1。
