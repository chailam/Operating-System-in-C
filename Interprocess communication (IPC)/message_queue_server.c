/*
Message Queue Server
name : Loi Chai Lam
ID : 2813 6179
date : 8/10/2017
*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MKEY 34569
#define SIZE 1024

struct msgbuf 
{
	long mtype;
	char mtext[SIZE];
};

int main(void)
{
	key_t key;
	int n, msqid, pid, k, i;
	char character[SIZE] = "\nserver : ";
	char *tmp = NULL;
	char *arg[SIZE];
	struct msgbuf buf;
	
	/* Create a new message queue */ 
	key = MKEY;
	if ((msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0777)) < 0) 
	{
		perror("server : msgget error");
		exit(1);
	}
	
	/* Reset the memory of the struct */
	memset(&buf, 0, sizeof(struct msgbuf));
	
	/* Receive messages from the message queue */
	while ((n = msgrcv(msqid, &buf, SIZE, 0, 0)) > 0) 
	{
		/*  If type is 1, execute the command  */
		if (buf.mtype == 1) 
		{
			write(1, character, 9);
			buf.mtext[n] = '\0'; /**/
			char **argument = malloc(SIZE * sizeof(char*));
			memset(arg, 0, SIZE); /* Reset the memory of arg */
		
			/* Separate the argument using strtok */
			i = 0;
			tmp = strtok(buf.mtext,"\t\n ");
			while (tmp != NULL)
			{
				argument[i] = tmp;
				tmp = strtok(NULL, "\t\n ");
				i++;
			}

			/* Copy the argument */
			for (k=0; k<i ;k++)
			{
				arg[k] = argument[k];
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
		else if (buf.mtype == 2) 
		{
			/* If type is 2, remove the message queue from the system */
			if (msgctl (msqid, IPC_RMID, NULL) < 0) 
			{
				perror("server : msgctl error");
				exit(1);
			}
		}
	}
	exit(0);
}


