#include "avl.h"
using namespace std;

Node* AVL::left_rotation(Node* x){ //if right->right
        if(x==NULL)
         return x;
        
        if(x->right)
         Node* y=x->right;
        else
         return x;
        
        if(y->right)
         Node* z=y->right;
         else
          return x;
          
         Node* temp=y->left;
         y->left=x;
         x->right=temp;
         
         return y;
}

Node* AVL::right_rotation(Node* x){ //if left->left
        if(x==NULL)
         return x;
        
        if(x->left)
         Node* y=x->left;
        else
         return x;
        
        if(y->left)
         Node* z=y->left;
         else
          return x;
          
         Node* temp=y->right;
         y->right=x;
         x->left=temp;
         
         return y;
}

Node* AVL::left_right_rotation(Node)
