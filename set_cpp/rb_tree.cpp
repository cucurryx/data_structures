//
// Created by xvvx on 17-7-19.
//

#include "rb_tree.h"
//public functions

rb_tree::rb_tree(): root(NULL), rb_tree_count(0){}
rb_tree::~rb_tree(){ destroy(); }

int rb_tree::size()
{
    return rb_tree_count;
}

bool rb_tree::empty()
{
    return rb_tree_count == 0;
}

rb_tree_node* rb_tree::search(T key)
{
    return search(root, key);
}

T rb_tree::mininum()
{
    rb_tree_node* min_node = mininum(root);

    if(min_node == NULL)
    {
        cout<<"Error: mininum return NULL"<<endl;
        return (T)NULL;
    }
    return min_node->key;
}

T rb_tree::maxinum()
{
    rb_tree_node* max_node = maxinum(root);

    if(max_node == NULL)
    {
        cout<<"Error: maxinum return NULL"<<endl;
        return (T)NULL;
    }
    return max_node->key;
}

void rb_tree::insert(T key)
{
    rb_tree_node* new_node =  new rb_tree_node(key, BLACK, NULL, NULL, NULL);
    if(search(key) == NULL)
    {
        ++rb_tree_count;
        insert(root, new_node);
    }
}

void rb_tree::remove(T key)
{
    rb_tree_node* node;
    if((node = search(root, key)) != NULL)
    {
        remove(root, node);
        --rb_tree_count;
    }
}

void rb_tree::destroy()
{
    destroy(root);
    rb_tree_count = 0;
}

void rb_tree::print()
{
    if(root != NULL)
        print(root, root->key, 0);
}

//private functions

void rb_tree::pre_order_print(rb_tree_node* tree) const
{
    if(tree != NULL)
    {
        cout<<tree->key<<" ";
        pre_order_print(tree->left);
        pre_order_print(tree->right);
    }
}

void rb_tree::in_order_print(rb_tree_node* tree) const
{
    if(tree != NULL)
    {
        in_order_print(tree->left);
        cout<<tree->key<<" ";
        in_order_print(tree->right);
    }
}

void rb_tree::post_order_print(rb_tree_node* tree) const
{
    if(tree != NULL)
    {
        post_order_print(tree->left);
        post_order_print(tree->right);
        cout<<tree->key<<" ";
    }
}

rb_tree_node* rb_tree::search(rb_tree_node* tree, T key) const
{
    if(tree == NULL)
        return NULL;
    if(key == tree->key)
        return tree;

    if(key < tree->key)
        return search(tree->left, key);
    else if(key > tree->key)
        return search(tree->right, key);
    return nullptr;
}

