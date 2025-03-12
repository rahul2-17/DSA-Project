#include "node.h"
using namespace std;

class AVL{
        public:
        Node* root;
        
        Node* left_rotation(Node* x);
        Node* right_rotation(Node* x);
        Node* left_right_rotation(Node* x);
        Node* right_left_rotation(Node* x);
        
        void balance_tree(Node* &root);
        
        Node* search(Node* root, int rollNo);
        Node* deleteNode(Node* root, int rollNo);
};
