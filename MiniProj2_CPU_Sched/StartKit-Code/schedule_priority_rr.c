/****
 * Name: Christopher Boyd
 * St #: 216 869 356
 * York: chris360
 * 
 * Priority CPU Scheduler with Round Robing
 * 
 * Run highest priority processes until completion
 * first. Equal priority processes are run with a round
 * robin schedule with each process getting QUANTUM cpu time,
 * as defined in cpu.h
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
	newTask->preEmpt = 0;
	pid++;

	insert_priority(&list, newTask);
}

void schedule() {
	struct node *temp = list;
	struct node *rr;
	struct node *itr;
	double totalTurn = 0.0;
	double totalWait = 0.0;
	double totalResp = 0.0;
	int samePri = 0;
	int totalTime = 0;

	printf("\nPriority Round Robin CPU Scheduler\n");
	printf("************************************\n\n");

	//while there are still processes to run, iterate
	//through list
	while (temp != NULL) {
		//find all processes that match the priority of temp->task
		//and add to the rr list for round robin scheduling
		itr = temp;
		insert_head(&rr, temp->task);
		while (itr->next != NULL
				&& itr->task->priority == itr->next->task->priority) {
			insert_head(&rr, itr->next->task);
			itr = itr->next;
			temp = itr;
			samePri++;
		}
		//process rr list if more than one element
		if (samePri > 0) {
			itr = rr;
			//while there is at least one process in rr with remaining
			//cpu burst time, run
			while (more_run(&itr)) {
				while (itr != NULL) {
					if (itr->task->burst > 0 && itr->task->burst <= QUANTUM) {
						totalTime += QUANTUM;
						run(itr->task, QUANTUM);
						itr->task->burst = 0;
						itr->task->endTime = totalTime;
						totalTurn += totalTime;
					} else if (itr->task->burst > 0) {
						itr->task->preEmpt = itr->task->preEmpt + 1;
						totalTime += QUANTUM;
						run(itr->task, QUANTUM);
						itr->task->burst = itr->task->burst - QUANTUM;
					}
					itr = itr->next;
				}
				itr = rr;
			}
			//calculate response times for round robin of 
			//equal priorities
			for (int i = 0; i <= samePri; i++)
				totalResp += (QUANTUM * i);
			//calculate how much time each process spent waiting in the 
			//round robin queue
			itr = rr;
			while (itr != NULL) {
				totalWait += (itr->task->endTime - QUANTUM)
						- (itr->task->preEmpt * QUANTUM);
				itr = itr->next;
			}
		}
		//no matching priorities for temp->task->priority, process
		//whole job
		else {
			totalWait += totalTime;
			totalResp += totalTime;
			run(temp->task, temp->task->burst);
			totalTime += temp->task->burst;
			totalTurn += totalTime;
		}
		//reset rr list and number of elements with the same priority
		rr = NULL;
		samePri = 0;
		temp = temp->next;
	}

	printf("\nAverage Turnaround Time: %.2f\n", totalTurn / (pid - 1));
	printf("Average Wait Time: %.2f\n", totalWait / (pid - 1));
	printf("Average Response Time: %.2f\n\n", totalResp / (pid - 1));
}

//used for round robin schedules to determine
//if more task in list pointed at by head have
//cpu burst time remaining
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
