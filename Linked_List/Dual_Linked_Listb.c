#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    //---
    struct node *next;
    struct node *prev;
};
struct node *getNewNode(int val){
    // allocate mem for node
    struct node *newNode = (struct node*)malloc(sizeof(struct node));

    // fill node structure
    newNode->data = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    // return this new node
    return newNode;
}

int getLastNodeData(struct node *ptr)
{
    int val = 0;
    struct node *newNode = ptr;
    while(newNode != NULL){
        val = newNode->data;
        //---
        newNode = newNode->next;
    }
    return val;
}
int nodesCount(struct node *ptr)
{
    struct node *newNode = ptr;
    int count = 0;
    while(newNode != NULL){
        ++count;
        //---
        newNode = newNode->next;
    }
    return count;
}
void traverseForward(struct node *n1){
    struct node *newNode = n1;

    while(newNode != NULL){
        printf("%d -> ", newNode->data);
        newNode = newNode->next;
    }
    printf(" NULL");
}

void traverseBackward(struct node *nodePtr){
    struct node *currNode = nodePtr;

    while(currNode != NULL){
        printf("%d -> ", currNode->data);
        currNode = currNode->prev;
    }
    printf(" NULL");
}


struct node *insertAtBeginning(struct node *ptr, int val){
    struct node *newNode = getNewNode(val);
    newNode->next = ptr;

    ptr->prev = newNode;
    return newNode;
}

struct node *getLastNode(struct node *nodePtr){
    if (nodePtr == NULL){   // empty list
        return NULL;
    }

    while (nodePtr->next != NULL){
        nodePtr = nodePtr->next;
    }

    return nodePtr;         // last node
}

struct node *insertAtEnd(struct node *nodePtr, int val){
    struct node *lastNode = getLastNode(nodePtr);
    struct node *newNode = getNewNode(val);
    
    newNode->next = NULL;
    newNode->prev = lastNode;
    lastNode->next = newNode;
    return newNode;
}


void freeMemory(struct node *head)
{
    struct node *temp;

    while (head != NULL){
        temp = head;            // save current node
        head = head->next;      // advance to next node
        free(temp);             // free current node
    }
}



int main(){

    struct node *n1 = getNewNode(10);
    struct node *n2 = getNewNode(20);
    struct node *n3 = getNewNode(30);
    struct node *n4 = getNewNode(40);
    struct node *n5 = getNewNode(50);
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;

    n2->prev = n1;
    n3->prev = n2;
    n4->prev = n3;
    n5->prev = n4;

    // insert before --> b1 = 110, b2 = 120, b3 = 130
    struct node *b1 = insertAtBeginning(n1, 110);
    struct node *b2 = insertAtBeginning(b1, 120);
    struct node *b3 = insertAtBeginning(b2, 130);

    struct node *e1 = insertAtEnd(b3, 210);
    struct node *e2 = insertAtEnd(b3, 220);
    struct node *e3 = insertAtEnd(n4, 230);

    traverseForward(b3);
    printf("\n");
    traverseBackward(e3);

    int totalNodes = nodesCount(n1);
    printf("\nTotal nodes = %d",totalNodes);

    int dataLastNode = getLastNodeData(n1);
    printf("\nLast node val = %d", dataLastNode);

    freeMemory(b3);

    n1 = n2 = n3 = n4 = n5 = b1 = b2 = b3 = e1 = e2 = e3 = NULL;

    return 0;    
}