#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node<T>* next;
    node<T>* prev;
};

template <typename T>
class DoublyLinkedList {
private:
    node<T>* head;
    node<T>* tail;

    node<T>* getNewNode(T val) {
        node<T>* newNode = new node<T>;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

    node<T>* getLastNode() {
        return tail;
    }

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    DoublyLinkedList(const DoublyLinkedList& other) {
        head = nullptr;
        tail = nullptr;
        node<T>* temp = other.head;
        while(temp != nullptr) {
            insertAtEnd(temp->data);
            temp = temp->next;
        }
    }

    ~DoublyLinkedList() {
        freeMemory();
    }

    void insertAtBeginning(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) {  // Empty list
            head = tail = newNode;
            return;
        }
        
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(T val) {
        node<T>* newNode = getNewNode(val);
        
        if(head == nullptr) {  // Empty list
            head = tail = newNode;
            return;
        }
        
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void insertAtAnyPos(int position, T val) {
        if(position <= 0 || position > nodeCount() + 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(position == 1) {
            insertAtBeginning(val);
            return;
        }
        
        if(position == nodeCount() + 1) {
            insertAtEnd(val);
            return;
        }
        
        node<T>* newNode = getNewNode(val);
        node<T>* temp = head;
        
        for(int i = 1; i < position - 1; i++) {
            temp = temp->next;
        }
        
        newNode->next = temp->next;
        newNode->prev = temp;
        
        if(temp->next != nullptr) {
            temp->next->prev = newNode;
        }
        
        temp->next = newNode;
    }

    void deleteFromStart() {
        if(!isEmpty()){
            node<T>* temp = head;
            if( head == tail) {  
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            
            delete temp;
        }    
    }

    void deleteFromEnd() {
        if(head == nullptr) {
            cout << "Cannot delete from end, list is empty!" << endl;
            return;
        }
        
        node<T>* temp = tail;
        
        if(head == tail) { 
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        delete temp;
    }

    void deleteAtAnyPos(int position) {
        if(head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        if(position <= 0 || position > nodeCount()) {
            cout << "Invalid position!" << endl;
            return;
        }
        
        if(position == 1) {
            deleteFromStart();
            return;
        }
        
        if(position == nodeCount()) {
            deleteFromEnd();
            return;
        }
        
        node<T>* temp = head;
        for(int i = 1; i < position; i++) {
            temp = temp->next;
        }
        
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        delete temp;
    }

    void reverse() {
        if(head == nullptr || head->next == nullptr) {
            return;
        }
        
        node<T>* current = head;
        node<T>* temp = nullptr;
        
        // Swap head and tail
        tail = head;
        
        while(current != nullptr) {
            // Swap next and prev pointers
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            
            // Move to next node (which is prev now)
            current = current->prev;
        }
        
        // temp->prev is the new head
        if(temp != nullptr) {
            head = temp->prev;
        }
    }

    int nodeCount() {
        int count = 0;
        node<T>* temp = head;
        while(temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    T getNthNode(int n) {
        if(n < 1 || n > nodeCount()) {
            cout << "Invalid position!" << endl;
            return T();
        }
        
        node<T>* temp = head;
        for(int i = 1; i < n; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    T getLastNodeData() {
        if(tail == nullptr) {
            cout << "List is empty!" << endl;
            return T();
        }
        return tail->data;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    bool searchData(T val) {
        node<T>* temp = head;
        while(temp != nullptr) {
            if(temp->data == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void findMiddle() {
        if(head == nullptr) {
            cout << "List is empty!" << endl;
            return;
        }
        
        node<T>* slow = head;
        node<T>* fast = head;
        
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << "Middle element: " << slow->data << endl;
    }

    void traverseForward() {
        node<T>* temp = head;
        while(temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void traverseReverse() {
        node<T>* temp = tail;
        while(temp != nullptr) { 
            cout << temp->data << " -> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    void freeMemory() {
        node<T>* temp;
        while(head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
};

int main() {
    DoublyLinkedList<int> list;

    // Test isEmpty
    cout << "Is list empty: " << (list.isEmpty() ? "Yes" : "No") << endl;

    // Insert at end
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    list.insertAtEnd(50);
    cout << "Inserted 10, 20, 30, 40, 50 at end" << endl;

    // Traverse forward
    cout << "Forward: ";
    list.traverseForward();

    // Traverse backward
    cout << "Backward: ";
    list.traverseReverse();

    // Insert at beginning
    list.insertAtBeginning(110);
    list.insertAtBeginning(120);
    list.insertAtBeginning(130);
    cout << "\nInserted 110, 120, 130 at beginning" << endl;
    cout << "Forward: ";
    list.traverseForward();

    // Node count
    cout << "\nTotal nodes: " << list.nodeCount() << endl;

    // Get last node data
    cout << "Last node data: " << list.getLastNodeData() << endl;

    // Find middle
    list.findMiddle();

    // Get Nth node
    cout << "3rd node: " << list.getNthNode(3) << endl;

    // Search
    cout << "Search 30: " << (list.searchData(30) ? "Found" : "Not Found") << endl;
    cout << "Search 999: " << (list.searchData(999) ? "Found" : "Not Found") << endl;

    // Insert at position
    list.insertAtAnyPos(4, 999);
    cout << "\nInserted 999 at position 4" << endl;
    cout << "Forward: ";
    list.traverseForward();

    // Delete from start
    list.deleteFromStart();
    cout << "\nDeleted from start" << endl;
    cout << "Forward: ";
    list.traverseForward();

    // Delete from end
    list.deleteFromEnd();
    cout << "\nDeleted from end" << endl;
    cout << "Forward: ";
    list.traverseForward();

    // Delete at position
    list.deleteAtAnyPos(3);
    cout << "\nDeleted at position 3" << endl;
    cout << "Forward: ";
    list.traverseForward();

    // Reverse
    list.reverse();
    cout << "\nReversed list" << endl;
    cout << "Forward: ";
    list.traverseForward();
    cout << "Backward: ";
    list.traverseReverse();

    // Copy constructor test
    DoublyLinkedList<int> copyList(list);
    cout << "\nCopy of list:" << endl;
    cout << "Forward: ";
    copyList.traverseForward();

    return 0;
}