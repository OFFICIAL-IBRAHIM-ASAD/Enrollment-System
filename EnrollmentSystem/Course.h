// Course.h
#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include "StudentDLinkedList.h" // Include the list of students

struct Course {
    std::string courseCode;
    std::string courseName;
    int capacity;
    StudentDLinkedList enrolledStudentsList; // Each course has its own list of students

    Course(std::string code = "", std::string name = "", int cap = 0)
        : courseCode(std::move(code)), courseName(std::move(name)), capacity(cap) {}

    bool enrollStudent(const Student& student) {
        if (enrolledStudentsList.getSize() < capacity) {
            // Optional: Check if student already enrolled
            if (enrolledStudentsList.findStudent(student.studentId)) {
                 std::cout << "Error: Student " << student.studentId << " already enrolled in " << courseCode << std::endl;
                 return false;
            }
            enrolledStudentsList.addStudent(student);
            return true;
        }
        return false; // Course is full
    }

    bool dropStudent(const std::string& studentId) {
        return enrolledStudentsList.removeStudent(studentId);
    }

    void displayCourseInfo(bool showEnrolledCount = true) const {
        std::cout << "Course Code: " << courseCode << "\n"
                  << "Course Name: " << courseName << "\n"
                  << "Capacity: " << capacity << "\n";
        if (showEnrolledCount) {
             std::cout << "Enrolled: " << enrolledStudentsList.getSize() << std::endl;
        }
    }

    void displayEnrolledStudentsList() const {
        std::cout << "Students enrolled in " << courseCode << " - " << courseName << ":" << std::endl;
        enrolledStudentsList.displayStudents();
    }

    std::vector<Student> getEnrolledStudentsVector() const {
        return enrolledStudentsList.getStudentsAsVector();
    }

    bool isFull() const {
        return enrolledStudentsList.getSize() >= capacity;
    }

    // For AVL Tree comparisons (based on courseCode)
    bool operator<(const Course& other) const { return courseCode < other.courseCode; }
    bool operator>(const Course& other) const { return courseCode > other.courseCode; }
    bool operator==(const Course& other) const { return courseCode == other.courseCode; }

    friend std::ostream& operator<<(std::ostream& os, const Course& c) {
        os << "Code: " << c.courseCode << ", Name: " << c.courseName << ", Capacity: " << c.capacity << ", Enrolled: " << c.enrolledStudentsList.getSize();
        return os;
    }
};

#endif //COURSE_H