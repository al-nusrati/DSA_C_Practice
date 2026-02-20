//binary tree
#include <iostream>
using namespace std;

struct node {
    int data;
    //----------
    node *left;
    node *right;
};

// --- Create a new node ---
node* createNode(int val) {
    node* newNode = new node;
    newNode->data = val;
    //---
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


node *bst_insert(node *btNode, int val){
    //--- btNode == nullptr -------------------- (end position)
    if(btNode == nullptr)
    {
        node *newNode = createNode(val);
        btNode = newNode;
        return btNode;
    }

    //--- btNode != nullptr -------------------- (not end position)
    else
    { 
                //  LEFT CHECK
                if (val <= btNode->data)    
                {
                    btNode->left = bst_insert(btNode->left, val);
                }
                //  RIGHT CHECK
                if (val > btNode->data)
                {
                    btNode->right = bst_insert(btNode->right, val);
                }

        return btNode;
    }
}


void sort(node *root) {
    if(root) {                  // ------- (end condition)
        // cout << root->data << " ";   //preorder: root, left, right
        sort(root->left);
        cout << root->data << " ";  //inorder: left, root, right
        sort(root->right);
        // cout << root->data << " ";   //postorder: left, right, root
    }
}

void freeTree(node *root){
    if(root){
        freeTree(root->left);
        freeTree(root->right);
        delete root;

    }
}


void findNode(node *root, int val){
    if(root == NULL){
        cout << "No Node found" << endl;
        return;
    }
    if(root->data == val){
        cout << "Node found: " << root->data << endl;
    }
    if(val < root->data){
        cout << "Going left from node: " << root->data << "\n";
        return findNode(root->left, val);
    }
    else{
        cout << "Going right from node: " << root->data << "\n";
        return findNode(root->right, val);
    }
}


// bst = binary search tree
int main() {
    node* root = nullptr;

    // Insert values into BST
    root = bst_insert(root, 50);
    root = bst_insert(root, 30);
    root = bst_insert(root, 70);
    root = bst_insert(root, 20);
    root = bst_insert(root, 40);
    root = bst_insert(root, 60);
    root = bst_insert(root, 80);

    // Inorder traversal (sorted output)
    cout << "Inorder traversal: ";
    sort(root);
    cout << endl;

    // Search tests
    cout << "\nSearching for 40:\n";
    findNode(root, 40);

    cout << "\nSearching for 90:\n";
    findNode(root, 90);

    // Free memory
    freeTree(root);
    root = nullptr;

    return 0;
}

















    // //  LEFT CHECK
    // if (val <= btNode->data && btNode->left == nullptr)
    // {
    //     btNode->left = bst_insert(btNode->left, val);          // end position
    // }
    // else if (val <= btNode->data && btNode->left != nullptr)
    // {
    //     btNode->left = bst_insert(btNode->left, val);
    // }
    // }

    // //  RIGHT CHECK
    // if (val > btNode->data && btNode->right == nullptr)
    // {
    //     btNode->right = bst_insert(btNode->right, val);        // end position
    // }
    // else if (val > btNode->data && btNode->right != nullptr)
    // {
    //     btNode->right = bst_insert(btNode->right, val);
