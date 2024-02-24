# Operating-System-in-C
Operating System Unit to Code in C

## Basic Command Line Interface (CLI) Implementation in C

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

## Interprocess communication (IPC) Implementation in C

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



