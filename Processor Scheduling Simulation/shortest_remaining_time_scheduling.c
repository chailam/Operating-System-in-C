/*
Shortest Remaining Time Scheduling
author : Loi Chai Lam
ID : 28136179
date : 18/9/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 1024

typedef struct Queue
{
	int * queue; //the address of the circular queue
	int front;  //front pointer
	int rear;  //rear pointer
	int size; //the size of the queue
} QUEUE;

/* Function Prototype */
void initialiseQueue(QUEUE * pQueue);
void appendQueue(QUEUE * pQueue, int value);
void removeQueue(QUEUE * pQueue, int * pValue);
void traverseQueue(QUEUE * pQueue);
int sizeQueue(QUEUE * pQueue);
void smallest_index(QUEUE * pQueue, int * processing, int sizeQ);


/* main */
int main(int argc, char *argv[])
{
	int fd, n, num = 0, indicate = 0, i;
	char buffer[SIZE];
	char **arrival_char = malloc(SIZE*sizeof(char*));
	char **processing_char = malloc(SIZE*sizeof(char*));
	int arrival[SIZE], processing[SIZE],  service[SIZE];
	char *tmp = NULL;
	
	if ((fd = open(argv[1],O_RDONLY)) < 0) //open the file
	{
		perror("Open file error.");
	}
	else
	{
		n = read(fd, buffer, sizeof(buffer)); //read the file
		
		/* separate the file with strtok */
		tmp = strtok(buffer,"\t\n ");
		while (tmp != NULL) 
		{
			if (indicate == 1)
			{
				tmp = strtok(NULL,"\t\n ");
			}
			tmp = strtok(NULL,"\t\n ");
			arrival_char[num] = tmp;
			tmp = strtok(NULL,"\t\n ");
			processing_char[num] = tmp;
			indicate = 1;
			num++;
		}
		
		/* change from string to integer using atoi */
		for (i = 0; i<num-1 ; i++) //num-1 is the number of processes
		{
			arrival[i] = atoi(arrival_char[i]);
			processing[i] = atoi(processing_char[i]);
			service[i] = processing[i];
		}
		close(fd);
	}
	
	/* Shortest Remaining Time (SRT) */
	//(num-1) = number of processes = len(arrival) = len(processing)

	int j = 0, sizeQ, process, k, index, shortest;
	int turnaround[SIZE], waiting[SIZE];
	float averageWaiting, averageTurnaround, throughput, temporary, temporary1, temporary2;
	QUEUE queue; //struct
	initialiseQueue(&queue); // initialise the queue
	i = 0;
	
	while (i < 1024)
	{
		if (j < (num-1))
		{
			if (arrival[j] == i)
			{
				/* if a process arrive, put the process in queue */
				appendQueue(&queue, j);
				j += 1;
			}
		}
		
		if (i > 0)
		{
			if (processing[process] > 0)
			{
				/* after executing the previous process, if the remaining processing time of the previous process > 0, re-queue the process (pre-emptive) */
				appendQueue(&queue, process);
			}
		}
		
		sizeQ = sizeQueue(&queue); //the size of the queue
		if (sizeQ != 0)
		{
			/* if the queue is not empty, find the process with the shortest remaining time, take it out from queue and execute it */
			smallest_index(&queue, processing, sizeQ);
			removeQueue(&queue, &process); //
			processing[process] -= 1;
			printf("%d ",process);
			i += 1; //the time increase by 1
			
			if (processing[process] == 0)
			{
				/* if the process finished all the processing time, calculate the turnaround time */
				turnaround[process] = i - arrival[process];
			}
		}
		else
		{
			/* if there is no process in the queue, break */
			break;
		}	
	}
	
	/* Calculate the waiting time */
	for (k=0; k<(num-1); k++)
	{
		waiting[k] = turnaround[k] - service[k];
		//service is a copy of the processing
	}
	
	
	/* Calculate the average waiting time & average turnaround time & throughput. Output(Print) the information */
	printf("\nP1 = 0 ; P2 = 1 ; P3 = 2 ; P4 = 4.......\n");
	printf("Shortest Remaining Time (SRT)\n");
	printf("\t-----Process-----Arrival Time-----Processing Time-----Waiting Time-----Turnaround Time-----\n");

	temporary = 0;
	temporary1 = 0;
	temporary2 = 0;
	
	/* Calculate the throughput, average waiting time & average turnaround time*/
	for (k=0; k<num-1; k++)
	{
		printf("\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\n",k+1, arrival[k], service[k], waiting[k], turnaround[k]);
		temporary += service[k];
		temporary1 += waiting[k];
		temporary2 += turnaround[k];
	}
	throughput = temporary / (num-1);
	averageWaiting = temporary1 / (num-1);
	averageTurnaround = temporary2 / (num-1);
	
	printf("\nAverage Waiting Time : %.3f \n", averageWaiting);
	printf("Average Turnaround Time : %.3f \n", averageTurnaround);
	printf("Overall Throughput : %.3f seconds per job\n", throughput);
	
	
	free(arrival_char);
	free(processing_char);
	return 0;
}


/* Function */

void initialiseQueue(QUEUE * pQueue)
{
	//initialise the queue
	pQueue->queue = (int*)malloc(sizeof(int) * SIZE);
	pQueue->front = 0;
	pQueue->rear = 0;
	pQueue->size = 0;
}

void appendQueue(QUEUE * pQueue, int value)
{
	//append the queue
	if ((pQueue->rear+1) % SIZE == pQueue->front)
	{
		printf("The queue is full.\n");
	}
	else
	{
		pQueue->queue[pQueue->rear] = value; //append the queue
		pQueue->rear = (pQueue->rear+1) % SIZE; //increase the rear pointer
		pQueue->size += 1; //increase the size
	}	
}

void removeQueue(QUEUE * pQueue, int * pValue)
{
	//remove one item from queue
	if (pQueue->front == pQueue->rear)
	{
		printf("The queue is empty.\n");
	}
	else
	{
		*pValue = pQueue->queue[pQueue->front]; //take the item out from queue
		pQueue->front = (pQueue->front+1) % SIZE; //increase the front pointer
		pQueue->size -= 1; //decrease the size
	}				
}
	
void traverseQueue(QUEUE * pQueue)
{
	//print the queue
	int i = pQueue->front;
	printf("Queue : ");
	while (i != pQueue->rear)
	{
		printf("%d ", pQueue->queue[i]);
		i = (i+1) % SIZE;
	}
	printf("\n");
}

int sizeQueue(QUEUE * pQueue)
{
	//return the size of the queue
	return pQueue->size;
}

void smallest_index(QUEUE * pQueue, int * processing, int sizeQ)
{
	//find the index in the queue of the smallest element in processing array, then change the position between pointer front and index
	int smallest, index=pQueue->front, i, tmp;
	i = pQueue->front;
	smallest = processing[pQueue->queue[i]];
	while (i != pQueue->rear)
	{
		if (processing[pQueue->queue[i]] < smallest)
		{
			smallest = processing[pQueue->queue[i]];
			index = i;
		}
		i = (i + 1) % SIZE;
	}
	tmp = pQueue->queue[index];
	pQueue->queue[index] = pQueue->queue[pQueue->front];
	pQueue->queue[pQueue->front] = tmp;
}





