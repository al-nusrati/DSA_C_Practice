#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 8

int queue[MAXSIZE];
int front = -1;
int rear = -1;

// Check if the queue is full
int isFull() {
    return (front == MAXSIZE - 1);
}

// Check if the queue is empty
int isEmpty() {
    return (front == -1 || front > rear); 
}

// enqueue an element onto the queue
void enqueue(int value) {
    if (isFull()) {
        printf("Queue overflow! Cannot enqueue %d\n", value);
        return;
    }

    if (front == -1)
        front = 0;

    queue[++rear] = value;
    printf("Enqueued %d onto the queue\n", value);
}

// dequeue an element from the queue
int dequeue() {
    if (isEmpty()) {
        printf("Queue empty! Cannot dequeue\n");
        return -1;
    }

    return queue[front++];
}

// Peek the front element
int peek() {
    if (isEmpty()) {
        printf("Queue is empty! Nothing to peek\n");
        return -1;
    }
    return queue[front];
}

// Display queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("\nQueue elements: ");
    for (int i = 0; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();

    printf("Front element is %d\n", peek());
    printf("Dequeued element: %d\n", dequeue());
    display();

    return 0;
}