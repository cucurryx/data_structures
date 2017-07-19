#include "rb_tree.h"
//#include"BinaryTree.h"
//#include"RBtree.h"

class Set
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
private:
	rb_tree tree;
};

void Set::insert(const T& key)
{
	tree.insert(key);
}

void Set::erase(const T& key)
{
	tree.remove(key);
}

void Set::clear()
{
	tree.destroy();
}

void Set::deleteMin()
{
	tree.remove(mininum());
}

void Set::deleteMax()
{
	tree.remove(maxinum());
}

T Set::findMin()
{
	return tree.mininum();
}

T Set::findMax()
{
	return tree.maxinum();
}

int Set::count(const T& key)
{
	if(tree.search(key) == NULL)
		return 0;
	return 1;
}

bool Set::empty()
{
	return tree.empty();
}

int Set::size()
{
	return tree.size();
}
