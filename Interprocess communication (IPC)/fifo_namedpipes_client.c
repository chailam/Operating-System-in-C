/*
 Named Pipes (FIFO) Client
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

#define FIFO "fifo"
#define SIZE 1024

int main(void)
{
	int n, fd;
	char buffer[SIZE];
	char character[SIZE] = "\nclient : ";
	
	/* Open the FIFO which was created by the server */
	if ((fd = open(FIFO, O_WRONLY)) < 0) 
	{
		perror("client : open error");
		exit(1);
	}
	
	/* Read the commands.txt file from stdin 
	then print the command and send the data to FIFO */
	while (fgets (buffer, SIZE, stdin) != NULL)
	{
		n = strlen(buffer);
		buffer[n-1] = '\0'; /**/
		write(1, character, 9); 
		write(1, buffer, n); /* print the command at standard output */
		write(fd, buffer, n);
		sleep(3); /* the client sleep for a while */
	}
	
	/* Close the file */
	close(fd);
	exit(0);
}
		