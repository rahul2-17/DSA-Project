#include "avl.h"
#include <algorithm>
#include <functional>
using namespace std;

AVL::AVL(KeyType key) {
    root = nullptr;
    keyType = key;
}

AVL::~AVL() {
    destroy(root);
}

void AVL::destroy(Node* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

int AVL::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVL::getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* AVL::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* AVL::insert(Node* node, int rollNo, string name, float cgpa, int numSubjects, CourseInfo* courses) {
    if (!node)
        return new Node(rollNo, name, cgpa, numSubjects, courses);
    if ((keyType == ROLL_NO && rollNo < node->rollNo) || (keyType == CGPA && cgpa < node->cgpa))
        node->left = insert(node->left, rollNo, name, cgpa, numSubjects, courses);
    else if ((keyType == ROLL_NO && rollNo > node->rollNo) || (keyType == CGPA && cgpa > node->cgpa))
        node->right = insert(node->right, rollNo, name, cgpa, numSubjects, courses);
    else
        return node;  // Duplicate key not inserted

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return balance(node);
}

void AVL::insertStudent(int rollNo, string name, float cgpa, int numSubjects, CourseInfo* courses) {
    root = insert(root, rollNo, name, cgpa, numSubjects, courses);
}

// Print each student record in the required format
void AVL::inorderTraversal(Node* node) {
    if (!node) return;
    inorderTraversal(node->left);
    cout << "Roll No: " << node->rollNo << "\n";
    cout << "Name: " << node->name << "\n";
    cout << "CGPA: " << node->cgpa << "\n";
    cout << "BF: " << getBalanceFactor(node) << "\n";
    if (node->numSubjects > 0) {
        cout << "\nCourses:\n";
        for (int i = 0; i < node->numSubjects; i++) {
            cout << node->courses[i].getCourseId() << ": " << node->courses[i].getMarks() << "\n";
        }
    }
    cout << "\n";
    inorderTraversal(node->right);
}

void AVL::printInOrder() {
    cout << "Final Student Records (Sorted by " << (keyType == ROLL_NO ? "Roll Number" : "CGPA") << "):\n\n";
    if (!root) {
        cout << "No student records found!\n";
    } else {
        inorderTraversal(root);
    }
}

KeyType AVL::getKeyType() {
    return keyType;
}

// Helper: full tree search for a student by roll number
Node* AVL::searchByRollNo(Node* node, int rollNo) {
    if (!node) return nullptr;
    if (node->rollNo == rollNo)
        return node;
    Node* found = searchByRollNo(node->left, rollNo);
    if (found) return found;
    return searchByRollNo(node->right, rollNo);
}

// Operation 2: Modify student CGPA
bool AVL::modifyCGPA(int rollNo, float newCgpa) {
    Node* student = searchByRollNo(root, rollNo);
    if (!student) return false;
    if (keyType == CGPA) {
        int r = student->rollNo;
        string n = student->name;
        int numSub = student->numSubjects;
        CourseInfo* courses = new CourseInfo[numSub];
        for (int i = 0; i < numSub; i++)
            courses[i] = student->courses[i];
        root = deleteByRollNo(root, rollNo);
        insertStudent(r, n, newCgpa, numSub, courses);
        delete [] courses;
    } else {
        student->cgpa = newCgpa;
    }
    return true;
}

// Operation 3: Add a new course to a student record
bool AVL::addCourse(int rollNo, int courseCode, int marks) {
    Node* student = searchByRollNo(root, rollNo);
    if (!student) return false;
    int newCount = student->numSubjects + 1;
    CourseInfo* newCourses = new CourseInfo[newCount];
    for (int i = 0; i < student->numSubjects; i++)
        newCourses[i] = student->courses[i];
    newCourses[newCount - 1] = CourseInfo(courseCode, marks);
    delete[] student->courses;
    student->courses = newCourses;
    student->numSubjects = newCount;
    return true;
}

// Operation 4: Modify course marks for a given course code
bool AVL::modifyCourseMarks(int rollNo, int courseCode, int newMarks) {
    Node* student = searchByRollNo(root, rollNo);
    if (!student) return false;
    for (int i = 0; i < student->numSubjects; i++) {
        if (student->courses[i].getCourseId() == courseCode) {
            student->courses[i].setMarks(newMarks);
            return true;
        }
    }
    return false;
}

// Operation 5: Delete a course from a student record
bool AVL::deleteCourse(int rollNo, int courseCode) {
    Node* student = searchByRollNo(root, rollNo);
    if (!student) return false;
    int index = -1;
    for (int i = 0; i < student->numSubjects; i++) {
        if (student->courses[i].getCourseId() == courseCode) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;
    int newCount = student->numSubjects - 1;
    CourseInfo* newCourses = (newCount > 0) ? new CourseInfo[newCount] : nullptr;
    int j = 0;
    for (int i = 0; i < student->numSubjects; i++) {
        if (i == index) continue;
        newCourses[j++] = student->courses[i];
    }
    delete[] student->courses;
    student->courses = newCourses;
    student->numSubjects = newCount;
    return true;
}

// Helper: find the node with minimum key (used in deletion)
Node* AVL::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Operation 6: Delete a student record by roll number
Node* AVL::deleteByRollNo(Node* node, int rollNo) {
    if (!node) return nullptr;
    if (keyType == ROLL_NO) {
        if (rollNo < node->rollNo)
            node->left = deleteByRollNo(node->left, rollNo);
        else if (rollNo > node->rollNo)
            node->right = deleteByRollNo(node->right, rollNo);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->rollNo = temp->rollNo;
                node->name = temp->name;
                node->cgpa = temp->cgpa;
                node->numSubjects = temp->numSubjects;
                delete[] node->courses;
                int count = temp->numSubjects;
                node->courses = new CourseInfo[count];
                for (int i = 0; i < count; i++)
                    node->courses[i] = temp->courses[i];
                node->right = deleteByRollNo(node->right, temp->rollNo);
            }
        }
    } else { // For CGPA-keyed tree, traverse entire tree
        if (node->rollNo == rollNo) {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = minValueNode(node->right);
                node->rollNo = temp->rollNo;
                node->name = temp->name;
                node->cgpa = temp->cgpa;
                node->numSubjects = temp->numSubjects;
                delete[] node->courses;
                int count = temp->numSubjects;
                node->courses = new CourseInfo[count];
                for (int i = 0; i < count; i++)
                    node->courses[i] = temp->courses[i];
                node->right = deleteByRollNo(node->right, temp->rollNo);
            }
        } else {
            node->left = deleteByRollNo(node->left, rollNo);
            node->right = deleteByRollNo(node->right, rollNo);
        }
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return balance(node);
}

bool AVL::deleteStudent(int rollNo) {
    if (searchByRollNo(root, rollNo) == nullptr)
        return false;
    root = deleteByRollNo(root, rollNo);
    return true;
}

// Query functions for roll number keyed tree
void AVL::printGreaterRoll(int rollNo) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->rollNo > rollNo)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}

void AVL::printLessRoll(int rollNo) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->rollNo < rollNo)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}

void AVL::printBetweenRoll(int low, int high) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->rollNo >= low && node->rollNo <= high)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}

// Query functions for CGPA keyed tree
void AVL::printGreaterCGPA(float cgpa) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->cgpa > cgpa)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}

void AVL::printLessCGPA(float cgpa) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->cgpa < cgpa)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}

void AVL::printBetweenCGPA(float low, float high) {
    function<void(Node*)> traverse = [&](Node* node) {
        if (!node) return;
        traverse(node->left);
        if (node->cgpa >= low && node->cgpa <= high)
            cout << "Roll No: " << node->rollNo << ", Name: " << node->name << ", CGPA: " << node->cgpa << "\n";
        traverse(node->right);
    };
    traverse(root);
}
