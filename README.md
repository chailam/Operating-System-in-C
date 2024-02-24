# Operating-System-in-C
Operating System Unit to Code in C

## Basic Command Line Interface (CLI) Implementation in C

### Objective
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


### Implementation Details
- **Operating System**: Unix/Linux
- **Language**: C programming language
