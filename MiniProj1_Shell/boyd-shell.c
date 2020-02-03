
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
  
void  execute(char **argv, char *file)
{
	pid_t  pid;
	int    status;
	bool bg = isBackground(argv);
	int fd;
	
	if ((pid = fork()) < 0) {     //fork a child process           
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) {          // for the child process
		if (file != NULL){
			fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			dup2(fd, 1);
			close(fd);
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
	if (file_desc = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR) < 0){
		printf("open failed: %s\n", filename);
		exit(1);
	}
	
	return file_desc;
}

void executePipe(char **outputcmd, char **inputcmd)
{
	pid_t  pid1, pid2, wpid;
	int fds[2], status;
	pipe(fds);
	
	if ((pid1 = fork()) < 0) {     //fork a child process           
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid1 == 0) {          // for the child process
		//open up write on this end of the pipe
		dup2(fds[0], 0);  
		
		 
		if (execvp(*inputcmd, inputcmd) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	else if ((pid2 = fork()) < 0) {
		printf("*** ERROR: forking second child process failed\n");
		exit(1);
	}
	else if (pid2 == 0){
		dup2(fds[1], 1);
		
		if (execvp(*outputcmd, outputcmd) < 0) {     // execute the command 
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	else {                                      
		while ((wpid = wait(&status)) > 0);
	    close(fds[0]);
	    close(fds[1]);
	}
}
 
void  main(void)
{
	char line[MAX_LINE];             
	char *argv[MAX_LINE/2 + 1];
	char *inputcmd[MAX_LINE/2 + 1];
	char *outputcmd[MAX_LINE/2 + 1];
	char *trimmed[MAX_LINE/2 +1];
	char lastcmd[MAX_LINE] = "";
	char *source;
	char *dest;
	int fd = 0;
	
	while (1) {                  
		printf("BoydShell -> ");     
		fflush(stdout);
		source = NULL;
		dest = NULL;
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
		
		//need to parse strings returned by strtok to remove whitespace
		//Potential cleanup: parse line before strtok, then remove index
		//with < or >
		if( strchr(line, '>') != NULL || strchr(line, '<') != NULL ){
			source = strtok(line, "<>");
			dest = strtok(NULL, "<>");
			//remove trailing whitespace from source, can't use parse as
			//that breaks things like "ls -al", put into line for 
			//processing into argv
			source[strlen(source) - 1] = '\0';
			
			//remove leading and trailing whitespace after strtok				
			parse(dest, trimmed);
			strcpy(dest, trimmed[0]);
			
			parse(source, argv); 
			execute(argv, dest); 			
		}
		else if( strchr(line, '|') != NULL ){
			parse(line, trimmed);
			int i = 0, j = 0;
			
			while (strcmp(trimmed[i], "|") != 0){
				outputcmd[i] = trimmed[i];
				i++;
			}
			outputcmd[i] = NULL;
			i++;
			while (trimmed[i] != NULL){
				inputcmd[j] = trimmed[i];
				i++;
				j++;
			}
			inputcmd[j] = NULL;
			executePipe(outputcmd, inputcmd);
		}
		else if (strcmp(line, "") != 0){
			//parse input and execute command
			parse(line, argv); 
	
			if (strcmp(argv[0], "exit") == 0)	
				exit(0);  
			execute(argv, dest); 
		}  		
	}
}

                