// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream> // For operator<<

struct Student {
    std::string studentId;
    std::string studentName;

    Student(std::string id = "", std::string name = "") : studentId(std::move(id)), studentName(std::move(name)) {}

    // For searching and comparison, primarily for removing from list or sorting
    bool operator==(const Student& other) const {
        return studentId == other.studentId;
    }

    // For sorting (e.g., by name then ID)
    bool operator<(const Student& other) const {
        if (studentName != other.studentName) {
            return studentName < other.studentName;
        }
        return studentId < other.studentId;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        os << "ID: " << s.studentId << ", Name: " << s.studentName;
        return os;
    }
};

#endif //STUDENT_H