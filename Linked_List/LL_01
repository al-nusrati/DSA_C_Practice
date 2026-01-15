//-----------------------
// add all nodes manually
//-----------------------

#include <stdio.h>
#include <stdlib.h>

// Standard Node Structure
struct Node
{
    int data;
    struct Node *next;
};

void practice1();

int main()
{
    printf("Linked List Practice\n");
    practice1();
    return 0;
}

void practice1()
{
    //--------------- Add Three Nodes Manullay ---------------

    // Manually create three nodes
    struct Node *head = NULL;
    struct Node *second = NULL;
    struct Node *third = NULL;

    // Allocate memory for nodes
    head   = (struct Node *)malloc(sizeof(struct Node));
    second = (struct Node *)malloc(sizeof(struct Node));
    third  = (struct Node *)malloc(sizeof(struct Node));

    // Assign data
    head->data = 10;
    second->data = 20;
    third->data = 30;

    // Link nodes (Singly Linked List)
    head->next = second;
    second->next = third;
    third->next = NULL;

    // Traverse and print
    struct Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


/*
gcc -Wall -Wextra practice.c -o practice
Explanation of flags:
-Wall → enable all warnings (catch mistakes)
-Wextra → enable extra warnings (more checks)
practice.c → your C file
-o practice → output executable named practice
*/