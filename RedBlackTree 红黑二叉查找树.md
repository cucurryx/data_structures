# RedBlackTree 红黑二叉查找树


##定义
> 相比二叉查找树，红黑树的每个结点多了颜色信息，并且满足下面条件：
> 1. 每个结点都需要被着色， 红/黑。
> 2. 根节点root为黑色。
> 3. 红色节点的子节点必须为黑色。
> 4. 从任意一个节点到NULL的所有路径上，黑色节点数相同


红黑树背后的思想是用标准的二叉查找树（完全由2-结点构成）和一些额外的信息来表示2-3树。
红色链接：表示两个2-结点连接起来称为一个3-结点
黑色连接：表示2-3树中的普通链接
并将链接存储在链接的两个元素的儿子结点中，并且要求红色链接只能是左斜的。

## Search搜索元素
由于搜索并不需要涉及到结点的颜色，所以同普通二叉树。
```
rb_tree_node* rb_tree::search(rb_tree_node* tree, T key) const
{
    if(tree == NULL || key == tree->key)
        return tree;

    if(key < tree->key)
        return search(tree->left, key);
    else if(key > tree->key)
        return search(tree->right, key);
}
```




##  Insert 插入元素
插入元素和普通二叉树过程相同，只是在插入后需要对树进行调整来使其满足树平衡的条件。


### 版本1

```
// 版本1， 根据stl源码剖析
void rb_tree::insert(rb_tree_node* &root, rb_tree_node* node)
{
    rb_tree_node* x = root;
    rb_tree_node* x_parent = NULL;
    
    while(x != NULL)
    {
        x_parent = x;
        if(node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = x_parent;
    if(x_parent != NULL)
    {
        if(node->key < x_parent->key)
            x_parent->left = node;
        else
            x_parent->right = node;
    }
    else
        root = node;

    node->color = RED;
    insert_fixup(root, node);
}
```

### 版本2
```
//版本2， 根据算法4-edtion中的Java代码改编
Node* RedBlackBST::insert(Node* h, const T& key)
{
	if(h == NULL)
		return new Node(key, 1, RED);
	if(key < h->key)
		h->left = insert(h->left, key);
	else if(key > h->key)
		h->right = insert(h->right, key);

	if(isRed(h->right) && !isRed(h->left))
		h = rotateLeft(h);
	if(isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if(isRed(h->left) && isRed(h->right))
		flipColors(h);

	h->N = size(h->left) + size(h->right) + 1;
	return h;
}
```
	
### 对树的调整操作
1. **left rotate** 将树向左旋转 
2. **right rotate** 将树向右选装
3. **flip color**  转换结点以及儿子结点的颜色，该操作只在版本二中有使用

#### 版本1中的左旋（右旋只需要换个方向就行）

```
void rb_tree::rb_left_rotate(rb_tree_node* &root, rb_tree_node* x)
{
    rb_tree_node* y = x->right;

    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
```

#### 版本2中的左旋(版本2不需要parent指针，所以相对比较简单)
```
Node* RedBlackBST::rotateLeft(Node* h)
{
	Node* x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	x->N = h->N;
	h->N = 1 + size(h->left) + size(h->right);
	return x;
}
```

#### 版本2中的flipColor
```
void RedBlackBST::flipColors(Node* h)
{
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}
```
因为该函数只有在一个节点的两个儿子都是红色的时候才会用到，此时该节点是黑色，所以等同于
```
void RedBlackBST::flipColors(Node* h)
{
	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}
```

## remove/delete删除节点
> 这个操作比较复杂，敬请期待。