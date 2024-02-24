/*
Basic Command Line
author : Loi Chai Lam
student ID : 2813 6179
start date : 23/8/2017
last modified : 30/8/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


#define LEN 100
#define SIZE 1024

/* Function Prototype */
int read_line(char line[], int limit);
char **separate_line(char *line);
void operation(char **argument, char *cwd_buffer);
void echo (char **argument);
void cd (char **argument);
void ls (char **argument);
void help (char **argument, char *cwd_buffer);
void create (char **argument);
void copy (char **argument);
void search(char **argument);
void run (char**argument);
void halt (char**argument);


/* main */
int main(int argc, char *argv[])
{
    char line[LEN]; //initialize the command entered with 100 maximum characters
	char **argument;
	int i; //argument length
	int flag = 1;
    char cwd_buffer[SIZE];
	
	while(1)
	{
        if (flag == 1)
        {
            getcwd (cwd_buffer,sizeof(cwd_buffer)); //record the initial path
            flag = 2;
        }
    	read_line(line,LEN); //read the line user entered
		argument = separate_line(line);
		operation(argument,cwd_buffer);
        free(argument);
	}	
    return 0;
}


/* Function */
int read_line(char line[], int limit)
{
    /*
    This function is used to read the command entered by the user
    argument : line - after reading, the command will store into line
             : limit - the limit of the character read
    return   : i - the numbers of character read
    */

    int c;
    char buffer[SIZE]; //store the cwd
	
	loop: //label
    getcwd (buffer,sizeof(buffer));
    printf("%s",buffer);
    printf(" $ ");
    int i = 0;
    while((c = getchar())!= EOF && c != '\n' && i < limit-1)
    //if the character read is not EOF, newline and the length of character read not exceed the limit set,
    //save the character to line
    {
        if (c != '"')
        {        
            line[i] = c;
            i++;
        }
    }
    //the last character in line to be '\0'
    line[i] = '\0';
	// if the first character is 'n', reload the statement
	if (line[0] == '\0')
	{
		goto loop; 
	}
    return i;
}


char **separate_line(char *line)
{
	/* This function is used to separate the command using strtok with delimiter " "
	argument : line - the line from read_line, which is the command entered by the user
	return   : i - the number of elements in the argument 
	*/
	
	char *tmp = NULL; //temporary store
    char **argument = malloc(SIZE * sizeof(char*)); //allocate memory for argument
    int i = 0; //argument length
	argument[1] = NULL; //initialize argument[1], as it will be used in cd function
	
	tmp = strtok( line, " "); 
    while( tmp != NULL )
    {
        argument[i] = tmp;
        tmp = strtok( NULL, " ");
        i++; 
    }
	return argument;
}
	

void operation (char **argument, char *cwd_buffer)
{
	/* This function is used to do the operation of command 
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
	
	if (strcmp(argument[0],"quit\0") == 0)  //quit command
    {
        exit(0);
    }
    else if (strcmp(argument[0],"clear\0") == 0) //clear command
    {
        printf("\x1b[3;J\x1b[H\x1b[2J"); //the information of the clear command at the bottom of code
		
    }
	else if (strcmp(argument[0],"echo\0") == 0) //echo command
	{
		echo(argument);
	}
	else if (strcmp(argument[0],"ls\0") == 0) //ls command
	{
		ls(argument);
	}
	else if (strcmp(argument[0],"cd\0") == 0) //cd command
	{
		cd(argument);
	}
    else if (strcmp(argument[0],"help\0") == 0) //help command
	{
		help(argument, cwd_buffer);
	}
	/*----------------------Task 2 --------------------------------------*/
	else if (strcmp(argument[0],"create\0") == 0) //create command
	{
		create(argument);
	}
	else if (strcmp(argument[0],"copy\0") == 0) //copy command
	{
		copy(argument);
	}
    else if (strcmp(argument[0],"search\0") == 0) //search command
	{
		search(argument);
	}
    else if (strcmp(argument[0],"run\0") == 0) //run command
    {
        run(argument);
    }
    else if (strcmp(argument[0],"halt\0") == 0) //halt command
    {
        halt(argument);
    }
	else
	{
		printf("command not found.\n");
	}
}


