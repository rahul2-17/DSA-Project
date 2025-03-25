#ifndef AVL_H
#define AVL_H

#include "node.h"
#include <iostream>
#include <functional>

enum KeyType { ROLL_NO, CGPA };

class AVL {
private:
    Node* root;
    KeyType keyType;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);
    Node* insert(Node* node, int rollNo, std::string name, float cgpa, int numSubjects, CourseInfo* courses);
    Node* searchByRollNo(Node* node, int rollNo);
    Node* minValueNode(Node* node);
    Node* deleteByRollNo(Node* node, int rollNo);
    void inorderTraversal(Node* node);
    void destroy(Node* node); // recursive deletion

public:
    AVL(KeyType key);
    ~AVL();
    void insertStudent(int rollNo, std::string name, float cgpa, int numSubjects, CourseInfo* courses);
    void printInOrder();
    KeyType getKeyType();

    // Operation 2: Modify student CGPA
    bool modifyCGPA(int rollNo, float newCgpa);
    // Operation 3: Add new course to a student
    bool addCourse(int rollNo, int courseCode, int marks);
    // Operation 4: Modify course marks for a given course code
    bool modifyCourseMarks(int rollNo, int courseCode, int newMarks);
    // Operation 5: Delete a course from a student record
    bool deleteCourse(int rollNo, int courseCode);
    // Operation 6: Delete a student
    bool deleteStudent(int rollNo);

    // Query functions for roll number keyed tree
    void printGreaterRoll(int rollNo);
    void printLessRoll(int rollNo);
    void printBetweenRoll(int low, int high);

    // Query functions for CGPA keyed tree
    void printGreaterCGPA(float cgpa);
    void printLessCGPA(float cgpa);
    void printBetweenCGPA(float low, float high);
};

#endif
