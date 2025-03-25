#ifndef COURSEINFO_H
#define COURSEINFO_H

class CourseInfo {
private:
    int courseId;
    int marks;

public:
    CourseInfo(int courseId = 0, int marks = 0);
    int getCourseId();
    int getMarks();
    void setCourseId(int newCourseId);
    void setMarks(int newMarks);
};

#endif
