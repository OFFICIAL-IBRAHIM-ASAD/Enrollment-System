// StudentDLinkedList.h
#pragma once
#ifndef STUDENTDLINKEDLIST_H
#define STUDENTDLINKEDLIST_H

#include "Student.h"
#include <vector> // For getStudentsAsVector
#include <iostream>

struct DLNode {
    Student data;
    DLNode* next;
    DLNode* prev;

    DLNode(Student val) : data(std::move(val)), next(nullptr), prev(nullptr) {}
};

class StudentDLinkedList {
public: // Public interface
    StudentDLinkedList();
    ~StudentDLinkedList();

    bool addStudent(const Student& student);
    bool removeStudent(const std::string& studentId);
    DLNode* findStudent(const std::string& studentId) const; // Returns a raw pointer,
    void displayStudents() const;
    bool isEmpty() const;
    int getSize() const;
    std::vector<Student> getStudentsAsVector() const;

private: // Internal implementation details
    DLNode* head;
    DLNode* tail;
    int currentSize;
};

#endif //STUDENTDLINKEDLIST_H