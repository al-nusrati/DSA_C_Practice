#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
    node *prev;
};

class CircularStaticQueue{
private:
    int size;
    int arr[size];  // here issue is: 
    node* front;
    node* rear;

public:
    CircularStaticQueue(): front(nullptr), rear(nullptr) {}

    ~CircularStaticQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
//-------------------------------------------------------------
    void enqueue(int value){
        node* newNode = new node();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if(front == nullptr){
            front = rear = newNode;
            front->next = front;
            front->prev = front;
            return;
        }

        rear->next = newNode;
        newNode->prev = rear;
        rear = newNode;
        rear->next = front;
        front->prev = rear;

        cout << "Enqueued " << value << " onto the circular queue" << endl;
    }
    int dequeue(){
        if(front == nullptr){
            cout << "Circular Queue empty! Cannot dequeue" << endl;
            return -1;
        }

        node* temp = front;
        int dequeuedValue = front->data;

        if(front == rear){
            front = rear = nullptr;
        } else {
            front = front->next;
            rear->next = front;
            front->prev = rear;
        }

        delete temp;
        return dequeuedValue;
    }
    bool isEmpty(){
        return front == nullptr;
    }
    

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty! Nothing to peek" << endl;
            return -1;
        }
        return front->data;
    }
    
};

int main(){



    return 0;
}