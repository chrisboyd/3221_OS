/**
 * 
 * Implements the FCFS, SCAN and C-SCAN
 * disk scheduling algorithms as defined
 * in OSC 11.2.1, 11.2.2 and 11.2.3
 * 
 * Chris Boyd
 * 216 869 356
 * York EECS 3221 Winter 2020
 */

#include "DiskAlgorithms.h"

/*
 * Perform cylinder requests in the order they arrive
 * 
 * inputs[] is the list of requests to process 
 * 
 * outputs[] contains list of requests in the order
 * they were processed by SCAN
 * 
 * Returns the number of head movements to process
 * inputs[] 
 * 
 */
int fcfs(int inputs[], int outputs[]) {
	int mvmt = abs((INIT_HEAD_POSITION - inputs[0]));
	for (int i = 0; i < NUM_REQUESTS; i++) {
		if (i > 0)
			mvmt += abs((inputs[i] - inputs[i - 1]));
		outputs[i] = inputs[i];
	}
	return mvmt;
}

/*
 * Starting with INIT_HEAD_POSITION, scan towards
 * cylinder 0, processing requests in descending
 * numerical order, then switch scan direction and
 * process requests in ascending numerical order.
 * 
 * All requests are in inputs[] prior to beginning
 * sequence. Does not support a new request queue
 * 
 * inputs[] is the list of requests to process 
 * 
 * outputs[] contains list of requests in the order
 * they were processed by SCAN
 * 
 * Returns the number of head movements to process
 * inputs[] 
 * 
 */
int scan(int inputs[], int outputs[]) {
	int j = 0, switch_index = 0, mvmt = 0;
	int *start_sort;
	//get all elements of input that scan would read going from 
	//INIT_HEAD_POSITION to 0
	for (int i = 0; i < NUM_REQUESTS; i++) {
		if (inputs[i] <= INIT_HEAD_POSITION) {
			outputs[j] = inputs[i];
			j++;
		}
	}

	switch_index = j;
	start_sort = outputs;
	//sort outputs in descending order to show head position
	//moving head from INIT_HEAD_POSITION to 0 
	qsort(start_sort, switch_index, sizeof(int), compare_decreasing);

	//get all elements of input that scan would read going from
	//INIT_HEAD_POSITION to 99
	for (int i = 0; i < NUM_REQUESTS; i++) {
		if (inputs[i] > INIT_HEAD_POSITION) {
			outputs[j] = inputs[i];
			j++;
		}
	}

	start_sort = &(outputs[switch_index]);
	//sort second set of seeks in ascending order
	//moving head from 0 to 99
	qsort(start_sort, (NUM_REQUESTS - switch_index), sizeof(int),
			compare_increasing);

	//all requests cylinders are greater than INIT_HEAD_POSITION
	//so head has to go to 0 and back with no requests being processed
	if (switch_index == 0) {
		mvmt += (2 * INIT_HEAD_POSITION);
	}
	//determine head movement from INIT_HEAD_POSITION to first request
	mvmt += abs((INIT_HEAD_POSITION - outputs[0]));
	for (int i = 1; i < NUM_REQUESTS; i++) {
		//get movement from lowest cylinder request to 0 and back
		if (i == switch_index - 1) {
			mvmt += 2 * (outputs[i]);
		}
		mvmt += abs((outputs[i] - outputs[i - 1]));
	}
	return mvmt;
}

/*
 * Starting with INIT_HEAD_POSITION, scan towards
 * cylinder 99, processing requests in ascending
 * numerical order, then move head to 0, and continue
 * processing requests in ascending numerical order until
 * complete.
 * 
 * Note: if the last request is at cylinder 99 the head will 
 * immediately move to cylinder 0 (as defined in OSC 11.2.3)
 * 
 * outputs[] contains list of requests in the order
 * they were processed
 * 
 * Returns the number of head movements to process
 * inputs[]
 * 
 */
int c_scan(int inputs[], int outputs[]) {
	int j = 0, switch_index = 0, mvmt = 0;
	int *start_sort;
	//start head at INIT_HEAD_POSITION and service requests
	//until end of disk, 99
	for (int i = 0; i < NUM_REQUESTS; i++) {
		if (inputs[i] >= INIT_HEAD_POSITION) {
			outputs[j] = inputs[i];
			j++;
		}
	}
	switch_index = j;
	start_sort = outputs;
	//sort outputs in ascending order to show head position
	//moving head from INIT_HEAD_POSITION to 0 
	qsort(start_sort, switch_index, sizeof(int), compare_increasing);

	//move head to 0 position and scan, reading requests
	//with index < INIT_HEAD_POSITION
	for (int i = 0; i < NUM_REQUESTS; i++) {
		if (inputs[i] < INIT_HEAD_POSITION) {
			outputs[j] = inputs[i];
			j++;
		}
	}
	start_sort = &(outputs[switch_index]);
	//sort second set of seeks in ascending order
	//moving head from 0 to end
	qsort(start_sort, (NUM_REQUESTS - switch_index), sizeof(int),
			compare_increasing);

	//no requests processed from INIT_HEAD_POSITION to 99
	//add movement from INIT_HEAD_POSITION to 99 and back to 
	//highest cylinder request in inputs
	if (switch_index == 0) {
		mvmt += (99 - INIT_HEAD_POSITION) + 99;
		mvmt += outputs[0];

	}
	//some requests from INIT_HEAD_POSITION to 99 were processed
	else {
		mvmt += abs((INIT_HEAD_POSITION - outputs[0]));
		//special case where all requests are to the right of the init head
		//position and last request is at the end of the cylinder, head
		//immediately moves to start of the cylinder
		if (switch_index == 25 && outputs[NUM_REQUESTS - 1] == 99)
			mvmt += 99;

	}
	//determine head movement for all requests processed
	for (int i = 1; i < NUM_REQUESTS; i++) {
		if (i == switch_index - 1 && switch_index != NUM_REQUESTS)
			mvmt += ((outputs[i] - outputs[i - 1])) + (99 - outputs[i]);
		else if (i == switch_index)
			mvmt += 99 + outputs[i];
		else
			mvmt += abs((outputs[i] - outputs[i - 1]));
	}
	return mvmt;
}

/*
 * Used for c library qsort, sort integers in
 * ascending order
 * 
 */
int compare_increasing(const void *left, const void *right) {
	const int *left_int = (const int*) left;
	const int *right_int = (const int*) right;
	return *left_int - *right_int;
}

/*
 * used for c library qsort, sort integers in
 * descending order
 * 
 */
int compare_decreasing(const void *left, const void *right) {
	const int *left_int = (const int*) left;
	const int *right_int = (const int*) right;
	return *right_int - *left_int;
}

