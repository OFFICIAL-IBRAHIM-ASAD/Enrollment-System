// main.cpp
#include <iostream>
#include <string>
#include <limits> // Required for std::numeric_limits
#include <vector> // For sorting

#include "CourseAVLTree.h"
#include "Sorting.h" // For selectionSortStudents

CourseAVLTree courseDatabase; // Global database for courses

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handleAddNewCourse() {
    std::string code, name;
    int capacity;
    std::cout << "Enter Course Code (e.g., CS101): ";
    std::cin >> code;
    clearInputBuffer(); 
    std::cout << "Enter Course Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Course Capacity: ";
    while (!(std::cin >> capacity) || capacity <= 0) {
        std::cout << "Invalid capacity. Please enter a positive number: ";
        std::cin.clear();
        clearInputBuffer();
    }
    clearInputBuffer();

    if (courseDatabase.search(code)) {
        std::cout << "Error: Course with code " << code << " already exists." << std::endl;
    } else {
        courseDatabase.insert(Course(code, name, capacity));
        std::cout << "Course " << code << " added successfully." << std::endl;
    }
}

void handleEnrollStudent() {
    std::string courseCode, studentId, studentName;
    std::cout << "Enter Course Code to enroll student in: ";
    std::cin >> courseCode;
    clearInputBuffer();

    AVLNode* courseNode = courseDatabase.search(courseCode);
    if (!courseNode) {
        std::cout << "Error: Course " << courseCode << " not found." << std::endl;
        return;
    }

    if (courseNode->data.isFull()) {
        std::cout << "Error: Course " << courseCode << " is already full." << std::endl;
        return;
    }

    std::cout << "Enter Student ID: ";
    std::cin >> studentId;
    clearInputBuffer();
    std::cout << "Enter Student Name: ";
    std::getline(std::cin, studentName);

    if (courseNode->data.enrolledStudentsList.findStudent(studentId)) {
         std::cout << "Error: Student " << studentId << " is already enrolled in this course." << std::endl;
         return;
    }

    if (courseNode->data.enrollStudent(Student(studentId, studentName))) {
        std::cout << "Student " << studentName << " enrolled successfully in " << courseCode << "." << std::endl;
    } else {
        // This case should ideally be caught by isFull() or duplicate check above
        std::cout << "Failed to enroll student (course might be full or student already exists)." << std::endl;
    }
}

void handleDropStudent() {
    std::string courseCode, studentId;
    std::cout << "Enter Course Code to drop student from: ";
    std::cin >> courseCode;
    clearInputBuffer();

    AVLNode* courseNode = courseDatabase.search(courseCode);
    if (!courseNode) {
        std::cout << "Error: Course " << courseCode << " not found." << std::endl;
        return;
    }

    std::cout << "Enter Student ID to drop: ";
    std::cin >> studentId;
    clearInputBuffer();

    if (courseNode->data.dropStudent(studentId)) {
        std::cout << "Student " << studentId << " dropped successfully from " << courseCode << "." << std::endl;
    } else {
        std::cout << "Error: Student " << studentId << " not found in course " << courseCode << "." << std::endl;
    }
}

void handleDisplayAllCourses() {
    std::cout << "\n--- All Courses ---" << std::endl;
    courseDatabase.displayCoursesInOrder();
    std::cout << "-------------------\n" << std::endl;
}

void handleDisplayEnrolledStudents() {
    std::string courseCode;
    std::cout << "Enter Course Code to display enrolled students: ";
    std::cin >> courseCode;
    clearInputBuffer();

    AVLNode* courseNode = courseDatabase.search(courseCode);
    if (!courseNode) {
        std::cout << "Error: Course " << courseCode << " not found." << std::endl;
        return;
    }

    courseNode->data.displayCourseInfo(false); // Display course info without enrolled count here
    
    if (courseNode->data.enrolledStudentsList.isEmpty()) {
        std::cout << "No students enrolled in this course." << std::endl;
        return;
    }

    char sortChoice;
    std::cout << "Sort students? (y/n): ";
    std::cin >> sortChoice;
    clearInputBuffer();

    if (sortChoice == 'y' || sortChoice == 'Y') {
        std::vector<Student> studentsVec = courseNode->data.getEnrolledStudentsVector();
        char sortCriteria;
        std::cout << "Sort by (N)ame or (I)D? ";
        std::cin >> sortCriteria;
        clearInputBuffer();
        bool sortByName = (sortCriteria == 'N' || sortCriteria == 'n');
        
        selectionSortStudents(studentsVec, sortByName); // Use the sorting function
        
        std::cout << "Enrolled Students (Sorted):" << std::endl;
        int count = 1;
        for (const auto& s : studentsVec) {
            std::cout << "    " << count++ << ". " << s << std::endl;
        }
    } else {
        courseNode->data.displayEnrolledStudentsList();
    }
}

void handleSearchCourse() {
    std::string courseCode;
    std::cout << "Enter Course Code to search: ";
    std::cin >> courseCode;
    clearInputBuffer();

    AVLNode* courseNode = courseDatabase.search(courseCode);
    if (courseNode) {
        std::cout << "--- Course Found ---" << std::endl;
        courseNode->data.displayCourseInfo();
        courseNode->data.displayEnrolledStudentsList();
        std::cout << "--------------------" << std::endl;
    } else {
        std::cout << "Course " << courseCode << " not found." << std::endl;
    }
}


int main() {
    int choice;
    do {
        std::cout << "\n--- Student Enrollment System ---" << std::endl;
        std::cout << "1. Add New Course" << std::endl;
        std::cout << "2. Enroll Student in Course" << std::endl;
        std::cout << "3. Drop Student from Course" << std::endl;
        std::cout << "4. Display All Courses" << std::endl;
        std::cout << "5. Display Enrolled Students for a Course" << std::endl;
        std::cout << "6. Search for a Course" << std::endl;
        std::cout << "7. Delete Course (Full AVL Remove)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer(); // Consume the newline after reading the integer

        switch (choice) {
            case 1: handleAddNewCourse(); break;
            case 2: handleEnrollStudent(); break;
            case 3: handleDropStudent(); break;
            case 4: handleDisplayAllCourses(); break;
            case 5: handleDisplayEnrolledStudents(); break;
            case 6: handleSearchCourse(); break;
            case 7: {
                std::string courseCodeDel;
                std::cout << "Enter Course Code to delete: ";
                std::cin >> courseCodeDel;
                clearInputBuffer();
                courseDatabase.remove(courseCodeDel); // Call AVL remove
                std::cout << "Attempted to delete course " << courseCodeDel << ". (If it existed and deletion is fully implemented)" << std::endl;
                break;
            }
            case 0: std::cout << "Exiting system." << std::endl; break;
            default: std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}