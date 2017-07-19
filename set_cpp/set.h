//
// Created by xvvx on 17-7-19.
//
#include "rb_tree.h"

#ifndef SET_CPP_SET_H
#define SET_CPP_SET_H
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
    bool contain(const T&);
    int size();
    void print();
private:
    rb_tree tree;
};
#endif //SET_CPP_SET_H
