/*
Message Queue Client
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
	int n, msqid;
	char character[SIZE] = "\nclient : ";
	struct msgbuf buf;
	
	/* Get the message queue which was created by the server */
	key = MKEY;
	if ((msqid = msgget(key, 0777)) < 0) 
	{
		perror("client : msgget error");
		exit(1);
	}
	
	/* Reset the memory of the struct */
	memset(&buf, 0, sizeof(struct msgbuf));
	
	/* Read the commands.txt file from stdin 
	then print the command and send a message of type 1 to message queue */
	while (fgets (buf.mtext, SIZE, stdin) != NULL)
	{
		n = strlen(buf.mtext);
		buf.mtext[n-1] = '\0'; /**/
		buf.mtype = 1;
		write(1, character, 9); 
		write(1, buf.mtext, n); /* print the command at standard output */
		if (msgsnd(msqid, &buf, n, 0) < 0) /* Send the message */
		{
			perror("client : msgsnd error");
			exit(1);
		}		
		sleep(3); /* the client sleep for a while */
	}

	
	/* Send a message of type 2 to message queue to inform the server that the end of the command list has been reached */
	buf.mtype = 2;
	memset(buf.mtext, 0, SIZE);
	
	if (msgsnd(msqid, &buf, SIZE, 0) < 0) 
	{
		perror("client : msgsnd error");
		exit(1);
	}
	
	exit(0);
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	