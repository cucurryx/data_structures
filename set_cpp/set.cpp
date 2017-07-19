//
// Created by xvvx on 17-7-19.
//
#include "set.h"

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
    tree.remove(tree.mininum());
}

void Set::deleteMax()
{
    tree.remove(tree.maxinum());
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

bool Set::contain(const T& val)
{
    return tree.search(val) != NULL;
}

int Set::size()
{
    return tree.size();
}

void Set::print()
{
    tree.print();
}

