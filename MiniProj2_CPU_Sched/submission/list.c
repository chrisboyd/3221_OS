/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * 
 * 
 ****/


/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"


//insert newTask into list pointed to by head in 
//sorted position with highest priority first
void insert_priority(struct node **head, Task *newTask){
	struct node *newNode = malloc(sizeof(struct node));
	struct node *temp = *head;
	
    newNode->task = newTask;
	if (*head == NULL || (*head)->task->priority <= newTask->priority){
		newNode->next = *head;
		*head = newNode;
	}
	else{
		
		while(temp->next != NULL && temp->next->task->priority > newTask->priority)
			temp = temp->next;
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

//insert newTask into list pointed to by head in 
//sorted position with shortest burst time first
void insert_shortest(struct node **head, Task *newTask){
	struct node *newNode = malloc(sizeof(struct node));
	struct node *temp = *head;
	
    newNode->task = newTask;
	if (*head == NULL || (*head)->task->burst >= newTask->burst){
		newNode->next = *head;
		*head = newNode;
	}
	else{
		
		while(temp->next != NULL && temp->next->task->burst < newTask->burst)
			temp = temp->next;
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

// add a new task to front of the list of tasks
void insert_head(struct node **head, Task *newTask) {
    // add the new task to the list 
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

//add new task to the end of the list
void insert_tail(struct node **tail, Task *newTask) {
	struct node *newNode = malloc(sizeof(struct node));
    struct node *temp = *tail;
	newNode->task = newTask;
    newNode->next = NULL;
	
    //list has no elements, put newNode at the front
	if (temp == NULL){
		*tail = newNode;
	}
	else{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
	
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
