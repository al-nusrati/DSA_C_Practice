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
        cout << "returning from (" << btNode->data << ")\n";     // check marker
        return btNode;
    }

    //--- btNode != nullptr -------------------- (not end position)
    else
    {
        
        //  LEFT CHECK
        if (val <= btNode->data && btNode->left == nullptr)
        {
            btNode->left = bst_insert(btNode->left, val);          // end position
        }
        else if (val <= btNode->data && btNode->left != nullptr)
        {
            bst_insert(btNode->left, val);
        }

        //  RIGHT CHECK
        if (val > btNode->data && btNode->right == nullptr)
        {
            btNode->right = bst_insert(btNode->right, val);        // end position
        }
        else if (val > btNode->data && btNode->right != nullptr)
        {
            bst_insert(btNode->right, val);
        }


        cout << "returning from (" << btNode->data << ")\n";       // check marker
        return btNode;
    }
}

// bst = binary search tree
int main(){
    //int tree[12] = { 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56 };
    node* root = nullptr;

    root = bst_insert(root, 10); // nullptr , 10

    cout << "\n<---- 2nd number ---->\n";
    root = bst_insert(root, 8);   // root , 8

    cout << "\n<---- 3rd number ---->\n";
    root = bst_insert(root, 5);   // root , 5

    cout << "\n<---- 4th number ---->\n";
    root = bst_insert(root, 3);   // root , 3

    //--------------------------- greater than value
    cout << "\n<---- 5th number ---->\n";
    root = bst_insert(root, 50);   // root , 50

    cout << "\n<---- 6th number ---->\n";
    root = bst_insert(root, 60);   // root , 60

    delete root;
    return 0;
}

// // simplified bst method 
// node *bst_insert(node *btNode, int val){
//     if(btNode == nullptr)
//     {
//         node *newNode = createNode(val);
//         cout << "returning from (" << newNode->data << ")\n";
//         return newNode;
//     }
    
//     // Just check the value, let recursion handle nullptr
//     if (val <= btNode->data)
//         btNode->left = bst_insert(btNode->left, val);
//     else
//         btNode->right = bst_insert(btNode->right, val);
    
//     cout << "returning from (" << btNode->data << ")\n";
//     return btNode;
// }