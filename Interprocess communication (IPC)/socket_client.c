/*
UNIX Socket Client
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

#define SOCKET "socket"
#define SIZE 1024

int main(void)
{
	char buffer[SIZE];
	int n, clientSocket, len;
	char character[SIZE] = "\nclient : ";
	struct sockaddr_un addr;
	
	/* Create a socket */
	if ((clientSocket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("client : create socket error");
		exit(1);
	}
	
	/* Create the address */
	memset(&addr, 0, sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SOCKET);
	
	/* Connect to the server */
	if (connect(clientSocket, (struct sockaddr *) &addr, SUN_LEN(&addr)) < 0)  
	{
		perror("client : connect error");
		exit(1);
	}
	
	/* Read the commands.txt file from stdin 
	then print the command and send the data to socket */
	while (fgets (buffer, SIZE, stdin) != NULL)
	{
		n = strlen(buffer);
		buffer[n-1] = '\0'; /**/
		write(1, character, 9); 
		write(1, buffer, n); /* print the command at standard output */
		if (send(clientSocket, buffer, n, 0) < 0) 
		{
			perror("client : send error");
			exit(1);
		}
		sleep(3); /* the client sleep for a while */
	}
	
	/* Close the socket */
	close(clientSocket);
	exit(0);
}
		   
		   
		   
		   