/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * 
 * 
 ****/


#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#include <stdbool.h>
#include "list.h"

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();

//used for round robin schedules to determine
//if more task in list pointed at by head have
//cpu burst time remaining
bool more_run(struct node **head);
