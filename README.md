# code of Data structures
the formal data structures writte in C
including list, stack, queue, tree, AvlTree, HashTable and so on
and I just write some fundamental functions
>for example, The **Insert()** of AvlTree
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
