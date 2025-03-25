#include "courseinfo.h"

CourseInfo::CourseInfo(int courseId, int marks) {
    this->courseId = courseId;
    this->marks = marks;
}

int CourseInfo::getCourseId() {
    return courseId;
}

int CourseInfo::getMarks() {
    return marks;
}

void CourseInfo::setCourseId(int newCourseId) {
    courseId = newCourseId;
}

void CourseInfo::setMarks(int newMarks) {
    marks = newMarks;
}
