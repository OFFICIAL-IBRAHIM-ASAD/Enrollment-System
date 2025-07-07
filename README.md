# Enrollment-System
An efficient command-line system for managing student enrollments in academic courses. The system facilitates adding courses, enrolling and dropping students, tracking course capacities, and displaying relevant information, thereby streamlining administrative tasks.


**Project Report: Student Enrollment Management System**
1. Introduction
1.1 Project Purpose:
To develop an efficient command-line system for managing student enrollments in academic courses. The system facilitates adding courses, enrolling and dropping students, tracking course capacities, and displaying relevant information, thereby streamlining administrative tasks.
1.2 Scope:
The system allows administrators or users to:
oAdd new courses with unique codes, names, and capacities.
oEnroll students (identified by ID and name) into available courses, respecting capacity limits.
oDrop students from courses.
oView a list of all available courses and their current enrollment status.
oView a detailed list of students enrolled in a specific course, with an option to sort this list.
oSearch for specific courses.
oDelete courses from the system.
1.3 Technologies Used:
oProgramming Language: C++
oCore Data Structures: AVL Tree, Doubly Linked List
oSorting Algorithm: Selection Sort
oDevelopment Environment: CLion IDE 

2. System Design and Implementation
2.1 Core Components:
oStudent Structure: Represents a student with attributes like studentId and studentName.
oCourse Structure: Represents a course with courseCode, courseName, capacity, and an embedded list of enrolled students.
oStudentDLinkedList Class: A Doubly Linked List implementation to manage the list of students enrolled within each Course object. Chosen for its efficient addition and removal of students, especially at the ends of the list. Removing a student by searching for their ID can take more time if the list is long.
oCourseAVLTree Class: An AVL Tree implementation to store and manage Course objects, using courseCode as the key. Chosen for its self-balancing property, ensuring quick search, insertion, and deletion of courses, even as the number of courses increases.
oSorting Module: Contains the selectionSortStudents function used to sort student lists by name or ID upon request. The time taken to sort increases with the number of students.
2.2 Key Functionalities & Data Flow:
oAdding a Course: A new Course object is created and inserted into the CourseAVLTree. This process is designed to be efficient.
oEnrolling a Student: The target course is quickly located in the CourseAVLTree. If found and not at capacity, the Student is added to the course's internal StudentDLinkedList. Duplicate enrollment checks are performed. The overall process is efficient, though checking for duplicates in a specific course can take longer if many students are already enrolled in that course.
oDropping a Student: The student is removed from the specific course's StudentDLinkedList. Finding the course is quick, but finding and removing the student from the course's list can take longer if the course has many students.
oDisplaying Courses: An in-order traversal of the CourseAVLTree is performed, efficiently listing all courses.
oDisplaying Enrolled Students: Students are retrieved from the course's StudentDLinkedList. Finding the course is quick, and listing students is also straightforward. If sorting is requested, data is copied to a temporary list and sorted using Selection Sort; this sorting step can take longer for courses with many students.

3. Challenges and Solutions
Challenge: Ensuring efficient management and retrieval of courses as the number grows.
oSolution: Implemented an AVL Tree, guaranteeing good performance for core course operations. This structure prevents performance degradation that can occur with simpler methods as more courses are added.
Challenge: Managing dynamic lists of students for each course with efficient enrollment/dropping.
oSolution: Utilized a Doubly Linked List for each course's student roster, allowing for generally quick additions and removals of students.
Challenge: Implementing balanced tree rotations (AVL) correctly.
oSolution: Careful implementation and testing of the logic for LL, RR, LR, and RL rotations during insertion and deletion were performed to maintain tree balance and efficiency.
Challenge: Providing sorted views of enrolled students without impacting the primary student list structure.
oSolution: Students are temporarily copied to a separate list and sorted using Selection Sort. This approach preserves the integrity and typical performance of the main student list.

4. Conclusion and Future Work
4.1 Conclusion:
The Student Enrollment System successfully meets its objectives, providing a robust and efficient command-line tool for managing course enrollments. The choice of AVL trees and Doubly Linked Lists ensures good performance for key operations.
