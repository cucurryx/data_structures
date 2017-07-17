#include<iostream>
#include<algorithm>
using namespace std;

static bool RED = true;
static bool BLACK = false;
//set 需要实现insert(const T&), erase(const T&), clear(), count(const T&), empty(), size(). 钦定数据结构内核为左倾红黑树(LLRB)

template <typename T>
class Node
{
public:
	//Node(): N(0), key(0), left(NULL), right(NULL), color(RED){}
	Node(T _key, int _N, bool _color):
	 	key(_key), N(_N), color(_color), left(NULL), right(NULL){}
	int size(){return N;};
	void printKey()
	{
		cout<<key<<" ";
	}
public:
	int N;
	T key;
	Node *left, *right;
	bool color;
};

template <typename T>
class RedBlackBST
{
public:
	RedBlackBST(): root(NULL){}
	void insert(const T&);
	Node<T>* insert(Node<T>*, const T&);
	Node<T>* find(Node<T>*, const T&);
	Node<T>* find(const T&);
	Node<T>* findMin(Node<T>*);
	Node<T>* findMax(Node<T>*);
	Node<T>* findMin();
	Node<T>* findMax();
	void deleteKey(const T&);
	Node<T>* deleteKey(Node<T>*, const T&);
	void deleteMin();
	Node<T>* deleteMin(Node<T>*);
	void deleteMax();
	Node<T>* deleteMax(Node<T>*);
	void clear();
	void clear(Node<T>* &);
	int count(const T&);
	bool empty();
	int size();
	int size(Node<T>* h);
	void print();
	void print(Node<T>*);

private:
	Node<T>* root;
	bool isRed(Node<T>* h);
	Node<T>* rotateLeft(Node<T>* h);
	Node<T>* rotateRight(Node<T>* h);
	void flipColors(Node<T>* h);
	Node<T>* balance(Node<T>* h);
	Node<T>* moveRedLeft(Node<T>*);
	Node<T>* moveRedRight(Node<T>*);
};

template <typename T>
bool RedBlackBST<T>::isRed(Node<T>* x)
{
	if(x == NULL)
		return false;
	return x->color == RED;
}

template <typename T>
Node<T>* RedBlackBST<T>::rotateLeft(Node<T>* h)
{
	Node<T>* x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	x->N = h->N;
	h->N = 1 + size(h->left) + size(h->right);
	return x;
}

template <typename T>
Node<T>* RedBlackBST<T>::rotateRight(Node<T>* h)
{
	Node<T>* x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	x->N = h->N;
	h->N = 1 + size(h->left) + size(h->right);
	return x;
}

template <typename T>
void RedBlackBST<T>::flipColors(Node<T>* h)
{
	h->color = RED;
	h->left->color = BLACK;
	h->right->color = BLACK;
}

