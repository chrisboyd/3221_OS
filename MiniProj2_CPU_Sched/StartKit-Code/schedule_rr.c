/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * Round Robin CPU Scheduler
 * 
 * Runs each process in the queue for time
 * equal to QUANTUM, as defined in cpu.h
 * 
 * Note: if a process has less than QUANTUM 
 * remaining the processor will still
 * allocate the full QUANTUM time.
 * 
 ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "schedulers.h"
#include "task.h"
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
	newTask->preEmpt = 0;
	insert_tail(&list, newTask);
}

void schedule() {
	struct node *temp = list;
	double totalTurn = 0.0;
	double totalWait = 0.0;
	double totalResp = 0.0;
	int totalTime = 0;
	printf("\nRound Robin CPU Scheduler\n");
	printf("************************************\n\n");

	//while there are processes with more CPU Burst time
	while (more_run(&temp)) {
		//iterate through list of processes
		while (temp != NULL) {
			//current process has less than QUANTUM time left
			if (temp->task->burst > 0 && temp->task->burst <= QUANTUM) {
				totalTime += QUANTUM;
				run(temp->task, QUANTUM);
				temp->task->burst = 0;
				temp->task->endTime = totalTime;
				totalTurn += totalTime;
			}
			//current process can run for full QUANTUM
			else if (temp->task->burst > 0) {
				temp->task->preEmpt = temp->task->preEmpt + 1;
				totalTime += QUANTUM;
				run(temp->task, QUANTUM);
				temp->task->burst = temp->task->burst - QUANTUM;
			}
			temp = temp->next;
		}
		//go back to the start of the list to check for remaining
		//burst time
		temp = list;
	}
	//calculate the total amount of time it took to get a 
	//response from each process
	for (int i = 0; i < pid - 1; i++)
		totalResp += (QUANTUM * i);

	temp = list;
	//find total time each process waited by summing all of the end times for 
	//each process and subtracting how many times each process was pre-empted (ie was 
	//running during the total time.
	while (temp != NULL) {
		totalWait += (temp->task->endTime - QUANTUM)
						- (temp->task->preEmpt * QUANTUM);
		temp = temp->next;
	}
	printf("\nAverage Turnaround Time: %.2f\n", totalTurn / (pid - 1));
	printf("Average Wait Time: %.2f\n", totalWait / (pid - 1));
	printf("Average Response Time: %.2f\n\n", totalResp / (pid - 1));

}

//iterate through list starting at head,
//if any processes have more burst time
//return true
bool more_run(struct node **head) {
	bool more = false;
	struct node *temp = *head;

	while (temp != NULL) {
		if (temp->task->burst > 0)
			more = true;
		temp = temp->next;
	}
	return more;
}
