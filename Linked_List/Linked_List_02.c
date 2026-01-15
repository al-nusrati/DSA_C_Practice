#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

    // declare nodes
    struct node *head = NULL;
    struct node *second = NULL;
    struct node *third = NULL;


void traverse(struct node *head)
{
    struct node *temp = head;

    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
}

void cleanup(){
    free(head);
    free(second);
    free(third);
}

int main(){

    // create nodes
    head = (struct node*)malloc(sizeof(struct node));
    second = (struct node*)malloc(sizeof(struct node));
    third = (struct node*)malloc(sizeof(struct node));

    head->data = 10;
    second->data = 20;
    third->data = 30;

    head->next = NULL;
    head->next = second;
    second->next = third;


    traverse(head);
    cleanUP();

    return 0;
}