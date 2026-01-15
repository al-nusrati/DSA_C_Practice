#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

    // declare nodes
    struct node *head = NULL;
    struct node *one = NULL;
    struct node *two = NULL;

void display(struct node *head)
{
    printf("Size of Node: %d\n", sizeof(struct node));
    printf("Data: %d\n", head->data);
    printf("1st Node: %d\n", one->data);
    printf("2nd Node: %d\n", two->data);
}

int main(){
    // create nodes
    head = (struct node*)malloc(sizeof(struct node));
    one = (struct node*)malloc(sizeof(struct node));
    two = (struct node*)malloc(sizeof(struct node));

    head->data = 10;
    head->next = NULL;

    one->data = 20;
    one->next = NULL;

    two->data = 30;
    two->next = NULL;


    display(head);

    free(head);
    free(one);
    free(two);

    return 0;
}