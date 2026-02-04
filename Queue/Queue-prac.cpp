#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

class Queue {
private:
    node* front;
    node* rear;
public:
    Queue(): front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }


    //---------------------------------------------------


    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int value) {
        node* newNode = new node();
        newNode->data = value;
        newNode->next = nullptr;
        if (rear == nullptr) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
        cout << "Enqueued " << value << " onto the queue" << endl;
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue empty! Cannot dequeue" << endl;
            return -1;
        }
        node* temp = front;
        int dequeuedValue = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return dequeuedValue;
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty! Nothing to peek" << endl;
            return -1;
        }
        return front->data;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "\nQueue elements: ";
        node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }




};