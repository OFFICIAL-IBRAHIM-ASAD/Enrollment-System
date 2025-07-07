// StudentDLinkedList.cpp
#include "StudentDLinkedList.h"

StudentDLinkedList::StudentDLinkedList() : head(nullptr), tail(nullptr), currentSize(0) {}

StudentDLinkedList::~StudentDLinkedList() {
    DLNode* current = head;
    while (current != nullptr) {
        DLNode* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    currentSize = 0;
}

DLNode* StudentDLinkedList::findStudent(const std::string& studentId) const { // <<< 'const' MUST be here too
    DLNode* current = head;
    while (current != nullptr) {
        if (current->data.studentId == studentId) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool StudentDLinkedList::addStudent(const Student& student) {
    DLNode* newNode = new DLNode(student);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    currentSize++;
    return true;
}

bool StudentDLinkedList::removeStudent(const std::string& studentId) {
    DLNode* current = head;
    while (current != nullptr) {
        if (current->data.studentId == studentId) {
            if (current == head) {
                head = current->next;
                if (head) head->prev = nullptr;
                else tail = nullptr; // List became empty
            } else if (current == tail) {
                tail = current->prev;
                if (tail) tail->next = nullptr;
                else head = nullptr; // List became empty
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            currentSize--;
            return true;
        }
        current = current->next;
    }
    return false; // Not found
}

void StudentDLinkedList::displayStudents() const {
    if (isEmpty()) {
        std::cout << "    No students enrolled." << std::endl;
        return;
    }
    DLNode* current = head;
    int count = 1;
    while (current != nullptr) {
        std::cout << "    " << count++ << ". " << current->data << std::endl;
        current = current->next;
    }
}

std::vector<Student> StudentDLinkedList::getStudentsAsVector() const {
    std::vector<Student> studentsVec;
    DLNode* current = head;
    while (current != nullptr) {
        studentsVec.push_back(current->data);
        current = current->next;
    }
    return studentsVec;
}

bool StudentDLinkedList::isEmpty() const { return head == nullptr; }
int StudentDLinkedList::getSize() const { return currentSize; }
// ... Implement findStudent similarly ...