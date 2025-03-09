#include "avl.h"
using namespace std;

Node *AVL::left_rotation(Node *x)
{ // if right->right
        Node *y;
        Node *z;
        if (x == NULL)
                return x;

        if (x->right)
                y = x->right;
        else
                return x;

        if (y->right)
                z = y->right;
        else
                return x;

        Node *temp = y->left;
        y->left = x;
        x->right = temp;

        return y;
}

Node *AVL::right_rotation(Node *x)
{ // if left->left
        Node *y;
        Node *z;
        if (x == NULL)
                return x;

        if (x->left)
                y = x->left;
        else
                return x;

        if (y->left)
                z = y->left;
        else
                return x;

        Node *temp = y->right;
        y->right = x;
        x->left = temp;

        return y;
}

Node *AVL::left_right_rotation(Node *x)
{
        if (x == NULL || x->left == NULL)
                return x;

        x->left = left_rotation(x->left);

        return right_rotation(x);
}

Node *AVL::right_left_rotation(Node *x)
{
        if (x == NULL || x->right == NULL)
                return x;

        x->right = right_rotation(x->right);

        return left_rotation(x);
}

void AVL::balance_tree(Node *&root)
{
        if (root == NULL)
        {
                return;
        }

        int balFactor = root->balancing_factor();

        if (balFactor < 1)
                return;
}