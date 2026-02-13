#include <iostream>
using namespace std;

#define N 5

// ==================== DOUBLY LINKED LIST (from my Lab 03) ====================
template <typename T>
class DoublyLinkedList {
private:
    struct node {
        T data;
        node* next;
        node* prev;
    };
    node* head;
    node* tail;

public:
    DoublyLinkedList() {
        head = tail = nullptr;
    }

    void insertAtBeginning(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->prev = nullptr;
        newNode->next = head;
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtEnd(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = nullptr;
        newNode->prev = tail;
        
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void deleteFromStart() {
        if (head == nullptr) {
            cout << "Empty List" << endl;
            return;
        }
        node* temp = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }
        delete temp;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    void display() {
        node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== STATIC CIRCULAR QUEUE ====================
template <typename T>
class StaticCircularQueue {
private:
    T queue[N];
    int front, rear;

public:
    StaticCircularQueue() {
        front = rear = -1;
    }

    bool isEmpty() {
        return (front == -1 && rear == -1);
    }

    bool isFull() {
        return ((rear + 1) % N == front);
    }

    void enqueue(T v) {
        if (isFull()) {
            cout << "Overflow! Queue is full." << endl;
        } else if (isEmpty()) {
            front = rear = 0;
            queue[rear] = v;
        } else {
            rear = (rear + 1) % N;
            queue[rear] = v;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow! Queue is empty." << endl;
        } else if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % N;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        int i = front;
        while (i != rear) {
            cout << queue[i] << " ";
            i = (i + 1) % N;
        }
        cout << queue[rear] << endl;
    }

    T getFront() {
        if (!isEmpty()) return queue[front];
        return T();
    }
};

// ==================== DYNAMIC QUEUE (Linked List) ====================
template <typename T>
class DynamicQueue {
private:
    struct node {
        T data;
        node* next;
    };
    node *front, *rear;

    node* getNewNode(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = nullptr;
        return newNode;
    }

public:
    DynamicQueue() {
        front = rear = nullptr;
    }

    bool isEmpty() {
        return (front == nullptr);
    }

    void enqueue(T x) {
        node* newNode = getNewNode(x);
        if (front == nullptr && rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty" << endl;
            return;
        }
        node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    T getFront() {
        if (front != nullptr) return front->data;
        return T();
    }

    ~DynamicQueue() {
        while (front != nullptr) {
            dequeue();
        }
    }
};

// ==================== DYNAMIC QUEUE (Using DoublyLinkedList) ====================
template <typename T>
class QueueUsingList {
private:
    DoublyLinkedList<T> list;

public:
    void enqueue(T val) {
        list.insertAtEnd(val);
    }

    void dequeue() {
        list.deleteFromStart();
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    void display() {
        list.display();
    }
};

// ==================== STATIC STACK ====================
template <typename T>
class StaticStack {
private:
    T stack[N];
    int top;

public:
    StaticStack() {
        top = -1;
    }

    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == N - 1);
    }

    void push(T data) {
        if (isFull()) {
            cout << "Overflow! Stack is full." << endl;
        } else {
            top++;
            stack[top] = data;
        }
    }

    void pop() {
        if (isEmpty()) {
            cout << "Underflow! Stack is empty." << endl;
        } else {
            top--;
        }
    }

    T peek() {
        if (!isEmpty()) return stack[top];
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << " ";
        }
        cout << endl;
    }
};

// ==================== DYNAMIC STACK (Linked List) ====================
template <typename T>
class DynamicStack {
private:
    struct node {
        T data;
        node* next;
    };
    node* top;

public:
    DynamicStack() {
        top = nullptr;
    }

    bool isEmpty() {
        return (top == nullptr);
    }

    void push(T val) {
        node* newNode = new node;
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        node* temp = top;
        top = top->next;
        delete temp;
    }

    T peek() {
        if (top != nullptr) return top->data;
        return T();
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        node* temp = top;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~DynamicStack() {
        while (top != nullptr) {
            pop();
        }
    }
};

// ==================== DYNAMIC STACK (Using DoublyLinkedList) ====================
template <typename T>
class StackUsingList {
private:
    DoublyLinkedList<T> list;

public:
    void push(T val) {
        list.insertAtBeginning(val);
    }

    void pop() {
        list.deleteFromStart();
    }

    bool isEmpty() {
        return list.isEmpty();
    }

    void display() {
        list.display();
    }
};

int main() {
    cout << "========== TESTING STATIC CIRCULAR QUEUE ==========" << endl;
    StaticCircularQueue<int> scq;
    scq.enqueue(10);
    scq.enqueue(20);
    scq.enqueue(30);
    scq.enqueue(40);
    scq.enqueue(50);
    cout << "After enqueuing 5 elements: ";
    scq.display();
    scq.enqueue(60); // Should show overflow
    scq.dequeue();
    scq.dequeue();
    cout << "After 2 dequeues: ";
    scq.display();
    scq.enqueue(60);
    scq.enqueue(70);
    cout << "After circular enqueues: ";
    scq.display();

    cout << "\n========== TESTING DYNAMIC QUEUE (Linked List) ==========" << endl;
    DynamicQueue<int> dq;
    dq.enqueue(100);
    dq.enqueue(200);
    dq.enqueue(300);
    cout << "After enqueuing: ";
    dq.display();
    dq.dequeue();
    cout << "After dequeue: ";
    dq.display();

    cout << "\n========== TESTING DYNAMIC QUEUE (Using List) ==========" << endl;
    QueueUsingList<int> qul;
    qul.enqueue(5);
    qul.enqueue(15);
    qul.enqueue(25);
    cout << "After enqueuing: ";
    qul.display();
    qul.dequeue();
    cout << "After dequeue: ";
    qul.display();

    cout << "\n========== TESTING STATIC STACK ==========" << endl;
    StaticStack<int> ss;
    ss.push(1);
    ss.push(2);
    ss.push(3);
    ss.push(4);
    ss.push(5);
    cout << "After pushing 5 elements: ";
    ss.display();
    ss.push(6); // Should show overflow
    cout << "Top element: " << ss.peek() << endl;
    ss.pop();
    ss.pop();
    cout << "After 2 pops: ";
    ss.display();

    cout << "\n========== TESTING DYNAMIC STACK (Linked List) ==========" << endl;
    DynamicStack<int> ds;
    ds.push(99);
    ds.push(88);
    ds.push(77);
    cout << "After pushing: ";
    ds.display();
    cout << "Top element: " << ds.peek() << endl;
    ds.pop();
    cout << "After pop: ";
    ds.display();

    cout << "\n========== TESTING DYNAMIC STACK (Using List) ==========" << endl;
    StackUsingList<int> sul;
    sul.push(111);
    sul.push(222);
    sul.push(333);
    cout << "After pushing: ";
    sul.display();
    sul.pop();
    cout << "After pop: ";
    sul.display();

    return 0;
}

