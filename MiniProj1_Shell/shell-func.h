/*
header file for shell helper functions
*/
#include <stdio.h>
#include <string.h>

#define MAX_ARGS		40 /* 40 arguments max */

void parseInput(char *input_line, char **args);