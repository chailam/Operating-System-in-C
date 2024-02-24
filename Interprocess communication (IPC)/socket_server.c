/*
UNIX Socket Server
name : Loi Chai Lam
ID : 2813 6179
date : 8/10/2017
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define SOCKET "socket"
#define SIZE 1024

int main(void)
{
	char buffer[SIZE];
	int n, serverSocket, clientSocket, len, pid, k, i;
	char character[SIZE] = "\nserver : ";
	char *tmp = NULL;
	char *arg[SIZE];
	struct sockaddr_un addr;
	
	/* Create a new socket */
	if ((serverSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("client : create socket error");
		exit(1);
	}
	
	/* Create the address */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SOCKET);
	
	/* Remove previous socket */
	unlink(addr.sun_path);
	
	/* Naming the socket */
	if (bind(serverSocket, (struct sockaddr*)&addr, SUN_LEN(&addr)) < 0) 
	{
		perror("server : bind error");
		exit(1);
	}
	
	/* Waiting for connections */
	if (listen(serverSocket, 1) < 0) 
	{
		perror("server : listen error");
		exit(1);
	}
	
	/* Accepting connections */
	len = SUN_LEN(&addr); 
	if ((clientSocket = accept(serverSocket, (struct sockaddr *)&addr, &len)) < 0) 
	{
		perror("server : accept error");
		exit(1);
	}
	
	/* Read from the socket and execute the command */
	while ((n = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) 
	{
		write(1, character, 9);
		buffer[n] = '\0'; /**/
		char **argument = malloc(SIZE * sizeof(char*));
		memset(arg, 0, SIZE); /* Reset the memory of arg */
		
		/* Separate the argument using strtok */
		i = 0;
		tmp = strtok(buffer,"\t\n ");
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
	
	/* Close the socket */
	close(clientSocket);
	close(serverSocket);
	exit(0);
}
