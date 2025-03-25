#include "node.h"

Node::Node(int rollNo, std::string name, float cgpa, int numSubjects, CourseInfo* courses) {
    this->rollNo = rollNo;
    this->name = name;
    this->cgpa = cgpa;
    this->numSubjects = numSubjects;
    left = nullptr;
    right = nullptr;
    height = 1;
    this->courses = new CourseInfo[numSubjects];
    for (int i = 0; i < numSubjects; i++) {
        this->courses[i] = courses[i];
    }
}

Node::~Node() {
    delete[] courses;
    // Do not delete left/right here as AVL::destroy() handles that.
}
