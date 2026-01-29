#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T> *next;
};

template <typename T>
class linkedList {
private:
    node<T> *head;
    node<T> *tail;  // NEW: tail pointer

    node<T>* getNewNode(int pos){
        node<T> *newNode = new node<T>;
        newNode->data = pos;
        newNode->next = NULL;
        return newNode;
    }

    node<T>* getLastNode(){
        return tail;  // UPDATED: directly return tail
    }

    void traverseReverseHelper(node<T> *n) {
        if(n == NULL) {
            return;
        }
        traverseReverseHelper(n->next);
        cout << n->data << " -> ";
    }

public:
    linkedList() { 
        head = NULL; 
        tail = NULL;  // UPDATED: initialize tail
    }
    
    linkedList(const linkedList& other) {
        head = NULL;
        tail = NULL;  // UPDATED: initialize tail
        node<T>* temp = other.head;
        while(temp != NULL) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }
    
    ~linkedList() { freeMemory(); }

    void insertAtBeginning(int pos) {
        node<T> *nNode = getNewNode(pos);
        nNode->next = head;
        head = nNode;
        
        if(tail == NULL) {  // UPDATED: if list was empty
            tail = head;
        }
    }

    void insertAtEnd(int pos) {
        node<T> *nNode = getNewNode(pos);
        
        if(head == NULL){  // UPDATED: empty list
            head = nNode;
            tail = nNode;
            return;
        }
        
        tail->next = nNode;  // UPDATED: use tail directly
        tail = nNode;        // UPDATED: update tail
    }

    void insertAtAnyPos(int position, int val) {
        if(position < 0 || position > nodeCount()) {
            cout << "Invalid position!" << endl;
            return;
        }
        if(position == 0) {
            insertAtBeginning(val);
            return;
        }
        
        node<T> *nNode = getNewNode(val);
        node<T> *temp = head;
        
        for(int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        
        nNode->next = temp->next;
        temp->next = nNode;
        
        if(nNode->next == NULL) {  // UPDATED: if inserted at end
            tail = nNode;
        }
    }

    void deleteFromStart() {
        if(head == NULL){
            cout << "List is empty, cannot delete it!" << endl;
            return;     
        }
        
        node<T> *temp = head;         
        head = head->next;
        delete temp;
        
        if(head == NULL) {  // UPDATED: if list became empty
            tail = NULL;
        }
    }

    void deleteFromEnd() {
        if(head == NULL){
            cout << "List is empty, cannot delete it!" << endl;
            return;
        }
        
        if(head->next == NULL){  // UPDATED: only one node
            delete head;
            head = NULL;
            tail = NULL;
            return;
        }
        
        node<T>* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;      
        }
        
        delete temp->next;         
        temp->next = NULL;
        tail = temp;  // UPDATED: update tail
    }

    void deleteAtAnyPos(int position) {
        if (head == NULL) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if (position == 1) {
            deleteFromStart();
            return;
        }
        
        node<T>* temp = head;
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->next;
        }
        
        if (temp == NULL || temp->next == NULL) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        node<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        
        if(temp->next == NULL) {  // UPDATED: if deleted last node
            tail = temp;
        }
        
        delete toDelete;
    }

    void reverse() {
        if(head == NULL || head->next == NULL) {
            return;
        }
        
        node<T> *prev = NULL;
        node<T> *current = head;
        node<T> *next = NULL;
        
        tail = head;  // UPDATED: old head becomes tail
        
        while(current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    int nodeCount() {
        node<T> *ptr = head;
        int count = 0;
        while (ptr != NULL){
            ++count;
            ptr = ptr->next;
        }
        return count;
    }

    int getNthNode(int n) {
        if(n < 1 || n > nodeCount()) {
            cout << "Invalid position!" << endl;
            return -1;
        }
        
        node<T> *temp = head;
        for(int i = 1; i < n; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    int getLastNodeData() {
        if(tail == NULL) {
            return 0;
        }
        return tail->data;  // UPDATED: use tail directly
    }

    bool isEmpty() { return (head == NULL); }

    bool searchData(int pos) {
        node<T> *temp = head;
        while (temp != NULL){
            if(temp->data == pos){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void findMiddle() {
        if(head == NULL) {
            cout << "List is empty!" << endl;
            return;
        }
        
        node<T> *slow = head;
        node<T> *fast = head;
        
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << "Middle element: " << slow->data << endl;
    }

    void traverseForward() {
        node<T> *n1 = head;
        while(n1 != NULL){
            cout << n1->data << " -> ";
            n1 = n1->next;
        }
        cout << "NULL" << endl;  // FIXED: was "List is Empty"
    }

    void traverseReverse() {
        traverseReverseHelper(head);
        cout << "NULL" << endl;
    }

    void freeMemory() {
        node<T> *temp;
        while (head != NULL){
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;  // UPDATED: reset tail
    }
};


int main (){
    linkedList<int> list;
    linkedList<int> copyList(list);

    cout << "Is list empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(3);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    cout << "Inserted values 1-5 at the end." << endl;

    cout << "Is list empty: " << (list.isEmpty() ? "Yes" : "No") << endl;
    list.traverseForward();

    list.deleteFromStart();
    cout << "Deleted first element." << endl;
    list.traverseForward();

    list.insertAtBeginning(6);
    cout << "6 inserted at start." << endl;
    list.traverseForward();

    list.insertAtEnd(9);
    cout << "9 inserted at end." << endl;
    list.traverseForward();

    list.deleteFromEnd();
    cout << "Deleted last element." << endl;
    list.traverseForward();

    list.deleteAtAnyPos(3);
    cout << "Deleted element at position 3" << endl;
    list.traverseForward();

    list.insertAtAnyPos(4, 7);
    cout << "Inserted 7 at position 4." << endl;
    list.traverseForward();

    list.deleteFromStart();
    list.traverseForward();

    list.deleteAtAnyPos(2);
    cout << "Deleted element at position 2" << endl;
    list.traverseForward();

    list.deleteFromStart();
    list.deleteFromStart();
    list.deleteFromStart();
    list.traverseForward();

    return 0;
}