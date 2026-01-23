#include <iostream>

using namespace std;

// STEP 1: Define what a single node looks like
// Think of a node as a box that holds:
// 1. Some data (a number)
// 2. An arrow pointing to the next box
struct node
{
    int data;           // The actual number we want to store
    //---
    node *next;         // Arrow/pointer to the next node in the chain
};

// STEP 2: Create a LinkedList class to manage all the nodes
// Think of this as a train where each car (node) is connected to the next
class LinkedList
{
private:    // These are helper functions - only used inside the class
    node *head;     // This is like the "start point" of our train
                    // It points to the very first node
    
    // HELPER FUNCTION 1: Creates a brand new node (like building a new train car)
    node *getNewNode(int val){
        // allocate mem for node - Ask computer for space to store a node
        node *newNode = new node;

        // fill node structure - Put the number inside and set arrow to nothing
        newNode->data = val;            // Store the number
        newNode->next = nullptr;        // Arrow points to nothing (yet)

        // return this new node - Give back the address of this new node
        return newNode;
    }
    
    // HELPER FUNCTION 2: Finds the last node in the chain (the last train car)
    node *getLastNode(){
        if (head == nullptr){   // empty list - No train cars at all!
            return nullptr;
        }

        node *nodePtr = head;   // Start from the first car
        // Keep moving to next car until we find one with no next car
        while (nodePtr->next != nullptr){
            nodePtr = nodePtr->next;    // Move to next car
        }

        return nodePtr;         // last node - Found the last car!
    }

public:     // These are functions anyone can use
    
    // CONSTRUCTOR: Runs automatically when we create a LinkedList
    // Sets up an empty list (no train cars yet)
    LinkedList(){
        head = nullptr;     // Start with nothing - empty train
    }
    
    // DESTRUCTOR: Runs automatically when LinkedList is destroyed
    // Cleans up all nodes to prevent memory waste
    ~LinkedList(){
        freeMemory();   // Delete all train cars when we're done
    }
    
    // METHOD 1: Add a new node at the START of the list (front of train)
    void insertAtBeginning(int val){
        node *newNode = getNewNode(val);    // Build a new train car
        newNode->next = head;               // New car points to old first car
        head = newNode;                     // New car becomes the first car
    }
    
    // METHOD 2: Add a new node at the END of the list (back of train)
    void insertAtEnd(int val){
        node *newNode = getNewNode(val);    // Build a new train car
        
        // SPECIAL CASE: If the train is empty
        if(head == nullptr){        // Check if list is EMPTY
            head = newNode;         // If empty, new node becomes the head
            return;                 // Job done! Exit the function
        }
        
        // NORMAL CASE: Train has cars, add to the end
        node *lastNode = getLastNode();     // Find the last car
        lastNode->next = newNode;           // Connect last car to new car
    }
    
    // METHOD 3: Remove the first node (remove first train car)
    void deleteFromStart(){
        // SAFETY CHECK: Can't delete from empty list
        if(head == nullptr){
            cout << "List is empty, cannot delete!" << endl;
            return;     // Exit - nothing to delete
        }
        
        node *temp = head;          // Remember the first car (to delete it)
        head = head->next;          // Second car becomes the first car
        delete temp;                // Destroy the old first car (free memory)
    }
    
    // METHOD 4: Print all nodes from start to end (show entire train)
    void traverseForward(){
        node *n1 = head;    // Start from the first car
        
        // Keep going until we reach the end (nullptr)
        while(n1 != nullptr){
            cout << n1->data << " -> ";     // Print the number in this car
            n1 = n1->next;                  // Move to next car
        }
        cout << "NULL";     // Show we reached the end
    }
    
    // METHOD 5: Count how many nodes exist (count train cars)
    int nodesCount(){
        node *ptr = head;   // Start from first car
        int count = 0;      // Start counting from 0
        
        // Visit each car and count it
        while(ptr != nullptr){
            ++count;            // Add 1 to count
            ptr = ptr->next;    // Move to next car
        }
        return count;   // Return total number of cars
    }
    
    // METHOD 6: Get the data from the last node (check last car's number)
    int getLastNodeData(){
        int val = 0;        // Default value if list is empty
        node *ptr = head;   // Start from first car
        
        // Keep moving and remember each number we see
        while(ptr != nullptr){
            val = ptr->data;        // Remember this car's number
            ptr = ptr->next;        // Move to next car
        }
        return val;     // Return the last number we saw
    }
    
    // METHOD 7: Delete ALL nodes (destroy entire train)
    void freeMemory(){
        node *temp;     // Temporary pointer to remember current car
        
        // Keep deleting first car until train is empty
        while (head != nullptr){
            temp = head;            // Remember current first car
            head = head->next;      // Move head to next car
            delete temp;            // Destroy the remembered car
        }
    }
};


// MAIN PROGRAM: Where we actually use our LinkedList
int main(){

    LinkedList list;    // Create an empty train
    
    // Build initial 5 nodes (add 5 cars to back of train)
    list.insertAtEnd(10);       // Train: 10
    list.insertAtEnd(20);       // Train: 10 -> 20
    list.insertAtEnd(30);       // Train: 10 -> 20 -> 30
    list.insertAtEnd(40);       // Train: 10 -> 20 -> 30 -> 40
    list.insertAtEnd(50);       // Train: 10 -> 20 -> 30 -> 40 -> 50

    // insert at beginning (add cars to front of train)
    list.insertAtBeginning(110);    // Train: 110 -> 10 -> 20 -> 30 -> 40 -> 50
    list.insertAtBeginning(120);    // Train: 120 -> 110 -> 10 -> 20 -> 30 -> 40 -> 50
    list.insertAtBeginning(130);    // Train: 130 -> 120 -> 110 -> 10 -> 20 -> 30 -> 40 -> 50

    // insert at end (add more cars to back)
    list.insertAtEnd(210);      // Add 210 at end
    list.insertAtEnd(220);      // Add 220 at end
    list.insertAtEnd(230);      // Add 230 at end

    // Show the entire train
    list.traverseForward();

    // Count how many cars in train
    int totalNodes = list.nodesCount();
    cout << endl << "Total nodes = " << totalNodes;

    // Check what number is in the last car
    int dataLastNode = list.getLastNodeData();
    cout << endl << "Last node val = " << dataLastNode;

    // When program ends, destructor automatically cleans up all nodes!
    return 0;    
}