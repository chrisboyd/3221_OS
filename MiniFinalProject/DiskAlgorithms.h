/****
 * Functions for simulating the head movement of a 
 * disk
 * 
 * NOTE: head position is between [0,99]
 * 
 * Chris Boyd
 * 216 869 356
 * York EECS 3221 Winter 2020
 */

#include <stdlib.h>
#include <stdio.h>

//initial head position
static int INIT_HEAD_POSITION = 33;
//number of cylinder requests to process
static int NUM_REQUESTS = 25;

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
int fcfs(int inputs[], int outputs[]);

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
int scan(int inputs[], int outputs[]);

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
int c_scan(int inputs[], int outputs[]);

/*
 * Used for c library qsort, sort integers in
 * ascending order
 * 
 */
int compare_increasing(const void *left, const void *right);

/*
 * used for c library qsort, sort integers in
 * descending order
 * 
 */
int compare_decreasing(const void *left, const void *right);

