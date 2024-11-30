#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// BST Node Structure Definition
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// BST Class
class BinarySearchTree {
private:
    Node* root;

    // Method to insert a new node
    Node* add(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = add(node->left, value);
        }
        else if (value > node->data) {
            node->right = add(node->right, value);
        }
        return node;
    }

    // Method to remove a node
    Node* remove(Node* node, int value) {
        if (node == nullptr) return node;

        // Recursively search and removal for the node
        if (value < node->data) {
            node->left = remove(node->left, value);
        }
        else if (value > node->data) {
            node->right = remove(node->right, value);
        }
        else {  // Found node for deletion
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node has two children: Get the inorder successor
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    // Method to find the minimum value node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Method for inorder traversal
    void inorderTraverse(Node* node) {
        if (node != nullptr) {
            inorderTraverse(node->left);
            cout << node->data << " ";
            inorderTraverse(node->right);
        }
    }

    // Method to find a value in the tree
    Node* find(Node* node, int value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return find(node->left, value);
        }
        return find(node->right, value);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void add(int value) {
        root = add(root, value);
    }

    void remove(int value) {
        root = remove(root, value);
    }

    void inorderTraverse() {
        inorderTraverse(root);
        cout << endl;
    }

    Node* find(int value) {
        return find(root, value);
    }

    int maximum() {
        Node* current = root;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return current ? current->data : -1;
    }
};

int main() {
    BinarySearchTree bst;

    // TC: Add random values and perform inorder traversal
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100;
        cout << "Inserting: " << value << endl;
        bst.add(value);
    }

    // TC: Inorder traversal
    cout << "Inorder traversal: ";
    bst.inorderTraverse();

    // TC: Find a value
    int value = 50;
    Node* foundNode = bst.find(value);
    if (foundNode) {
        cout << "Node " << value << " found." << endl;
    }
    else {
        cout << "Node " << value << " not found." << endl;
    }

    // TC: Remove a node (with no children)
    value = 50;  // Choose a value to remove
    cout << "Removing node " << value << endl;
    bst.remove(value);
    bst.inorderTraverse();

    // TC: Remove a node (with one child or two children)
    value = 30;  // Choose a value to remove
    cout << "Removing node " << value << endl;
    bst.remove(value);
    bst.inorderTraverse();

    // TC: Maximum value
    cout << "Maximum value: " << bst.maximum() << endl;

    // Measure the time taken to insert nodes for different counts
    for (int numNodes : {100, 1000, 10000, 100000}) {
        // Create new BST for each test to avoid previous data affecting the test
        BinarySearchTree bstPerf;

        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < numNodes; i++) {
            int value = rand() % 100000;
            bstPerf.add(value);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Time taken to insert " << numNodes << " nodes: " << duration.count() << " ms" << endl;
    }
    return 0;
}