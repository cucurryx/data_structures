# code of Data Structures
部分基础数据结构以及基本操作函数-c代码实现
包括 list, stack, queue, tree, AvlTree, HashTable(HashQuad and HashSep)

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
