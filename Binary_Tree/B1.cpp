//binary tree
#include <iostream>
using namespace std;

struct node {
    int data;
    //----------
    node *left;
    node *right;
};
    node* root = nullptr;


struct node *getNewNode(int val){
    // allocate mem for node
    struct node *newNode = new node;

    // fill node structure
    newNode->data = val;
    newNode->left = nullptr;
    newNode->right = nullptr;

    // return this new node
    return newNode;
}


struct node *bst_insert(struct node *root, int val){

    if(root == nullptr){
        return getNewNode(val);
    }
    if(val <= root->data){
        root->left = bst_insert(root->left, val);
    }
    else {
        root->right = bst_insert(root->right, val);
    }
    return root;
}


int main(){

    int tree[12] = { 50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56 };

    struct node *n1 = bst_insert(root, 10); // bst = binary search tree
    struct node *n2 = bst_insert(root, 8);
    cout << n1->data << "  ->  " << n2->data;

    delete root;
    return 0;
}