template <typename T>
Node<T>* RedBlackBST<T>::balance(Node<T>* h)
{
	if(isRed(h->right) && !isRed(h->left))
		h = rotateLeft(h);
	if(isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if(isRed(h->left) && isRed(h->right))
		flipColors(h);

	h->N = size(h->left) + size(h->right) + 1;
	return h;
}

template <typename T>
void RedBlackBST<T>::insert(const T& key)
{
	root = insert(root, key);
	root->color = BLACK;
}

template <typename T>
Node<T>* RedBlackBST<T>::insert(Node<T>* h, const T& key)
{
	if(h == NULL)
		return new Node<T>(key, 1, RED);
	if(key < h->key)
		h->left = insert(h->left, key);
	else if(key > h->key)
		h->right = insert(h->right, key);
	return balance(h);
}

template <typename T>
Node<T>* RedBlackBST<T>::find(const T& key)
{
	return find(root, key);
}

template <typename T>
Node<T>* RedBlackBST<T>::find(Node<T>* root, const T& key)
{
	if(root == NULL)
		return NULL;
	else if(key < root->key)
		return find(root->left, key);
	else if(key > root->key)
		return find(root->right, key);
}

template <typename T>
Node<T>* RedBlackBST<T>::findMin()
{
	return findMin(root);
}

template <typename T>
Node<T>* RedBlackBST<T>::findMin(Node<T>* root)
{
	if(root == NULL)
		return NULL;
	else if(root->left == NULL)
		return root;
	else
		return findMin(root->left);
}

template <typename T>
Node<T>* RedBlackBST<T>::findMax()
{
	return findMax(root);
}

template <typename T>
Node<T>* RedBlackBST<T>::findMax(Node<T>* root)
{
	if(root == NULL)
		return NULL;
	else if(root->right == NULL)
		return root;
	else
		return findMax(root->right);
}

template <typename T>
void RedBlackBST<T>::deleteKey(const T& key)
{
	if(root == NULL)
		return ;
	if(!isRed(root->left) && !isRed(root->right))
		root->color = RED;
	root = deleteKey(root, key);
	if(!empty())
		root->color = BLACK;
}

template <typename T>
Node<T>* RedBlackBST<T>::deleteKey(Node<T>* root, const T& key)
{
	if(key < root->key)
	{
		if(!isRed(root->left) && !isRed(root->left->left))
			root = moveRedLeft(root);
		root->left = deleteKey(root->left, key);
	}
	else
	{
		if(isRed(root->left))
			root = rotateRight(root);
		if(key == root->key && root->right == NULL)
			return NULL;
		if(!isRed(root->right) && !isRed(root->right->left))
			root = moveRedRight(root);
		if(key == root->key)
		{
			root->key = findMin(root->right)->key;
			root->right = deleteMin(root->right);
		}
		else
			root->right = deleteKey(root->right, key);
	}
	return balance(root);
}

template <typename T>
Node<T>* RedBlackBST<T>::moveRedLeft(Node<T>* root)
{
	root->color = BLACK;
	root->left->color = RED;
	root->right->color = RED;
	if(isRed(root->right->left))
	{
		root->right = rotateRight(root->right);
		root = rotateLeft(root);
	}
	return root;
}

template <typename T>
Node<T>* RedBlackBST<T>::moveRedRight(Node<T>* root)
{
	root->color = BLACK;
	root->left->color = RED;
	root->right->color = RED;
	if(!isRed(root->left->left))
		root = rotateRight(root);
	return root;
}

template <typename T>
void RedBlackBST<T>::deleteMin()
{
	if(root == NULL)
		return;
	if(!isRed(root->left) && !isRed(root->right))
		root->color = RED;
	root = deleteMin(root);
	if(!empty())
		root->color = BLACK;
}

template <typename T>
Node<T>* RedBlackBST<T>::deleteMin(Node<T>* root)
{
	if(root->left == NULL)
		return NULL;
	if(!isRed(root->left) && !isRed(root->left->left))
		root = moveRedLeft(root);
	root->left = deleteMin(root->left);
	return balance(root);
}

template <typename T>
void RedBlackBST<T>::deleteMax()
{
	if(root == NULL)
		return;
	if(isRed(root->left) && !isRed(root->right))
		root->color = RED;
	root = deleteMax(root);
	if(!empty())
		root->color = BLACK;
}

template <typename T>
Node<T>* RedBlackBST<T>::deleteMax(Node<T>* root)
{
	if(isRed(root->left))
		root = rotateRight(root);
	if(root->right == NULL)
		return NULL;
	if(!isRed(root->right) && !isRed(root->right->left))
		root = moveRedRight(root);
	root->right = deleteMax(root->right);
	return balance(root);
}

template <typename T>
void RedBlackBST<T>::clear()
{
	clear(root);
}

template <typename T>
void RedBlackBST<T>::clear(Node<T>* &root)
{
	if(root == NULL)
		return ;
	clear(root->left);
	clear(root->right);
	delete root;
	root = NULL;
}

template <typename T>
int RedBlackBST<T>::count(const T& key)
{
	if(find(key) == NULL)
		return 0;
	return 1;
}

template <typename T>
bool RedBlackBST<T>::empty()
{
	return size() == 0;
}

template <typename T>
int RedBlackBST<T>::size()
{
	return size(root);
}

template <typename T>
int RedBlackBST<T>::size(Node<T>* h)
{
	if(h == NULL)
		return 0;
	return h->N;
}

template <typename T>
void RedBlackBST<T>::print()
{
	print(root);
}

template <typename T>
void RedBlackBST<T>::print(Node<T>* root)
{
	if(root == NULL)
		return ;
	print(root->left);
	root->printKey();
	print(root->right);
}
