/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * First Come First Serve CPU Scheduler
 * 
 * Run processes in the order that they
 * are delivered to the cpu queue
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
	pid++;
	newTask->priority = priority;
	newTask->burst = burst;

	insert_tail(&list, newTask);
}

void schedule() {
	struct node *temp = list;
	double avgTurn = 0.0;
	double avgWait = 0.0;
	int end = 0;
	printf("\nFirst Come First Serve CPU Scheduler\n");
	printf("************************************\n\n");

	while (temp != NULL) {
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
