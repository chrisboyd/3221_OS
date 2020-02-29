/*
 * Course: EECS 3221 Operating Systems
 * Assigment: MiniProject 1
 * Name: Christopher Boyd
 * Student #: 216 869 356
 * 
 * Overview: 
 * Implements a simple Linux shell.
 * 
 * Compile:
 * make
 * 
 * Run:
 * ./boyd-shell
 * 
 * Sample Usage:
 * BoydShell$ ls -al > out.txt 		//redirect ls -al to file out.txt
 * BoydShell$ cat file.txt | less 	//pipe output of cat to input of less
 * BoydShell$ ls -al & 				//run ls -al in the background
 * BoydShell$ sort < in.txt 		//use in.txt as input to sort command
 * 
 * 
 */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h> 

#define MAX_LINE		80  //80 char per line

/*
 * Function: is_background
 * ---------------------------------
 * checks array of input strings for the presence of the '&'
 * character and returns true if it is present and sets the 
 * value of the array index holding '&' to NULL
 */
bool is_background(char **args) {
	bool bg = false;
	while (*args != NULL && !bg) {
		if (**args == '&') {
			bg = true;
			*args = NULL;
		}
		*args++;
	}
	return bg;
}

/*
 * Function: parse
 * ---------------------------------
 * NOTE: this is the code from 
 * www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html
 * 
 * I had my own parse function that but was running major issues with it. 
 * In hindsight it was because I was using strtok. I ended up using strtok to 
 * break up the major bits of text on white space but then had to edit the end of 
 * each token to remove the newlines. Which ended up resulting in code that was
 * virtually the same as this.
 * 
 * Replaces all white space characters in line with \0, then puts all words
 * consisting of one or more letter into array pointed at by args * 
 * 
 */
void parse(char *line, char **args) {
	while (*line != '\0') { /* if not the end of line ....... */
		while (*line == ' ' || *line == '\t' || *line == '\n')
			*line++ = '\0'; /* replace white spaces with 0    */
		*args++ = line; /* save the argument position     */
		while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
			line++; /* skip the argument until ...    */
	}
	*args = '\0'; /* mark the end of argument list  */
}

/*
 * Function: execute
 * ---------------------------------
 * takes in an array of consisting of command followed by 
 * arguments for said command and, optionally, a filename
 * 
 * Forks a child purpose within which said command is executed via
 * execvp.
 * 
 * If a file name is passed in will open a file descriptor to the
 * file for the purpose of reading / writing to / from, respectively.
 * 
 * If the array of args contains the '&' character, the child
 * process will be run in the background. IE the parent process
 * will not wait on the background process to finish before 
 * continueing.c
 */
void execute(char **args, char **file) {
	pid_t pid;
	int status;
	bool bg = is_background(args);
	int fd;

	if ((pid = fork()) < 0) {     //fork a child process           
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	} else if (pid == 0) {          // for the child process
		if (file != NULL) {
			fd = open(*file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			close(fd);
		}
		if (execvp(*args, args) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	} else {                                  // for the parent:     
		if (!bg)
			while (wait(&status) != pid)
				;      // wait for completion 
		fflush (stdout);
	}
}

/*
 * Function: execute_pipe
 * ---------------------------------
 * uses inter-process pipe to output the results from 
 * using execvp of outputcmd as the input to inputcmd execvp
 * 
 */
void execute_pipe(char **outputcmd, char **inputcmd) {
	pid_t pid1, pid2, wpid;
	int fds[2], status;
	pipe(fds);

	if ((pid1 = fork()) < 0) {     //fork a child process           
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	} else if (pid1 == 0) {          // for the child process
		//open up write on this end of the pipe
		dup2(fds[0], 0);

		if (execvp(*inputcmd, inputcmd) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	} else if ((pid2 = fork()) < 0) {
		printf("*** ERROR: forking second child process failed\n");
		exit(1);
	} else if (pid2 == 0) {
		//open read side of pipe
		dup2(fds[1], 1);

		if (execvp(*outputcmd, outputcmd) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	} else {
		while ((wpid = wait(&status)) > 0)
			;
		close(fds[0]);
		close(fds[1]);
	}
}

/*
 * Function: split
 * ---------------------------------
 * Given an input string, line, splits the line into two arrays of 
 * strings based on delimiter. Left being the array of strings that 
 * occur to the left and right the right. 
 * 
 * IE: left delimiter right
 * 
 * Last element of both left and right is marked NULL
 * 
 */
void split(char *line, char **left, char **right, char *delimiter) {
	char *trimmed[MAX_LINE / 2 + 1];
	int i = 0, j = 0;

	parse(line, trimmed);

	while (strcmp(trimmed[i], delimiter) != 0) {
		left[i] = trimmed[i];
		i++;
	}
	left[i] = NULL;
	i++;
	while (trimmed[i] != NULL) {
		right[j] = trimmed[i];
		i++;
		j++;
	}
	right[j] = NULL;
}

/*
 * Function: main
 * ---------------------------------
 * Processes user input and determines which command is
 * entered. Stores last command executed.
 * 
 * Will run until user types 'exit'
 */
void main(void) {
	char line[MAX_LINE];
	char *args[MAX_LINE / 2 + 1];
	char *source[MAX_LINE / 2 + 1];
	char *dest[MAX_LINE / 2 + 1];
	char lastcmd[MAX_LINE] = "";

	while (1) {
		printf("BoydShell$ ");
		fflush (stdout);

		//read input command and remove new line
		fgets(line, MAX_LINE, stdin);
		printf("\n");
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';

		//check for history command
		if (strcmp(line, "!!") == 0) {
			if (strcmp(lastcmd, "") == 0) {
				printf("No commands in history\n");
				strcpy(line, "");
			} else {
				printf("Last command: %s being executed\n\n", lastcmd);
				strcpy(line, lastcmd);
			}
		}
		//keep record of last command
		else
			strcpy(lastcmd, line);

		//process potential input formats
		if (strchr(line, '>') != NULL) {
			split(line, source, dest, ">");
			execute(source, dest);
		} else if (strchr(line, '<') != NULL) {
			split(line, source, dest, "<");
			execute(source, dest);

		} else if (strchr(line, '|') != NULL) {
			split(line, source, dest, "|");
			execute_pipe(source, dest);
		}
		//no special redirect characters in input, 
		//process basic command
		else if (strcmp(line, "") != 0) {
			//parse input and execute command
			parse(line, args);
			if (strcmp(args[0], "exit") == 0)
				exit(0);
			execute(args, NULL);
		}
	}
}

