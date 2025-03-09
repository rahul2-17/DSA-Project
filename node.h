#include <string>
#include "courseInfo.h"

using namespace std;

class Node
{
public:
    int RollNo;
    string name;
    float CGPA;
    int noOfSubs;
    courseInfo *courses;
    Node *left;
    Node *right;

    Node()
    {
        RollNo = 0,
        name = "",
        CGPA = 0,
        noOfSubs = 0,
        courses = new courseInfo[noOfSubs],
        left = NULL;
        right = NULL;
    }

    ~Node()
    {
        delete[] courses;
    }

    int height();
    int balancing_factor();
};
