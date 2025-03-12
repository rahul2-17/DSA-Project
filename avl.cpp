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

Node* AVL::search(Node* root, int rollNo)
{
        if(root == NULL)
        {
                return NULL;
        }
        
        if(root->data == rollNo)
        {
                return root;
        }

        if(root->data < rollNo)
        {
                return search(root->left, rollNo);
        }

        else return search(root->right, rollNo);
}

void AVL::deleteNode(Node* &root, int rollNo){
        Node* loc = search(root, rollNo);

        if(loc == NULL)
                 return;

        if(loc->p == NULL){
                
        }

        //no children
        if(!loc->left && !loc->right){
                loc->p->left = NULL;
                loc->p->right = NULL;
                delete  loc;
        }

        //only 1 child

        if(loc->data >loc->p->data){
                if(!loc->left && loc->right){
                        loc->p->right = loc->right;
                        delete loc;
                }
                        
                else if(loc->left && !loc->right){
                        loc->p->right = loc->left;
                        delete loc;
                }

                else if(loc->left && loc->right){
                        
                }
        }

        if(loc->data < loc->p->data){
                if(!loc->left && loc->right){
                        loc->p->left = loc->right;
                        delete loc;
                }
                        
                else if(loc->left && !loc->right){
                        loc->p->left = loc->left;
                        delete loc;
                }
        }

        //2 children
                
}
