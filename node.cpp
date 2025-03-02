#include "node.h"

int Node::height(){
    if(this==NULL)
     return -1;

    return max(left->height() ,right->height()) + 1;
}