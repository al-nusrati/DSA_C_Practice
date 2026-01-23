#include <iostream>

using namespace std;

struct node
{
    int data;
    //---
    node *next;
};
node *getNewNode(int val){
    // allocate mem for node
    node *newNode = new node;

    // fill node structure
    newNode->data = val;
    newNode->next = nullptr;

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
    cout << "NULL";
}


node *insertAtBeginning(node *ptr, int val){
    node *newNode = getNewNode(val);
    newNode->next = ptr;

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

node *insertAtEnd(node *head, int val){
    node *newNode = getNewNode(val);
    
    if(head == nullptr){
        return newNode;
    }
    
    node *lastNode = getLastNode(head);
    lastNode->next = newNode;
    
    return head;
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

node *deleteFromStart(node *head){
    if(head == nullptr){   // empty list
        cout << "List is empty, cannot delete!" << endl;
        return nullptr;
    }
    
    node *temp = head;          // save current head
    head = head->next;          // move head to next node
    delete temp;                // free old head
    
    return head;                // return new head
}


int main(){

    node *head = nullptr;
    
    // Build initial 5 nodes using insertAtEnd
    head = insertAtEnd(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    head = insertAtEnd(head, 50);

    // insert at beginning --> 110, 120, 130
    head = insertAtBeginning(head, 110);
    head = insertAtBeginning(head, 120);
    head = insertAtBeginning(head, 130);

    // insert at end --> 210, 220, 230
    head = insertAtEnd(head, 210);
    head = insertAtEnd(head, 220);
    head = insertAtEnd(head, 230);

    head = deleteFromStart(head);
    head = deleteFromStart(head);
    
    traverseForward(head);

    int totalNodes = nodesCount(head);
    cout << endl << "Total nodes = " << totalNodes;

    int dataLastNode = getLastNodeData(head);
    cout << endl << "Last node val = " << dataLastNode;

    freeMemory(head);

    head = nullptr;

    return 0;    
}