rb_tree_node* rb_tree::mininum(rb_tree_node* tree)
{
    if(tree == NULL)
        return NULL;
    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

rb_tree_node* rb_tree::maxinum(rb_tree_node* tree)
{
    if(tree == NULL)
        return tree;
    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

void rb_tree::rb_left_rotate(rb_tree_node* &root, rb_tree_node* x)
{
    rb_tree_node* y = x->right;

    x->right = y->left;
    if(y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rb_tree::rb_right_rotate(rb_tree_node* &root, rb_tree_node* x)
{
    rb_tree_node* y = x->left;

    x->left = y->right;
    if(y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;
    if(x->parent == NULL)
        root = y;
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

//four cases
void rb_tree::insert(rb_tree_node* &root, rb_tree_node* node)
{
    rb_tree_node* x = root;
    rb_tree_node* x_parent = NULL;

    while(x != NULL)
    {
        x_parent = x;
        if(node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = x_parent;
    if(x_parent != NULL)
    {
        if(node->key < x_parent->key)
            x_parent->left = node;
        else
            x_parent->right = node;
    }
    else
        root = node;

    node->color = RED;
    insert_fixup(root, node);
}

void rb_tree::insert_fixup(rb_tree_node* &root, rb_tree_node* node)
{
    rb_tree_node* parent, *g_parent;
    while((parent = node->parent) && parent->color == RED)
    {
        g_parent = node->parent->parent;

        if(parent == g_parent->left)
        {
            //1.uncle exist and his color is red
            if(g_parent->right != NULL && g_parent->right->color == RED)
            {
                g_parent->color = RED;
                g_parent->left->color = BLACK;
                g_parent->right->color = BLACK;
                node = g_parent;
                continue;
            }
            //2.uncle is black and node is right child
            if(parent->right == node)
            {
                rb_left_rotate(root, parent);
                rb_tree_node *tmp = parent;
                parent = node;
                node = tmp;
            }
            //3.uncle is black and node is left child
            parent->color = BLACK;
            g_parent->color = RED;
            rb_right_rotate(root, g_parent);
        }
        else // parent == g_parent->right
        {
            // case one
            if(g_parent->left != NULL && g_parent->left->color == RED)
            {
                g_parent->color = RED;
                g_parent->left->color = BLACK;
                g_parent->right->color = BLACK;
                node = g_parent;
                continue;
            }
            // case two: node, parent, g_parent is not int a line
            if(parent->left == node)
            {
                rb_right_rotate(root, parent);
                rb_tree_node* tmp = parent;
                parent = node;
                node = tmp;
            }
            //case three:: node, parent, g_parent is in a line
            parent->color = BLACK;
            g_parent->color = RED;
            rb_left_rotate(root, g_parent);
        }
    }

    root->color = BLACK;
}

void rb_tree::remove(rb_tree_node* &root, rb_tree_node* node)
{
    rb_tree_node *child, *parent;
    rb_tree_color color;

    if(node->left != NULL && node->right != NULL)
    {
        rb_tree_node *replace = node;
        replace = replace->right;
        while(replace->left != NULL)
            replace = replace->left;

        if(node->parent)
        {
            if(node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        }
        else
            root = replace;

        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        if(parent == node)
            parent = replace;
        else
        {
            if(child != NULL)
                child->parent = parent;
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if(color == BLACK)
            remove_fixup(root, child, parent);
        delete node;
        return ;
    }

    if(node->left != NULL)
        child = node->left;
    else
        child = node->right;
    parent = node->parent;
    color = node->color;


    if(child != NULL)
        child->parent = parent;
    if(parent != NULL)
        if(parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    else
        root = child;

    if(color == BLACK)
        remove_fixup(root, child, parent);
    delete node;
}

void rb_tree::remove_fixup(rb_tree_node* &root, rb_tree_node* node, rb_tree_node* parent)
{
    rb_tree_node *other;

    while((!node || node->color == BLACK) && node != root)
    {
        if(parent->left == node)
        {
            other = parent->right;
            if(other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                rb_left_rotate(root, parent);
                other = parent->right;
            }
            if((!other->left || other->left->color == BLACK) &&
               (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if(!other->right || other->right->color == BLACK)
                {
                    other->left->color = BLACK;
                    other->color = RED;
                    rb_right_rotate(root, other);
                    other = parent->right;
                }

                other->color = parent->color;
                parent->color = BLACK;
                other->right->color = BLACK;
                rb_left_rotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if(other->color == RED)
            {
                other->color = BLACK;
                parent->color = RED;
                rb_right_rotate(root, parent);
                other = parent->left;
            }

            if((!other->left || other->left->color == BLACK) &&
               (!other->right || other->right->color == BLACK))
            {
                other->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if(!other->left  || other->left->color == BLACK)
                {
                    other->right->color = BLACK;
                    other->color = RED;
                    rb_left_rotate(root, other);
                    other = parent->left;
                }

                other->color = parent->color;
                parent->color = BLACK;
                other->left->color = BLACK;
                node = root;
                break;
            }
        }
    }

    if(node)
        node->color = BLACK;
}

void rb_tree::destroy(rb_tree_node* &tree)
{
    if(tree == NULL)
        return;
    destroy(tree->left);
    destroy(tree->right);
    delete tree;
    tree = NULL;
}

void rb_tree::print(rb_tree_node* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction == 0) // tree is root
            cout<<setw(4)<<tree->key<<"(B) is root"<<endl;
        else
            cout<<setw(4)<<tree->key<<(tree->color?"(B)":"(R)")<< "is"<<setw(4)<<key<<"'s "<<setw(12)<<
                (direction == 1 ? "right child" : "left child")<<endl;

        print(tree->left, tree->key, -1);
        print(tree->right, tree->key, 1);
    }
}