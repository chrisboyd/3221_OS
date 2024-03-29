/*
to be populated
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

void parseInput(char *input_line, char **args)
{
	
	int num_args = 1;
	char * token = strtok(input_line, " ");
	
	while (token != NULL){
		*args++ = token;
		if(*args[strlen(*args) -1] == '\n')
			*args[strlen(*args) -1] == '\0';
		num_args++;
		token = strtok(NULL, " ");
	}
	*args = NULL;
	
}


#define MAX_LINE		80  //80 char per line

int main(void)
{
    char *args[MAX_LINE/2 + 1];	//command line (of 80) has max of 40 arguments
    char input_line[MAX_LINE];
	int should_run = 1;
	pid_t pid;
	size_t len = MAX_LINE * sizeof(char);
	int i=0, status;
	char *cmd = "ls";
	char *argv[3];
	argv[0] = "ls";
	argv[1] = "-la";
	argv[2] = NULL;
	
    while (should_run == 1){
        printf("mysh:~$ ");
        fflush(stdout);
		fgets(input_line, MAX_LINE, stdin);
		
		parseInput(input_line, args);
		if (input_line[strlen(input_line) - 1] == '\n')
			input_line[strlen(input_line) - 1] = '\0';
		
		while (args[i] != NULL){
			printf("item: %i :: %s\n", i, args[i]);
			i++;
		}
		
		/*
		if(pid = fork() < 0){
			fprintf(stderr, "Fork Failed");
			exit(1);
		}
		else if (pid == 0){ 
			//execvp(cmd, argv);
			if (execvp(*args, args) < 0){
				printf("Error executing %s\n", *args);
				exit(1);
			}		
		}
		else { 
			while (wait(&status) != pid)  ;
			printf("Child complete\n\n");
		}
		*/
		
		should_run++;
    }

    return 0;
}


/**
  * After reading user input, the steps are:
  * (1) fork a child process
  * (2) the child process will invoke execvp()
  * (3) if command includes &, parent and child will run concurrently
  */