#include<iostream>
#include<algorithm>
using namespace std;

template <typename T>
class treeNode
{
public:
	void operator=(const treeNode &_node)
	{
		parent = _node.parent;
		left = _node.left;
		right = _node.right;
		element = _node.element;
		isRed = _node.isRed;
	}
	treeNode():	parent(NULL), left(NULL), right(NULL){}
public:
	treeNode *parent;
	treeNode *left;
	treeNode *right;
	T element;
	bool isRed;
};

template <typename T>
class RBtree
{
	friend class treeNode<T>;
public:
	RBtree();
	size_t getSize();
	treeNode<T> *find(const T &val, treeNode<T>* node);
	bool empty();
	void insert(const T &val, treeNode<T>* node);
	treeNode<T>* rootNode() {return root;};
	treeNode<T>* erase(const T &val, treeNode<T>* node);
private:
	treeNode<T> *findMin(treeNode<T>* node);
	treeNode<T> *findMax(treeNode<T>* node);
	void leftRotate(treeNode<T>* node);
	void rightRotate(treeNode<T>* node);
	void fixInsert(treeNode<T>* node);
	void fixErase(treeNode<T>* node);
	void freeTree(treeNode<T>* node);
	treeNode<T> *root;
	size_t size;
};

template <typename T>
RBtree<T>::RBtree()
{
	root = new treeNode<T>;
	root->isRed = false;
	size = 0;
}

template <typename T>
size_t RBtree<T>::getSize()
{
	return size;
}

template <typename T>
treeNode<T> *find(const T &val, treeNode<T>* node)
{
	if(node == NULL)
		return NULL;
	if(val < node->element)
		return find(val, node->left);
	else if(val > node->element)
		return find(val, node->right);
	else
		return node;
}

template <typename T>
bool RBtree<T>::empty()
{
	return size == 0;
}

template <typename T>
void RBtree<T>::insert(const T &val, treeNode<T> *node)
{
	treeNode<T>* pos = root;
	if(node == NULL)
	{
		node = new treeNode<T>;
		node->left = NULL;
		node->right = NULL;
		node->parent = pos->parent;
	    node->element = val;
		node->isRed = true;
		fixInsert(node);
	}
	else if(val < root->element)
	{
		insert(val, node->left);
		pos = pos->left;
	}
	else if(val > root->element)
	{
		insert(val, node->right);
		pos = pos->right;
	}
}

template <typename T>
treeNode<T>* RBtree<T>::erase(const T &val, treeNode<T>* node)
{
	if(node == NULL)
		return NULL;
	else if(val < node->element)
		erase(val, node->left);
	else if(val > node->element)
		erase(val, node->right);
	else if(node->left && node->right)
	{
		treeNode<T> tmp = findMin(node->right);
		node->element = tmp->element;
		erase(val, node->right);
	}
	else
	{
		treeNode<T> tmp = node;
		fixErase(node);
		if(node->left == NULL)
		{
			node->right->parent = node->parent;
			node = node->right;
		}
		if(node->right == NULL)
		{
			node->left->parent = node->parent;
			node = node->left;
		}
		free(tmp);
		return node;
	}
}

template <typename T>
treeNode<T> *RBtree<T>::findMin(treeNode<T>* node)
{
	if(node->left == NULL)
		return node;
	else
		return findMin(node->left);
}

template <typename T>
treeNode<T> *RBtree<T>::findMax(treeNode<T>* node)
{
	if(node->right == NULL)
		return node;
	else
		return findMax(node->right);
}

template <typename T>
void RBtree<T>::leftRotate(treeNode<T>* node)
{
	treeNode<T>* tmp = node->right;
	node->right = tmp->left;
	if(tmp->left != NULL)
		tmp->left->parent = node;
	tmp->parent = node->parent;
	if(node->parent == NULL)
		root = tmp;
	else
	{
		if(node->parent->left == node)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
	}
	tmp->left = node;
	node->parent = tmp;
}

template <typename T>
void RBtree<T>::rightRotate(treeNode<T>* node)
{
	treeNode<T>* tmp = node->left;
	node->left = tmp->right;
	if(tmp->right != NULL)
		tmp->left->parent = node;
	tmp->parent = node->parent;
	if(node->parent == NULL)
		root = tmp;
	else
	{
		if(node->parent->left == node)
			node->parent->left = tmp;
		else
			node->parent->right = tmp;
	}
	tmp->right = node;
	node->parent = tmp;
}

template <typename T>
void RBtree<T>::fixInsert(treeNode<T>* node)
{
	while(node->parent->isRed)
	{
		if(node->parent->parent->left == node->parent)
		{
			treeNode<T>* uncle = node->parent->parent->right;
			if(uncle == NULL)
			{
				if(node->parent->left == node)
				{
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					rightRotate(node->parent->parent);
				}
				else
				{
					node->isRed = false;
					node->parent->parent->isRed = true;
					leftRotate(node->parent);
					rightRotate(node->parent);
				}
			}
			else if(uncle->isRed)
			{
				node->parent->parent->isRed = true;
				node->parent->isRed = false;
				uncle->isRed = false;
			}
		}
		else
		{
			treeNode<T>* uncle = node->parent->parent->left;
			if(uncle == NULL)
			{
				if(node->parent->right == node)
				{
					node->parent->isRed = false;
					node->parent->parent->isRed = true;
					leftRotate(node->parent->parent);
				}
				else
				{
					node->isRed = false;
					node->parent->parent->isRed = true;
					rightRotate(node->parent);
					leftRotate(node->parent);
				}
			}
			else if(uncle->isRed)
			{
				node->parent->parent->isRed = true;
				node->parent->isRed = false;
				uncle->isRed = false;
			}
		}
	}
}

template <typename T>
void RBtree<T>::fixErase(treeNode<T>* node)
{
	while(node->isRed = false)
	{
		if(node->parent->left == node)
		{
			treeNode<T>* brother = node->parent->right;
			if(brother->isRed == true)
			{
				node->parent->isRed = true;
				node->parent->right->isRed = false;
				leftRotate(node->parent);
			}
			else if((brother->left->isRed || brother->right->isRed) == false)
			{
				brother->isRed = true;
				fixErase(node->parent);
			}
			else if(brother->left->isRed && !brother->right->isRed)
			{
				brother->left->isRed = false;
				brother->isRed = true;
				rightRotate(brother);
			}
			else if(!brother->left->isRed && brother->right->isRed)
			{
				leftRotate(node->parent);
			}
		}
		else
		{
			treeNode<T>* brother = node->parent->left;
			if(brother->isRed == true)
			{
				node->parent->isRed = true;
				brother->isRed = false;
				leftRotate(node->parent);
			}
			else if((brother->left->isRed || brother->right->isRed) == false)
			{
				brother->isRed = true;
				fixErase(node->parent);
			}
			else if(brother->right->isRed && !brother->left->isRed)
			{
				brother->right->isRed = false;
				brother->isRed = true;
				leftRotate(brother);
			}
			else if(!brother->right->isRed && brother->left->isRed)
			{
				rightRotate(node->parent);
			}
		}
	}
}

template <typename T>
void RBtree<T>::freeTree(treeNode<T>* node)
{
	if(node == NULL)
		return ;
	freeTree(node->left);
	freeTree(node->right);
	delete node;
}
