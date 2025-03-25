#include "filehandler.h"
#include "courseinfo.h"
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

// Utility: trim leading and trailing whitespace
static string trim(const string &s) {
    string result = s;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](int ch) {
        return !isspace(ch);
    }));
    result.erase(find_if(result.rbegin(), result.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), result.end());
    return result;
}

void FileHandler::processFile(const string& filename, AVL& tree) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    cout << "Opened file: " << filename << endl;
    string line;
    // Process each operation from the file
    while(getline(inputFile, line)) {
        if(line.empty())
            continue;
        if(line[0] == '#') {
            int op;
            istringstream iss(line.substr(1));
            iss >> op;
            // Process each operation and then display the current tree state
            if(op == 1) {  // Insert student
                if(getline(inputFile, line)) {
                    istringstream details(line);
                    int rollNo, numSubjects;
                    float cgpa;
                    char comma;
                    details >> rollNo;
                    details.ignore(); // ignore comma
                    string name;
                    getline(details, name, ',');
                    name = trim(name);
                    details >> cgpa >> comma >> numSubjects;
                    CourseInfo* courses = new CourseInfo[numSubjects];
                    for (int i = 0; i < numSubjects; i++) {
                        if(getline(inputFile, line)) {
                            istringstream courseStream(line);
                            int courseId, marks;
                            courseStream >> courseId;
                            courseStream.ignore();
                            courseStream >> marks;
                            courses[i] = CourseInfo(courseId, marks);
                        }
                    }
                    tree.insertStudent(rollNo, name, cgpa, numSubjects, courses);
                    delete [] courses;
                }
            }
            else if(op == 2) {  // Modify student CGPA: "RollNo, new_CGPA"
                if(getline(inputFile, line)) {
                    istringstream iss2(line);
                    int rollNo;
                    float newCgpa;
                    char comma;
                    iss2 >> rollNo >> comma >> newCgpa;
                    tree.modifyCGPA(rollNo, newCgpa);
                }
            }
            else if(op == 3) {  // Add new course: "RollNo, CourseCode, Marks"
                if(getline(inputFile, line)) {
                    istringstream iss2(line);
                    int rollNo, courseCode, marks;
                    char comma;
                    iss2 >> rollNo >> comma >> courseCode >> comma >> marks;
                    tree.addCourse(rollNo, courseCode, marks);
                }
            }
            else if(op == 4) {  // Modify course marks: "RollNo, CourseCode, new_Marks"
                if(getline(inputFile, line)) {
                    istringstream iss2(line);
                    int rollNo, courseCode, newMarks;
                    char comma;
                    iss2 >> rollNo >> comma >> courseCode >> comma >> newMarks;
                    tree.modifyCourseMarks(rollNo, courseCode, newMarks);
                }
            }
            else if(op == 5) {  // Delete course: "RollNo, CourseCode"
                if(getline(inputFile, line)) {
                    istringstream iss2(line);
                    int rollNo, courseCode;
                    char comma;
                    iss2 >> rollNo >> comma >> courseCode;
                    tree.deleteCourse(rollNo, courseCode);
                }
            }
            else if(op == 6) {  // Delete student: "RollNo"
                if(getline(inputFile, line)) {
                    istringstream iss2(line);
                    int rollNo;
                    iss2 >> rollNo;
                    tree.deleteStudent(rollNo);
                }
            }
            else if(op == 7) {  // Query: Print students with roll no greater than given value
                if(tree.getKeyType() == ROLL_NO && getline(inputFile, line)) {
                    int val;
                    istringstream iss2(line);
                    iss2 >> val;
                    cout << "\nStudents with roll number greater than " << val << ":\n";
                    tree.printGreaterRoll(val);
                    cout << "\n";
                }
            }
            else if(op == 8) {  // Query: Print students with roll no less than given value
                if(tree.getKeyType() == ROLL_NO && getline(inputFile, line)) {
                    int val;
                    istringstream iss2(line);
                    iss2 >> val;
                    cout << "\nStudents with roll number less than " << val << ":\n";
                    tree.printLessRoll(val);
                    cout << "\n";
                }
            }
            else if(op == 9) {  // Query: Print students with roll no between two values
                if(tree.getKeyType() == ROLL_NO && getline(inputFile, line)) {
                    int low, high;
                    char comma;
                    istringstream iss2(line);
                    iss2 >> low >> comma >> high;
                    cout << "\nStudents with roll number between " << low << " and " << high << ":\n";
                    tree.printBetweenRoll(low, high);
                    cout << "\n";
                }
            }
            else if(op == 10) {  // Query: Print students with CGPA greater than given value
                if(tree.getKeyType() == CGPA && getline(inputFile, line)) {
                    float val;
                    istringstream iss2(line);
                    iss2 >> val;
                    cout << "\nStudents with CGPA greater than " << val << ":\n";
                    tree.printGreaterCGPA(val);
                    cout << "\n";
                }
            }
            else if(op == 11) {  // Query: Print students with CGPA less than given value
                if(tree.getKeyType() == CGPA && getline(inputFile, line)) {
                    float val;
                    istringstream iss2(line);
                    iss2 >> val;
                    cout << "\nStudents with CGPA less than " << val << ":\n";
                    tree.printLessCGPA(val);
                    cout << "\n";
                }
            }
            else if(op == 12) {  // Query: Print students with CGPA between two values
                if(tree.getKeyType() == CGPA && getline(inputFile, line)) {
                    float low, high;
                    char comma;
                    istringstream iss2(line);
                    iss2 >> low >> comma >> high;
                    cout << "\nStudents with CGPA between " << low << " and " << high << ":\n";
                    tree.printBetweenCGPA(low, high);
                    cout << "\n";
                }
            }
            // After processing each operation, display the current state of the tree.
            cout << "\nCurrent AVL Tree State:\n";
            tree.printInOrder();
            cout << "----------------------------------------\n";
        }
    }
    inputFile.close();
}
