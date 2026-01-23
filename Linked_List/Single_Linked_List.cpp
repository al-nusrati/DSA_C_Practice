#include <iostream>

using namespace std;

struct node
{
    int data;
    //---
    node *next;
};

class LinkedList
{
private:
    node *head;
    
    node *getNewNode(int val){
        // allocate mem for node
        node *newNode = new node;

        // fill node structure
        newNode->data = val;
        newNode->next = nullptr;

        // return this new node
        return newNode;
    }
    
    node *getLastNode(){
        if (head == nullptr){   // empty list
            return nullptr;
        }

        node *nodePtr = head;
        while (nodePtr->next != nullptr){
            nodePtr = nodePtr->next;
        }

        return nodePtr;         // last node
    }

public:
    LinkedList(){
        head = nullptr;
    }
    
    ~LinkedList(){
        freeMemory();
    }
    
    void insertAtBeginning(int val){
        node *newNode = getNewNode(val);
        newNode->next = head;
        head = newNode;
    }
    
    void insertAtEnd(int val){
        node *newNode = getNewNode(val);
        
        if(head == nullptr){
            head = newNode;
            return;
        }
        
        node *lastNode = getLastNode();
        lastNode->next = newNode;
    }
    
    void deleteFromStart(){
        if(head == nullptr){
            cout << "List is empty, cannot delete!" << endl;
            return;
        }
        
        node *temp = head;
        head = head->next;
        delete temp;
    }
    
    void traverseForward(){
        node *n1 = head;
        
        while(n1 != nullptr){
            cout << n1->data << " -> ";
            n1 = n1->next;
        }
        cout << "NULL";
    }
    
    int nodesCount(){
        node *ptr = head;
        int count = 0;
        while(ptr != nullptr){
            ++count;
            ptr = ptr->next;
        }
        return count;
    }
    
    int getLastNodeData(){
        int val = 0;
        node *ptr = head;
        while(ptr != nullptr){
            val = ptr->data;
            ptr = ptr->next;
        }
        return val;
    }
    
    void freeMemory(){
        node *temp;
        
        while (head != nullptr){
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};


int main(){

    LinkedList list;
    
    // Build initial 5 nodes
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);

    // insert at beginning
    list.insertAtBeginning(110);
    list.insertAtBeginning(120);
    list.insertAtBeginning(130);

    // insert at end
    list.insertAtEnd(210);
    list.insertAtEnd(220);
    list.insertAtEnd(230);

    list.traverseForward();

    int totalNodes = list.nodesCount();
    cout << endl << "Total nodes = " << totalNodes;

    int dataLastNode = list.getLastNodeData();
    cout << endl << "Last node val = " << dataLastNode;

    return 0;    
}