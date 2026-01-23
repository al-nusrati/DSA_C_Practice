#include <iostream>

using namespace std;

struct node
{
    int data;
    //---
    node *next;
    node *prev;
};
node *getNewNode(int val){
    // allocate mem for node
    node *newNode = new node;

    // fill node structure
    newNode->data = val;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // return this new node
    return newNode;
}

int getLastNodeData(node *ptr)
{
    int val = 0;
    node *newNode = ptr;
    while(newNode != nullptr){
        val = newNode->data;
        //---
        newNode = newNode->next;
    }
    return val;
}
int nodesCount(node *ptr)
{
    node *newNode = ptr;
    int count = 0;
    while(newNode != nullptr){
        ++count;
        //---
        newNode = newNode->next;
    }
    return count;
}
void traverseForward(node *n1){
    node *newNode = n1;

    while(newNode != nullptr){
        cout << newNode->data << " -> ";
        newNode = newNode->next;
    }
    cout << " NULL";
}

void traverseBackward(node *nodePtr){
    node *currNode = nodePtr;

    while(currNode != nullptr){
        cout << currNode->data << " -> ";
        currNode = currNode->prev;
    }
    cout << " NULL";
}


node *insertAtBeginning(node *ptr, int val){
    node *newNode = getNewNode(val);
    newNode->next = ptr;

    ptr->prev = newNode;
    return newNode;
}

node *getLastNode(node *nodePtr){
    if (nodePtr == nullptr){   // empty list
        return nullptr;
    }

    while (nodePtr->next != nullptr){
        nodePtr = nodePtr->next;
    }

    return nodePtr;         // last node
}

node *insertAtEnd(node *nodePtr, int val){
    node *lastNode = getLastNode(nodePtr);
    node *newNode = getNewNode(val);
    
    newNode->next = nullptr;
    newNode->prev = lastNode;
    lastNode->next = newNode;
    return newNode;
}


void freeMemory(node *head)
{
    node *temp;

    while (head != nullptr){
        temp = head;            // save current node
        head = head->next;      // advance to next node
        delete temp;             // free current node
    }
}



int main(){

    node *n1 = getNewNode(10);
    node *n2 = getNewNode(20);
    node *n3 = getNewNode(30);
    node *n4 = getNewNode(40);
    node *n5 = getNewNode(50);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    n2->prev = n1;
    n3->prev = n2;
    n4->prev = n3;
    n5->prev = n4;

    // insert before --> b1 = 110, b2 = 120, b3 = 130
    node *b1 = insertAtBeginning(n1, 110);
    node *b2 = insertAtBeginning(b1, 120);
    node *b3 = insertAtBeginning(b2, 130);

    node *e1 = insertAtEnd(b3, 210);
    node *e2 = insertAtEnd(b3, 220);
    node *e3 = insertAtEnd(n4, 230);

    traverseForward(b3);
    cout << endl;
    traverseBackward(e3);

    int totalNodes = nodesCount(n1);
    cout << endl << "Total nodes = " << totalNodes;

    int dataLastNode = getLastNodeData(n1);
    cout << endl << "Last node val = " << dataLastNode;

    freeMemory(b3);

    n1 = n2 = n3 = n4 = n5 = b1 = b2 = b3 = e1 = e2 = e3 = nullptr;

    return 0;    
}