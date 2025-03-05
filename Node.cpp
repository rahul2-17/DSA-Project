#include "node.h"

int Node::height(Node* root){
		if(this.left==NULL && this.right==NULL){
		return 0;
		
		return max(height(root->left), height(root->right)) +1;
		
int Node::balancing_factor(){
		return abs(height(left->height()-height(right->height());
	}
}

