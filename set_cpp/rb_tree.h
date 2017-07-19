//
// Created by xvvx on 17-7-19.
//

#ifndef SET_CPP_RB_TREE_H
#define SET_CPP_RB_TREE_H
#include<iostream>
#include<iomanip>
using namespace std;

typedef bool rb_tree_color;
typedef double T;
static bool RED = false;
static bool BLACK = true;

class rb_tree_node
{
public:
    T key;
    rb_tree_color color;
    rb_tree_node *left;
    rb_tree_node *right;
    rb_tree_node *parent;

    rb_tree_node(T _key, rb_tree_color _color, rb_tree_node* _left,
		rb_tree_node* _right, rb_tree_node* _parent):
            key(_key), color(_color), left(_left), right(_right), parent(_parent){}
};

class rb_tree
{
public:
    rb_tree();
    ~rb_tree();

    void pre_order_print();

	void post_order_print();

    int size();
    bool empty();
    rb_tree_node* search(T key);
    T mininum();
    T maxinum();

    void insert(T key);
    void remove(T key);
    void destroy();
    void print();

private:
    void pre_order_print(rb_tree_node* tree) const;
    void in_order_print(rb_tree_node* tree) const;
    void post_order_print(rb_tree_node* tree) const;

    rb_tree_node* search(rb_tree_node* tree, T key) const;
    rb_tree_node* mininum(rb_tree_node* tree);
    rb_tree_node* maxinum(rb_tree_node* tree);

    void rb_left_rotate(rb_tree_node* &root, rb_tree_node* x);
    void rb_right_rotate(rb_tree_node* &root, rb_tree_node* x);
    void insert(rb_tree_node* &root, rb_tree_node* x);
    void insert_fixup(rb_tree_node* &root, rb_tree_node* x);
    void remove(rb_tree_node* &root, rb_tree_node* x);
    void remove_fixup(rb_tree_node* &root, rb_tree_node* x, rb_tree_node* parent);
    void destroy(rb_tree_node* &tree);
    void print(rb_tree_node* tree, T key, int direction);

private:
    int rb_tree_count;
    rb_tree_node *root;
};

#endif //SET_CPP_RB_TREE_H

