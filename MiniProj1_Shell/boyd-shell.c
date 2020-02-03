/* ----------------------------------------------------------------- */
/* PROGRAM  shell.c                                                  */
/*    This program reads in an input line, parses the input line     */
/* into tokens, and use execvp() to execute the command.             */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h> 


#define MAX_LINE		80  //80 char per line

bool isBackground(char **argv)
{
	bool bg = false;
	while (*argv != NULL && !bg){
		if (**argv == '&'){
			bg = true;
			*argv = NULL;
		} 
		*argv++;
	}
	return bg;
}
/* ----------------------------------------------------------------- */
/* FUNCTION  parse:                                                  */
/*    This function takes an input line and parse it into tokens.    */
/* It first replaces all white spaces with zeros until it hits a     */
/* non-white space character which indicates the beginning of an     */
/* argument.  It saves the address to argv[], and then skips all     */
/* non-white spaces which constitute the argument.                   */
/* ----------------------------------------------------------------- */

void  parse(char *line, char **argv)
{
	while (*line != '\0') {       /* if not the end of line ....... */ 
		while (*line == ' ' || *line == '\t' || *line == '\n')
			*line++ = '\0';     /* replace white spaces with 0    */
		*argv++ = line;          /* save the argument position     */
		while (*line != '\0' && *line != ' ' && 
			*line != '\t' && *line != '\n') 
				line++;             /* skip the argument until ...    */
	}
	*argv = '\0';                 /* mark the end of argument list  */
}

/* ----------------------------------------------------------------- */
/* FUNCTION execute:                                                 */
/*    This function receives a commend line argument list with the   */
/* first one being a file name followed by its arguments.  Then,     */
/* this function forks a child process to execute the command using  */
/* system call execvp().                                             */
/* ----------------------------------------------------------------- */
     
void  execute(char **argv, int fd)
{
	pid_t  pid;
	int    status, i = 0;
	bool bg = isBackground(argv);
	/*
	while(argv[i] != NULL){
		printf("Argv %i: %s\n", i,argv[i]);
		i++;
	}
	*/
	
	if ((pid = fork()) < 0) {     //fork a child process           
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          // for the child process
		if (fd > 0){
			dup2(fd, STDOUT_FILENO);
			printf("opened file \n");
		}		         
		if (execvp(*argv, argv) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	else {                                  // for the parent:     
		if (!bg)
			while (wait(&status) != pid);      // wait for completion 
		fflush(stdout);
	}
}

int getFD(char *filename)
{
	int file_desc;
	//filename,O_RDWR | O_APPEND | O_CREAT, 0666
	if (file_desc = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR) < 0){
		printf("open failed: %s\n", filename);
		exit(1);
	}
	else
		printf("open worked: %s\n", filename);
	return file_desc;
}


/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */
    
void  main(void)
{
	char line[MAX_LINE];             
	char *argv[MAX_LINE/2 + 1];                
	char lastcmd[MAX_LINE] = "";
	//char *split_redirect;
	char *source;
	char *dest;
	int fd = 0;
	
	while (1) {                  
		printf("BoydShell -> ");     
		fflush(stdout);
		
		//read command and remove new line
		fgets(line, MAX_LINE, stdin);
		printf("\n");
		if (line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		
		
		if (strcmp(line, "!!") == 0){
			if (strcmp(lastcmd, "") == 0){
				printf("No commands in history\n");
				strcpy(line, "");
			}
			else{
				printf("Last command: %s being executed\n\n", lastcmd);
				strcpy(line, lastcmd);
			}
		}
		else
			strcpy(lastcmd, line);
		
		//check for > or <
		if (strchr(line,'<') != NULL){
			//works for argv
			dest = strtok(line, "<");
			source = strtok(NULL, "<");
			fd = getFD(dest);
			strcpy(line, source);
		}
		else if( strchr(line, '>') != NULL){
			//add extra arg for argv, insert \O into source?
			source = strtok(line, ">");
			dest = strtok(NULL, ">");
			source[strlen(source) - 1] = '\0';
			fd = getFD(dest);
			strcpy(line, source);
		}	
		
		if (strcmp(line, "") != 0){
			//parse input and execute command
			parse(line, argv);    
			if (strcmp(argv[0], "exit") == 0)	
				exit(0);  
			execute(argv, fd); 
			if (fd > 0)
				close(fd);
		}  
		
	}
}

                