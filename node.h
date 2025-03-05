#include <string>
#include "courseInfo.h"

using namespace std;

class Node{
    int RollNo;
    string name;
    float CGPA;
    int noOfSubs;
    courseInfo* courses=new courseInfo[noOfSubs];
    Node* left;
    Node* right;
    int height();
    int balancing_factor();
};
