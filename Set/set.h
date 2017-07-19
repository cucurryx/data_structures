#include"BinaryTree.h"

//set 需要实现insert(const T&), erase(const T&), clear(), count(const T&), empty(), size()

template <typename T>
class mySet
{
public:
	void insert(const T&);
	void erase(const T&);
	void clear();
	void deleteMin();
	void deleteMax();
	T findMin();
	T findMax();
	int count(const T&);
	bool empty();
	int size();
	void print(){tree.print();};
private:
	RedBlackBST<T> tree;
};

template <typename T>
void mySet<T>::insert(const T& key)
{
	if(tree.count(key) != 0)
		return;
	tree.insert(key);
}

template <typename T>
void mySet<T>::erase(const T& key)
{
	if(tree.count(key) == 0)
		return;
	tree.deleteKey(key);
}

template <typename T>
void mySet<T>::clear()
{
	tree.clear();
}

template <typename T>
void mySet<T>::deleteMin()
{
	tree.deleteMin();
}

template <typename T>
void mySet<T>::deleteMax()
{
	tree.deleteMax();
}

template <typename T>
T mySet<T>::findMin()
{
	return tree.findMin()->key;
}

template <typename T>
T mySet<T>::findMax()
{
	return tree.findMax()->key;
}

template <typename T>
int mySet<T>::count(const T& key)
{
	if(tree.find(key) == NULL)
		return 0;
	return 1;
}

template <typename T>
bool mySet<T>::empty()
{
	return tree.empty();
}

template <typename T>
int mySet<T>::size()
{
	return tree.size();
}
