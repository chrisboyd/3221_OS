/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * 
 * 
 ****/

/**
 * list data structure containing the tasks in the system
 */
#ifndef LIST_H
#define LIST_H

#include "task.h"

struct node {
    Task *task;
    struct node *next;
};

// insert and delete operations.

//insert newTask at head of list pointed to by head
void insert_head(struct node **head, Task *task);

//insert newTask at tail of list pointed to by head
void insert_tail(struct node **head, Task *newTask);

//insert newTask into list pointed to by head in 
//sorted position with shortest burst time first
void insert_shortest(struct node **head, Task *newTask);

//insert newTask into list pointed to by head in 
//sorted position with highest priority first
void insert_priority(struct node **head, Task *newTask);

//delete a task matching task from list pointed
//to by head
void delete(struct node **head, Task *task);

//traverse the list head and print
//name, priority and burst of each
void traverse(struct node *head);

#endif
