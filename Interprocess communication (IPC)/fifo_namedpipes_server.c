/*
 Named Pipes (FIFO) Server
name : Loi Chai Lam
ID : 2813 6179
date : 8/10/2017
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define FIFO "fifo"
#define SIZE 1024

int main(void)
{
	int n, fd, i, pid, k;
	char buffer[SIZE];
	char character[SIZE] = "\nserver : ";
	char *tmp = NULL;
	char *arg[SIZE];

	/* Remove previous FIFO */
	unlink(FIFO);
	
	/* Create a FIFO */
	if (mkfifo(FIFO, 0777) < 0) 
	{
		perror("server: mkfifo error");
		exit(1);
	}  
	
	/* Open the FIFO for reading */
	if ((fd = open(FIFO, O_RDONLY)) < 0) 
	{
		perror("server : open error");
		exit(1);
	}

	/* Read from FIFO and execute the command */
	while ((n = read(fd, buffer, sizeof(buffer))) > 0) 
	{
		char **argument = malloc(SIZE * sizeof(char*));
		memset(arg, 0, SIZE); /* Reset the memory of arg */
		write(1, character, 9); 
		//printf("n.server: %d\n",n);
		buffer[n] = '\0'; /**/
		/* Separate the argument using strtok */
		i = 0;
		tmp = strtok(buffer,"\t\n ");
		while (tmp != NULL)
		{
			argument[i] = tmp;
			//printf("tmp: %s\n",tmp);
			i++;
			tmp = strtok(NULL, "\t\n ");
		}
		//printf("i.server: %d\n",i);
		/* Copy the argument */
		for (k=0; k<i ;k++)
		{
			arg[k] = argument[k];
			//printf("arg:%s\n",arg[k]);
		}

		
		/* Fork and execute, pid=0 is child, pid >0 is parent */
		pid = fork();
		if (pid < 0)
		{
			perror("fork error: child process could not be created");
		}
		else if (pid == 0)
		{
			if (execvp(arg[0],arg) < 0)
			{
				perror("execvp error");
			}
		}
		else
		{
			waitpid(pid,NULL,0);
		}
		
		/* Free the argument */
		free(argument);
	}
	
	/* Close the file */
	close(fd);
	exit(0);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	