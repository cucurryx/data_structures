#include<iostream>
#include<algorithm>
using namespace std;
using T = double;

//树节点
class Node
{
public:
	Node(T _key, int _N):
	 	key(_key), N(_N), left(NULL), right(NULL){}
	int size(){return N;};
public:
	int N;
	T key;
	Node *left, *right;
};

//树
class BinaryTree
{
public:
	BinaryTree(): root(NULL){}
	void insert(const T&);
	Node* insert(Node*, const T&);
	Node* find(Node*, const T&);
	Node* find(const T&);
	Node* findMin(Node*);
	Node* findMax(Node*);
	Node* findMin();
	Node* findMax();
	void deleteKey(const T&);
	Node* deleteKey(Node*, const T&);
	void deleteMin();
	Node* deleteMin(Node*);
	void deleteMax();
	Node* deleteMax(Node*);
	void clear();
	void clear(Node* &);
	int count(const T&);
	bool empty();
	int size();
	int size(Node* h);
	void print();
	void print(Node*);

private:
	Node* root;
};


void BinaryTree::insert(const T& key)
{
	root = insert(root, key);
}

Node* BinaryTree::insert(Node* root, const T& key)
{
	if(root == NULL)
		return new Node(key, 1);
	if(key < root->key)
		root->left = insert(root->left, key);
	else if(key > root->key)
		root->right = insert(root->right, key);
	return root;
}

Node* BinaryTree::find(const T& key)
{
	return find(root, key);
}

Node* BinaryTree::find(Node* root, const T& key)
{
	if(root == NULL)
		return NULL;
	if(key < root->key)
		return find(root->left, key);
	else if(key > root->key)
		return find(root->right, key);
	else if(key == root->key)
		return root;
}

Node* BinaryTree::findMin()
{
	return findMin(root);
}

Node* BinaryTree::findMin(Node* root)
{
	if(root == NULL)
		return NULL;
	if(root->left == NULL)
		return root;
	else
		return findMin(root->left);
}

Node* BinaryTree::findMax()
{
	return findMax(root);
}

Node* BinaryTree::findMax(Node* root)
{
	if(root == NULL)
		return NULL;
	if(root->right == NULL)
		return root;
	else
		return findMax(root->right);
}

void BinaryTree::deleteKey(const T& key)
{
	root = deleteKey(root, key);
}

Node* BinaryTree::deleteKey(Node* root, const T& key)
{
	if(root == NULL)
		return NULL;
	if(key < root->key)
		root->left = deleteKey(root->left, key);
	else if(key > root->key)
		root->right = deleteKey(root->right, key);
	else if(root->left && root->right)
	{
		root->key = findMin(root->right)->key;
		root->right = deleteMin(root->right);
	}
	else
	{
		Node* tmp = root;
		if(root->right == NULL)
			root = root->left;
		if(root->left == NULL)
			root = root->right;
		delete tmp;
	}
	return root;
}

void BinaryTree::deleteMin()
{
	root = deleteMin(root);
}

Node* BinaryTree::deleteMin(Node* root)
{
	if(root->left == NULL)
		return NULL;
	root->left = deleteMin(root->left);
	return root;
}

void BinaryTree::deleteMax()
{
	root = deleteMax(root);
}

Node* BinaryTree::deleteMax(Node* root)
{
	if(root->right == NULL)
		return NULL;
	root->right = deleteMax(root->right);
	return root;
}

void BinaryTree::clear()
{
	clear(root);
}

void BinaryTree::clear(Node* &root)
{
	if(root == NULL)
		return;
	clear(root->left);
	clear(root->right);
}

int BinaryTree::count(const T& key)
{
	if(find(key) != NULL)
		return 1;
	return 0;
}

bool BinaryTree::empty()
{
	return size() == 0;
}

int BinaryTree::size()
{
	return size(root);
}

int BinaryTree::size(Node* h)
{
	if(h != NULL)
		return h->N;
	else
		return 0;
}

void BinaryTree::print()
{
	print(root);
}

void BinaryTree::print(Node* root)
{
	cout<<root->key<<" ";
	print(root->left);
	print(root->right);
}
