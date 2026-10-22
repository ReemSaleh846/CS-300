// Reem Lewis
// CS-300
// Southern New Hampshire University
//
// Excerpt from ProjectTwo.cpp: the binary search tree that stores the
// Computer Science course list and prints it in alphanumeric order.
// Courses are kept sorted by course number as they are inserted, so
// printing the list is a plain in-order traversal with no extra sort step.

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// One Course object holds the data from exactly one line of the input file.
struct Course {
    string courseNumber;             // e.g. "CSCI200"
    string courseName;               // e.g. "Data Structures"
    vector<string> prerequisites;    // course numbers only; empty if none
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    explicit Node(const Course& aCourse) :
            course(aCourse), left(nullptr), right(nullptr) {
    }
};

class CourseTree {
public:
    CourseTree() : root(nullptr), count(0) {}
    ~CourseTree() { clear(); }

    void insert(const Course& course);
    void printInOrder() const;
    void clear();

private:
    Node* root;
    int count;

    static void printInOrder(const Node* node);
    static void deleteNodes(Node* node);
};

/**
 * Insert a course. Smaller course numbers go left, larger ones go right,
 * which keeps every course in sorted order as soon as it is inserted.
 */
void CourseTree::insert(const Course& course) {
    Node* newNode = new Node(course);
    ++count;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    while (true) {
        if (course.courseNumber < current->course.courseNumber) {
            if (current->left == nullptr) {
                current->left = newNode;
                return;
            }
            current = current->left;
        } else {
            if (current->right == nullptr) {
                current->right = newNode;
                return;
            }
            current = current->right;
        }
    }
}

/**
 * Print every course, sorted by course number from lowest to highest.
 */
void CourseTree::printInOrder() const {
    printInOrder(root);
}

/**
 * In-order traversal: left subtree, this node, right subtree. Because
 * smaller course numbers always live in the left subtree, this visits
 * every course in ascending order.
 */
void CourseTree::printInOrder(const Node* node) {
    if (node != nullptr) {
        printInOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseName << endl;
        printInOrder(node->right);
    }
}

/**
 * Remove every course from the tree.
 */
void CourseTree::clear() {
    deleteNodes(root);
    root = nullptr;
    count = 0;
}

void CourseTree::deleteNodes(Node* node) {
    if (node != nullptr) {
        deleteNodes(node->left);
        deleteNodes(node->right);
        delete node;
    }
}

// Called from the menu's "Print Course List" option in ProjectTwo.cpp:
//
//   cout << "Here is a sample schedule:" << endl << endl;
//   courses.printInOrder();
