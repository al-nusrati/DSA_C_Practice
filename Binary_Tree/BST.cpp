#include <iostream>
using namespace std;

// --- 1. Node Structure ---
struct node {
    int data;
    node *left;
    node *right;
};

// --- 2. BST Class Definition ---
class BST {
private:
    node *root;

    // ==========================================
    // PRIVATE HELPER FUNCTIONS (The Logic Core)
    // ==========================================

    // --- Create a new node ---
    node* createNode(int val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // --- Recursive Insert ---
    node* bst_insert(node *btNode, int val) {
        // Base Case: Found the spot
        if (btNode == nullptr) {
            return createNode(val);
        }

        // Recursive Step
        if (val <= btNode->data) {
            btNode->left = bst_insert(btNode->left, val);
        }
        else {
            btNode->right = bst_insert(btNode->right, val);
        }
        return btNode; // Return pointer to maintain links
    }

    // --- Find Minimum (Helper for Delete) ---
    node* findMin(node *root) {
        node *current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // --- Recursive Delete (The Tricky Part) ---
    node* bst_delete(node *root, int val) {
        if (root == nullptr) return nullptr; // Not found

        // 1. Search for the node
        if (val < root->data) {
            root->left = bst_delete(root->left, val);
        }
        else if (val > root->data) {
            root->right = bst_delete(root->right, val);
        }
        
        // 2. Node Found (val == root->data)
        else {
            // Case 1: No Child (Leaf)
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            // Case 2: One Child
            else if (root->left == nullptr) {       // Only Right Child
                node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {      // Only Left Child
                node *temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Two Children
            else {
                node *successor = findMin(root->right);             // Find Min in Right Subtree
                root->data = successor->data;                       // Copy value
                root->right = bst_delete(root->right, successor->data); // Delete the duplicate
            }
        }
        return root;
    }

    // --- Traversals ---
    void inorder(node *root) {
        if (root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    void preorder(node *root) {
        if (root) {
            cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void postorder(node *root) {
        if (root) {
            postorder(root->left);
            postorder(root->right);
            cout << root->data << " ";
        }
    }

    // --- Deep Copy (Preorder Logic) ---
    node* copyTree(node *root) {
        if (root == nullptr) return nullptr;

        node *newNode = createNode(root->data);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

    // --- Free Memory (Postorder Logic) ---
    void freeTree(node *root) {
        if (root) {
            freeTree(root->left);
            freeTree(root->right);
            delete root;
        }
    }

    // --- Search Node ---
    void findNode(node *root, int val) {
        if (root == nullptr) {
            cout << "Node " << val << " NOT found." << endl;
            return;
        }
        if (root->data == val) {
            cout << "Node " << val << " FOUND." << endl;
            return;
        }
        
        if (val < root->data) 
            findNode(root->left, val);
        else 
            findNode(root->right, val);
    }

public:
    // ==========================================
    // PUBLIC INTERFACE (Wrappers)
    // ==========================================
    
    BST() { root = nullptr; }   // Constructor
    
    ~BST() {                    // Destructor
        freeTree(root); 
        root = nullptr; 
    }

    void insert(int val) { root = bst_insert(root, val); }
    void remove(int val) { root = bst_delete(root, val); }

    void inorder()   { inorder(root);   }
    void preorder()  { preorder(root);  }
    void postorder() { postorder(root); }

    void findNode(int val) { findNode(root, val); }

    void isEmpty() {
        if (root == nullptr) cout << "Tree is EMPTY." << endl;
        else cout << "Tree is NOT empty." << endl;
    }

    // Returns a new BST object (Deep Copy)
    BST copyTree() {
        BST newBST;
        newBST.root = copyTree(root);
        return newBST;
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    BST bst;

    cout << "--- Inserting Nodes ---" << endl;
    bst.insert(21);
    bst.insert(22);
    bst.insert(10);
    bst.insert(19);
    bst.insert(17);
    bst.insert(6);
    
    cout << "Inorder   : "; bst.inorder();   cout << endl;
    cout << "Preorder  : "; bst.preorder();  cout << endl;
    cout << "Postorder : "; bst.postorder(); cout << endl;

    cout << "\n--- Searching ---" << endl;
    bst.findNode(6);
    bst.findNode(99); // Not in tree

    cout << "\n--- Deleting Nodes ---" << endl;
    cout << "Removing 10 (Node with 2 children logic check)..." << endl;
    bst.remove(10);
    cout << "Inorder after delete: "; bst.inorder(); cout << endl;

    cout << "\n--- Deep Copy Test ---" << endl;
    BST bst2 = bst.copyTree();
    
    cout << "Original BST : "; bst.inorder(); cout << endl;
    cout << "Copied BST2  : "; bst2.inorder(); cout << endl;

    cout << "\nModifying BST2 (Removing 21)..." << endl;
    bst2.remove(21);
    
    cout << "Original BST : "; bst.inorder(); cout << " (Should remain unchanged)" << endl;
    cout << "Copied BST2  : "; bst2.inorder(); cout << endl;

    cout << "\n--- Destructor will run automatically here ---" << endl;
    
    system("pause>0");
    return 0;
}