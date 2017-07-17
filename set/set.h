#include<iostream>
#include<algorithm>
using namespace std;

template <typename T>
class treeNode
{
public:
	treeNode():	parent(NULL), left(NULL), right(NULL){}
	treeNode(T _element): parent(NULL), left(NULL),
	right(NULL), element(_element){}
private:
	treeNode *parent;
	treeNode *left;
	treeNode *right;
	T element;
	bool isRed;
};

template <typename T>
class RBtree
{
public:
	RBtree();
	size_t getSize();
	treeNode<T> *find(const T &val, treeNode<T>* node);
	bool empty();
	void insert(const T &val, treeNode<T>* node);
	void erase(const T &val, treeNode<T>* node);
private:
	treeNode<T> *findMin(treeNode<T>* node);
	treeNode<T> *findMax(treeNode<T>* node);
	void leftRotate(treeNode<T>* node);
	void rightRotate(treeNode<T>* node);
	void fixInsert(treeNode<T>* node);
	void fixErase(treeNode<T>* node);
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
treeNode<T> *find(const T &val, treeNode<T> node)
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
	treeNode<T> pos = root;
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
	treeNode<T> tmp = node->right;
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
	treeNode<T> tmp = node->left;
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

}

template <typename T>
void RBtree<T>::fixErase(treeNode<T>* node)
{

}
