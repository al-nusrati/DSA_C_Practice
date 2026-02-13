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
        sort(root->left);
        cout << root->data << " ";
        sort(root->right);
    }
}

void freeTree(node *root){
    if(root){
        freeTree(root->left);
        freeTree(root->right);
        delete root;

    }
}

// bst = binary search tree
int main(){
    int tree[12] = { 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56 };

    node* root = nullptr;

    for(int val : tree){
        root = bst_insert(root, val);

    }

    sort(root);

    freeTree(root);

    int test = 0;

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
