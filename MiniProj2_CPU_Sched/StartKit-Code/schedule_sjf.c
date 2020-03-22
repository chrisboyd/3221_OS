/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * Shortest Job First CPU Scheduling
 * 
 * All jobs arrive at the same time, the remaining job with 
 * the shortest CPU Burst time is run until completion.
 * This continues until all processes have been run.
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

// add a task to the list 
void add(char *name, int priority, int burst) {
	Task *newTask;
	newTask = malloc(sizeof(Task));
	newTask->name = name;
	newTask->tid = pid;
	newTask->priority = priority;
	newTask->burst = burst;
	pid++;

	insert_shortest(&list, newTask);
}

//run each process in list until completion,
//in order of increasing CPU Burst time
void schedule() {
	struct node *temp = list;
	double avgTurn = 0.0;
	double avgWait = 0.0;
	int end = 0;

	printf("\nShortest Job First CPU Scheduler\n");
	printf("************************************\n\n");

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
