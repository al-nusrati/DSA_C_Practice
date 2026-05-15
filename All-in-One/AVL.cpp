#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
T getValidInput(string text) {
    T value;
    while (true) {
        cout << text;
        if (cin >> value)    return value;
        cout << "Invalid input! enter correct data type.\n";
        cin.clear();  
        cin.ignore(1000, '\n');   
    }
}

struct node {
    string filename;            
    vector<string> paths;       
    int height;                 
    node* left;
    node* right;
};

class AVL {
private:    // ==========================================
    node* root;
    node* createNode(string fileName, string fullPath) {
        node* newNode     = new node;
        newNode->filename = fileName;
        newNode->paths.push_back(fullPath);
        newNode->height   = 1;         
        newNode->left     = nullptr;
        newNode->right    = nullptr;
        return newNode;
    }

    int getHeight(node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    void updateHeight(node* n) {
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    }

    int getBalance(node* n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    node* rotateRight(node* y) {
        node* x  = y->left;
        node* T2 = x->right;

        x->right = y;
        y->left  = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    node* rotateLeft(node* x) {
        node* y  = x->right;
        node* T2 = y->left;

        y->left  = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    node* avl_insert(node* rootNode, string fileName, string fullPath) {
        if (rootNode == nullptr) return createNode(fileName, fullPath);

        if (fileName == rootNode->filename) {
            rootNode->paths.push_back(fullPath);
            return rootNode;
        }
        else if (fileName < rootNode->filename)    rootNode->left  = avl_insert(rootNode->left,  fileName, fullPath);
        else    rootNode->right = avl_insert(rootNode->right, fileName, fullPath);

        updateHeight(rootNode);
        int balance = getBalance(rootNode);
        if (balance > 1 && fileName < rootNode->left->filename)    return rotateRight(rootNode);
        if (balance < -1 && fileName > rootNode->right->filename)    return rotateLeft(rootNode);

        if (balance > 1 && fileName > rootNode->left->filename) {
            rootNode->left = rotateLeft(rootNode->left);
            return rotateRight(rootNode);
        }

        if (balance < -1 && fileName < rootNode->right->filename) {
            rootNode->right = rotateRight(rootNode->right);
            return rotateLeft(rootNode);
        }
        return rootNode;
    }

    void freeTree(node* root) {
        if (root) {
            freeTree(root->left);
            freeTree(root->right);
            delete root;
        }
    }

    node* searchNode(node* root, string fileName) {
        if (root == nullptr)         return nullptr;
        if (root->filename == fileName) return root;

        if (fileName < root->filename)    return searchNode(root->left,  fileName);
        else    return searchNode(root->right, fileName);
    }

public:     // ==========================================
    

    AVL()  { root = nullptr; }      

    ~AVL() {                        
        freeTree(root);
        root = nullptr;
    }

    void insert(string fileName, string fullPath) { root = avl_insert(root, fileName, fullPath); }
    
    node* search(string fileName) { return searchNode(root, fileName); }
    bool isEmpty() { return (root == nullptr); }

    void refresh(string rootPath);
};