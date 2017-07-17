#include"RBtree.h"

template <typename T>
class Set
{
public:
	Set();
	~Set(){}
	bool add(const T& key);
	bool contains(const T& key);
	bool remove(const T& key);
	bool isEmpty();
	size_t size();
	void clear();
private:
	RBtree<T>* tree;
	size_t count;
};

template <typename T>
Set<T>::Set()
{
	tree = new RBtree<T>;
	count = 0;
}

template <typename T>
bool Set<T>::add(const T& key)
{
	if(contains(key))
		return false;
	tree->insert(key, tree->rootNode());
	++count;
	return true;
}

template <typename T>
bool Set<T>::contains(const T& key)
{
	treeNode<T>* node = find(key, tree->rootNode());
	return node != NULL;
}

template <typename T>
bool Set<T>::remove(const T& key)
{
	if(!contains(key))
		return false;
	tree->erase(key, *tree);
	--count;
	return true;
}

template <typename T>
bool Set<T>::isEmpty()
{
	return count == 0;
}

template <typename T>
size_t Set<T>::size()
{
	return count;
}

template <typename T>
void Set<T>::clear()
{
	tree->freeTree(*tree);
	count = 0;
}
