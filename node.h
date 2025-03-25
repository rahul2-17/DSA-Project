#ifndef NODE_H
#define NODE_H

#include "courseinfo.h"
#include <string>

class Node {
public:
    int rollNo;
    std::string name;
    float cgpa;
    int numSubjects;
    CourseInfo* courses;
    Node* left;
    Node* right;
    int height;

    Node(int rollNo, std::string name, float cgpa, int numSubjects, CourseInfo* courses);
    ~Node();
};

#endif
