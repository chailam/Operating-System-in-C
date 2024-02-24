# Operating-System-in-C
Operating System Unit to Code in C which includes Basic Command Line Interface(CLI), Inter Process Communication (IPC) and Processor Scheduling Simulation in C.

## A. Basic Command Line Interface (CLI) Implementation in C

### Overview
The objective of this task is to implement a reduced version of a Command Line Interface (CLI) program, resembling the functionality of a Unix/Linux shell. The program will be developed using the C programming language and will incorporate essential Unix commands.

The basic CLI program capable of performing the following functions using specific commands has been implemented:

| Command      | Description                                                                                                           |
|--------------|-----------------------------------------------------------------------------------------------------------------------|
| clear        | Clear the output screen.                                                                                              |
| cd <directory> | Change the default directory to <directory>. If <directory> does not exist, an appropriate error message should be displayed. If the argument is not present, change the current directory to the directory given by the HOME environment variable in Unix. This command should also update the PWD variable. |
| ls <directory> | List the contents of the given directory named <directory>.                                                           |
| echo <statement> | Display <statement> on the output screen followed by a newline character '\n'. A statement is a sequence of characters begins with a double quote (") and terminated with the next double quote ("). |
| help         | Display the user manual using the command more or less in Unix.                                                      |
| quit         | Terminate the CLI program and exit.                                                                                   |
| create <file> | Create a new file with the name <file>.                                                                              |
| copy <old> <new> | Copy the contents of an existing file named <old> to a new file named <new>. If <old> does not exist, an appropriate error message should be displayed. |
| search <pattern> <file> | Display the number of occurrences of a sequence of characters <pattern> in the file named <file>. If <file> does not exist, an appropriate error message should be displayed. |
| run <program> | Execute an executable program named <program>.                                                                        |
| halt <program> | Stop executing the program named <program>.                                                                           |

<br>

----

<br>

## B. Interprocess communication (IPC) Implementation in C

### Overview
This task focuses on implementing a clientserver model in Unix utilizing three distinct mechanisms Named Pipes (FIFO), Message Queues, and Unix Sockets. Each mechanism requires the implementation of both server and client programs to facilitate communication.


#### Task 1 Named Pipes (FIFO)
Implement the named pipe mechanism, also known as the first-in-first-out (FIFO) device. The server program creates a new named pipe to share with the client program, allowing the server to receive and execute Unix commands sent by the client through the same named pipe.

#### Task 2 Message Queues
Implement the message queue mechanism. The server program creates a new message queue and waits for Unix commands sent by the client through the message queue. Upon receiving the commands, the server executes each of them accordingly. The client sends Unix commands as messages of Type 1 and sends a Type 2 message to signal the end of the command list.

#### Task 3 Unix Sockets
Implement IPC based on Unix sockets. The server program creates a new socket and names it with a Unix domain name (pathname). The client program connects to the known socket set up by the server. Upon successful connection, the client sends Unix commands to the server through the socket. The server executes each received command.

### Instructions:
1. Compile the C code
2. The Client program should take an input file as a command line input.   
3. The input file should consist of a list of Unix commands with each command as a separate
line in the input file. For commands which require arguments for execution, the arguments
should be presented on the same line as the command itself with space separated.   
The sample command input file is `commands.txt`.
4. Start the Server program in the background before executing the Client program.
5. Sample Input and Output to start the program would be:   
```
$ ./socket_server &   
$ ./socket_client < commands.txt   
client: echo abcde   
server: abcde   
```
<br>

---
<br>

## C. Processor Scheduling Simulation in C

### Overview
Processor scheduling aims to assign processes to be executed by the processor (or processors) to achieve certain operating system objectives such as response time, turnaround time, throughput, and processor efficiency. Scheduling algorithms play a crucial role in determining which process should wait and which process should proceed for execution, thereby affecting the overall system performance.    

This task focuses on implementing and simulating the performance of three different scheduling algorithms and observing their effects on system performance. For simplicity, these scheduling algorithms are assumed to be applied only on a uniprocessor system.

### Task 1: First-Come-First-Served Scheduling (FCFS)
In the first task, it implements the simplest scheduling algorithm based on the first-come-first-served (FCFS) approach. With FCFS, the process that first arrives in the Ready queue is the first to be allocated the processor for execution. This is a non-preemptive algorithm.

### Task 2: Round Robin Scheduling (RR)
For the second task, it implements a preemptive scheduling algorithm based on the Round Robin (RR) approach. Processes in the Ready queue are still scheduled on a first-come-first-served basis, but each process is assigned a fixed time quantum for execution. Upon the time quantum's expiration, the currently running process is preempted and placed at the end of the Ready queue. This continues until all jobs complete execution.    
(For this task, the time quantum is set to 2 seconds.)

### Task 3: Shortest Remaining Time Scheduling (SRT)
The third scheduling algorithm it implements is based on the Shortest Remaining Time (SRT) concept. The scheduler always chooses the process with the shortest expected remaining processing time. If a new process arrives with a shorter remaining time than the currently running process, the scheduler may preempt the running process and promote the new one for execution.    
If two processes share the same shortest remaining processing time, FCFS is used to break the tie.

### Instructions:
1. Compile the C code
2. For each program implemented for the tasks below, it should take an input file as a command line input.
3.  The input file should have the following structure:    
- The first column contains the process ID
- The second column indicates the arrival time (in seconds) of each process in the Ready queue
- The last column refers to the total processing time (in seconds) required for the corresponding process.    
<small>Assume these processes are batch jobs and are processor-bound only (no I/O operations involved). </small>

4. Sample content of the input file as below:

| Process | Arrival Time | Processing Time |
|---------|--------------|-----------------|
| P1      | 0            | 3               |
| P2      | 1            | 6               |
| P3      | 4            | 4               |
| P4      | 6            | 2               |

The sample command input file is `processes<n>.txt`, where `<n>` represents `1`, `2`, `3`.

