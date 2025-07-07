// CourseAVLTree.cpp
#include "CourseAVLTree.h"

CourseAVLTree::CourseAVLTree() : root(nullptr) {}

CourseAVLTree::~CourseAVLTree() {
    _destroyTree(root);
}

void CourseAVLTree::_destroyTree(AVLNode* node) {
    if (node) {
        _destroyTree(node->left);
        _destroyTree(node->right);
        delete node;
    }
}

int CourseAVLTree::getHeight(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int CourseAVLTree::getBalanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* CourseAVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVLNode* CourseAVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

void CourseAVLTree::insert(const Course& course) {
    root = _insert(root, course);
}

AVLNode* CourseAVLTree::_insert(AVLNode* node, const Course& course) {
    if (node == nullptr) return new AVLNode(course);

    if (course.courseCode < node->data.courseCode) {
        node->left = _insert(node->left, course);
    } else if (course.courseCode > node->data.courseCode) {
        node->right = _insert(node->right, course);
    } else {
        // Duplicate course codes not allowed (or update existing - your choice)
        std::cout << "Error: Course with code " << course.courseCode << " already exists." << std::endl;
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Left Left Case
    if (balance > 1 && course.courseCode < node->left->data.courseCode)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && course.courseCode > node->right->data.courseCode)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && course.courseCode > node->left->data.courseCode) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && course.courseCode < node->right->data.courseCode) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

AVLNode* CourseAVLTree::search(const std::string& courseCode) const {
    return _search(root, courseCode);
}

AVLNode* CourseAVLTree::_search(AVLNode* node, const std::string& courseCode) const {
    if (node == nullptr || node->data.courseCode == courseCode) {
        return node;
    }
    if (courseCode < node->data.courseCode) {
        return _search(node->left, courseCode);
    } else {
        return _search(node->right, courseCode);
    }
}

void CourseAVLTree::displayCoursesInOrder() const {
    if (root == nullptr) {
        std::cout << "No courses in the system." << std::endl;
        return;
    }
    _inOrder(root);
}

void CourseAVLTree::_inOrder(AVLNode* node) const {
    if (node != nullptr) {
        _inOrder(node->left);
        std::cout << "---------------------\n";
        node->data.displayCourseInfo(); // Using Course's display method
        std::cout << "---------------------\n";
        _inOrder(node->right);
    }
}
// --- AVL Deletion (findMinNode, _remove) is more involved ---
// For simplicity, you might skip full AVL deletion or implement it carefully
// A basic BST-style deletion could be a fallback if AVL deletion is too time-consuming
// For the project, `remove` might just mean "course is no longer offered" without actually removing from tree,
// or if you implement, remember to rebalance.

AVLNode* CourseAVLTree::findMinNode(AVLNode* node) {
    AVLNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

void CourseAVLTree::remove(const std::string& courseCode) {
    root = _remove(root, courseCode);
}

AVLNode* CourseAVLTree::_remove(AVLNode* node, const std::string& courseCode) {
    if (node == nullptr) return node;

    if (courseCode < node->data.courseCode) {
        node->left = _remove(node->left, courseCode);
    } else if (courseCode > node->data.courseCode) {
        node->right = _remove(node->right, courseCode);
    } else { // Node to be deleted found
        // Node with only one child or no child
        if (node->left == nullptr || node->right == nullptr) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == nullptr) { // No child
                temp = node;
                node = nullptr;
            } else { // One child
                *node = *temp; // Copy contents of the non-empty child
            }
            delete temp;
        } else { // Node with two children
            AVLNode* temp = findMinNode(node->right); // Get in-order successor
            node->data = temp->data; // Copy the in-order successor's data
            node->right = _remove(node->right, temp->data.courseCode); // Delete the in-order successor
        }
    }

    if (node == nullptr) return node; // If tree had only one node

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Rebalancing steps (similar to insert)
    // Left Left Case
    if (balance > 1 && getBalanceFactor(node->left) >= 0)
        return rotateRight(node);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right Case
    if (balance < -1 && getBalanceFactor(node->right) <= 0)
        return rotateLeft(node);

    // Right Left Case
    if (balance < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}