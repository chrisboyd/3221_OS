#include <stdlib.h>
#include <stdio.h>

static int INIT_HEAD_POSITION = 33;
static int NUM_REQUESTS = 25;

int fcfs(int inputs[], int outputs[]);
int scan(int inputs[], int outputs[]);
int c_scan(int inputs[], int outputs[]);
int compare_increasing(const void *left, const void *right);
int compare_decreasing(const void *left, const void *right);

