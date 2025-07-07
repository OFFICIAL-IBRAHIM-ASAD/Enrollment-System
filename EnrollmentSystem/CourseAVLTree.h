// CourseAVLTree.h
#ifndef COURSEAVLTREE_H
#define COURSEAVLTREE_H

#include "Course.h"
#include <algorithm> // For std::max
#include <iostream>

struct AVLNode {
    Course data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Course val) : data(std::move(val)), left(nullptr), right(nullptr), height(1) {}
};

class CourseAVLTree {
public:
    AVLNode* root;

    CourseAVLTree();
    ~CourseAVLTree(); // Important: to delete all nodes

    void insert(const Course& course);
    AVLNode* search(const std::string& courseCode) const; // Returns AVLNode to allow modification of course
    void remove(const std::string& courseCode); // More complex to implement fully
    void displayCoursesInOrder() const;


private:
    AVLNode* _insert(AVLNode* node, const Course& course);
    AVLNode* _search(AVLNode* node, const std::string& courseCode) const;
    AVLNode* _remove(AVLNode* node, const std::string& courseCode);
    void _inOrder(AVLNode* node) const;
    void _destroyTree(AVLNode* node);

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* findMinNode(AVLNode* node); // Helper for deletion
};

#endif //COURSEAVLTREE_H