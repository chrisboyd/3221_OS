#include "DiskAlgorithms.h"


int fcfs(int inputs[], int outputs[]){
	int mvmt = abs((INIT_HEAD_POSITION - inputs[0]));
	for (int i = 0; i < NUM_REQUESTS; i++){
		if (i > 0)
			mvmt += abs((inputs[i] - inputs[i-1]));
		outputs[i] = inputs[i];
	}
	return mvmt;	
}

int scan(int inputs[], int outputs[]){
	int j = 0, switch_index = 0, mvmt; 
	int *start_sort;	
	//get all elements of input that scan would read going from 
	//INIT_HEAD_POSITION to 0
	for (int i = 0; i < NUM_REQUESTS; i++){
		if (inputs[i] <= INIT_HEAD_POSITION){
			outputs[j] = inputs[i];
			j++;
		}
	}
	
	switch_index = j;
	start_sort = outputs;
	//sort outputs in descending order to show head position
	//moving head from INIT_HEAD_POSITION to 0 
	qsort(start_sort, switch_index, sizeof(int), compare_decreasing);
	
	//scan through requests in increasing order and add to outputs
	for (int i = 0; i < NUM_REQUESTS; i++){
		if (inputs[i] > INIT_HEAD_POSITION){
			outputs[j] = inputs[i];
			j++;
		}
	}
	
	start_sort = &(outputs[switch_index]);
	//sort second set of seeks in ascending order
	//moving head from 0 to end
	qsort(start_sort, (NUM_REQUESTS - switch_index), sizeof(int), compare_increasing);
	
	//determine head movement
	mvmt = abs((INIT_HEAD_POSITION - outputs[0]));
	for (int i= 1; i < NUM_REQUESTS; i++){
		if (i == switch_index - 1)
			mvmt += 2 * (outputs[i]);
		mvmt += abs((outputs[i] - outputs[i-1]));
	}
	return mvmt;
}


int c_scan(int inputs[], int outputs[]){
	
	return 0;
}


int compare_increasing(const void *left, const void *right){
	const int *left_int = (const int *)left; 
	const int *right_int = (const int *)right;
	return *left_int  - *right_int; 
}

int compare_decreasing(const void *left, const void *right){
	const int *left_int = (const int *)left; 
	const int *right_int = (const int *)right;
	return *right_int - *left_int; 
}

