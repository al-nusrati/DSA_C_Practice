#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 8

int stack[MAXSIZE];
int top = -1;

// Check if the stack is full
int isFull() {
    return top == MAXSIZE - 1;
}

// Check if the stack is empty
int isEmpty() {
    return top == -1;
}

// Push an element onto the stack
void push(int value) {
    if (isFull()) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    stack[++top] = value;
    printf("Pushed %d onto the stack\n", value);
}

// Pop an element from the stack
int pop() {
    if (isEmpty()) {
        printf("Stack underflow! Cannot pop\n");
        return -1; // or some error code
    }
    return stack[top--];
}

// Peek the top element
int peek() {
    if (isEmpty()) {
        printf("Stack is empty! Nothing to peek\n");
        return -1; // or some error code
    }
    return stack[top];
}

// Display stack
void display() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return 0;
    }
    printf("\nStack elements: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    push(10);
    push(20);
    push(30);
    display();

    printf("Top element is %d\n", peek());
    printf("Popped element: %d\n", pop());
    display();

    return 0;
}