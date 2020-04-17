#include "DiskAlgorithms.h"

int main(int argc, char *argv[]){
	FILE *disk_input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	int cylinder = 0, i = 0, fcfs_mvmt, scan_mvmt, c_scan_mvmt;
	int requests[NUM_REQUESTS], fcfs_results[NUM_REQUESTS], 
		scan_results[NUM_REQUESTS], c_scan_results[NUM_REQUESTS];
	
	if (disk_input == NULL){
		printf("Could not open: input.txt\n");
		return -1;
	}
	if (output == NULL){
		printf("Could not open: output.txt\n");
		return -1;
	}
	
	while (i < NUM_REQUESTS){
		if (fscanf(disk_input, "%d", &cylinder) != EOF){
			requests[i] = cylinder;
			i++;
		}
		else{
			printf("Input file is wrong format, less than %d addresses\n", NUM_REQUESTS);
			return -1;
		}
	}
	//Perform FCFS seek on request addresses
	fcfs_mvmt = fcfs(requests, fcfs_results);
	fprintf(output, "\nFCFS Algorithm\n");
	fprintf(output, "Initial head position = %d\n", INIT_HEAD_POSITION);
	fprintf(output, "Seek Sequence is:\n");
	for (int j = 0; j < NUM_REQUESTS; j++){
		fprintf(output, "%d\n", fcfs_results[j]);
	}
	fprintf(output, "Total head movement for FCFS = %d\n", fcfs_mvmt);
	
	//Perform SCAN seek on request addresses
	scan_mvmt = scan(requests, scan_results);
	fprintf(output, "\nSCAN Algorithm\n");
	fprintf(output, "Initial head position = %d\n", INIT_HEAD_POSITION);
	fprintf(output, "Seek Sequence is:\n");
	for (int j = 0; j < NUM_REQUESTS; j++){
		fprintf(output, "%d\n", scan_results[j]);
	}
	fprintf(output, "Total head movement for SCAN = %d\n", scan_mvmt);
	
	//perform C-SCAN seek on request adresses
	c_scan_mvmt = c_scan(requests, c_scan_results);
}