void echo (char **argument)
{
	/* This function is "echo" command, which used to display the statement on the output screen
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
	
	int pid;
	
	pid = fork(); //create new process	
	if (pid < 0)
	{
		perror("fork error : child process could not be created");
	}
	else if (pid == 0) //child process
	{
		if (execvp ("echo",argument) < 0)
		{
			perror("execvp error");
		}
	}
	else //parent process
	{
		waitpid(pid,NULL,0); //wait for the child process to terminate
		printf("\n");
	}
}


void cd (char **argument)
{
    /* This function is "cd" command, which used to change the default directory
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
    
	char *home_environment;
	char *get_PWD;
	char buffer[SIZE];
	
	if (argument[1] == NULL) //only one argument, which is cd
	{
		home_environment = getenv("HOME"); //get the environment variable
		chdir(home_environment);
		setenv("PWD",home_environment,1); //set the environment variable, PWD
		get_PWD = getenv("PWD");
		//printf("Current directory (HOME) : %s\n",get_PWD);
	}
	else if (chdir(argument[1]) < 0)
	{
		perror("Directory does not exist.");
	}
	else
	{
		getcwd (buffer,sizeof(buffer));
		//printf("Current directory : %s\n",buffer);
		setenv("PWD",buffer,1);
	}
}


void ls (char **argument)
{
	/* This function is "ls" command, which used to list the contents of given directory, which is argument[1]
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
	
	int pid; //id of processs
	
	pid = fork(); 	
	if (pid < 0)
	{
		perror("fork error : child process could not be created");
	}
	else if (pid == 0) 
	{
		if (execvp ("ls",argument) < 0)
		{
			perror("execvp error");
		}
	}
	else
	{
		waitpid(pid,NULL,0); 
	}
}


void help (char **argument, char *cwd_buffer)
{
    /* This function is "help" command, which used to display the user manual
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
	
	int pid; //id of processs

	pid = fork(); 	
	if (pid < 0)
	{
		perror("fork error : child process could not be created");
	}
	else if (pid == 0) 
	{
        chdir(cwd_buffer);
		if (execlp ("more", "more", "help.txt", NULL) < 0)
		{
            perror("execvp error");
		}
	}
	else
	{
		waitpid(pid,NULL,0); 
	}       
}


void create (char **argument)
{
	/* This function is "create" command, which create a new file with name <filename>, which is argument[1]
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
	
	int fd; //file descriptor
	
	if ((fd = open(argument[1], O_CREAT|O_EXCL, 0777)) < 0) //create new file, the owner, group and others can read, write as well as execute the file
	{
		perror(argument[1]);
	}
	else
	{
		printf("The file %s is created.\n",argument[1]);
	}
    close(fd);
}


void copy (char **argument)
{
	/* This function is "copy" command, which copy an existing file named <old> to a new file named <new>
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
    int fd_old; //file descriptor <old> file
    int fd_new; //file descriptor <new> file
    char buffer[SIZE];
    int n;
    
    if ((fd_old = open(argument[1],O_RDONLY)) < 0) //open <old> file
    {
        perror("Open file error."); 
    } 
    else if ((fd_new = open(argument[2],O_CREAT|O_TRUNC|O_WRONLY, 0777)) < 0)//create <new> file
    {
        perror("Create file error.");
    }
    else
    { 
        lseek (fd_old,0,SEEK_SET);
        while ((n = read(fd_old, buffer, sizeof(buffer))) > 0)
        {
            write(fd_new,buffer,n);
        }   
        close(fd_old);
        close(fd_new); 
    }   
}


void search(char **argument)
{  
	/* This function is "search" command, 
    which display the number of occurrsences of a sequence of character in file
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
    
    int fd, occur = 0, i = 1;
    char *buffer = malloc(SIZE * sizeof(char*)); //allocate memory for buffer
	int len = strlen(argument[1]);
	
	if ((fd = open(argument[2], O_RDONLY)) < 0) 
	{
		perror(argument[2]);
	}
	else
	{
		while ((read(fd, buffer, len)) > 0)
		{
			lseek (fd,i,SEEK_SET);
			if ((strstr(buffer, argument[1])) != NULL)
			{
				occur ++;
			}
			i++;
    	} 
		printf("Number of occurrences of %s in %s is %d \n", argument[1], argument[2], occur);
		close(fd); 
    }
    free(buffer);
}
    
    
void run (char**argument)
{
	/* This function is "run" command, which execute an executable program
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
    int pid; //id of processs
    char name[SIZE]; //name of the program run
	
	pid = fork(); 	
	if (pid < 0)
	{
		perror("fork error : child process could not be created");
	}
	else if (pid == 0) 
	{
        strcpy (name,"./");
        strcat(name, argument[1]);
		if (execvp (name,argument) < 0)
		{
			perror("execvp error");
		}
	}
	else
	{
        waitpid(pid,NULL,0); 
	}
	
}


void halt (char**argument)
{
	/* This function is "halt" command, which stop executing the program
	argument : argument - the separated line of command entered by the user
	return   : -
	*/
    int pid; //id of processs
    char name[SIZE]; //name of the program run
	
	pid = fork(); 	
	if (pid < 0)
	{
		perror("fork error : child process could not be created");
	}
	else if (pid == 0) 
	{
        if (execlp ("killall","-9",argument[1],NULL) < 0)
		{
			perror("execvp error");
		}
	}
	else
	{
		waitpid(pid,NULL,0); 
	}	
}


/* <ESC> = \x1b, its the ASCII
   <ESC>[{ROW};{COLUMN}H - Set the cursor position where subsequent text will begin. 
                           If no row/column parameters are provided(ie. <ESC>[H), the cursoe will move to the home position, at the upper left of screen
   <ESC>[2J - Erases the screen with the background colour and moves the cursor to home					   
Link : www.termsys.demon.co.uk/vtansi.htm
*/