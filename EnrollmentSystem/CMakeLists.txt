cmake_minimum_required(VERSION 3.29)
project(EnrollmentSystem)

set(CMAKE_CXX_STANDARD 20)

add_executable(EnrollmentSystem main.cpp
        CourseAVLTree.cpp
        CourseAVLTree.h
        Course.h
        StudentDLinkedList.cpp
        StudentDLinkedList.h
        Student.h
        Sorting.h)
