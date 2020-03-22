/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * Priority CPU Scheduler
 * 
 * Run highest priority processes until completion
 * first. Equal priority processes are run in the order
 * of arrival time.
 * 
 ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *list;
int pid = 1;

//insert newTask into list pointed to by head in 
//sorted position with highest priority first
void add(char *name, int priority, int burst) {
	Task *newTask;
	newTask = malloc(sizeof(Task));
	newTask->name = name;
	newTask->tid = pid;
	newTask->priority = priority;
	newTask->burst = burst;
	pid++;

	insert_priority(&list, newTask);
}

void schedule() {

	struct node *temp = list;
	double avgTurn = 0.0;
	double avgWait = 0.0;
	int end = 0;

	printf("\nPriority CPU Scheduler\n");
	printf("************************************\n\n");
	traverse(list);

	//iterate through the list of processes and run
	//each until competion
	while (temp != NULL) {
		temp->task->startTime = end;
		avgWait += end;
		end = end + temp->task->burst;
		temp->task->endTime = end;
		avgTurn += end;
		run(temp->task, temp->task->burst);
		temp = temp->next;
	}

	printf("\nAverage Turnaround Time: %.2f\n", avgTurn / (pid - 1));
	printf("Average Wait Time: %.2f\n", avgWait / (pid - 1));
	printf("Average Response Time: %.2f\n\n", avgWait / (pid - 1));

}
