#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 150

int main(int argc, char** argv, char** envp)
{
	char** args;	//Stores the arguments passed by the user
	char** tempVec;	//Temporary vector used to hold the value of each key in the envp[]
	char** path;	//Stores the value of PATH
	char* string;	//Stores the user input
	char* command;	//Stores the command given by the user
	int pipe1[2];
	int pipe2[2];
	int pid, pid2;		//Stores value of child process after fork()

	if(pipe(pipe1) < 0)
	{
		perror("Pipe failed\n");
		exit(1);
	}
	if(pipe(pipe2) < 0)
	{
		perror("Pipe failed\n");
		exit(1);
	}

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);	//Read buffer input into 'string'

		removeNewLine(string);	//Removes '\n' from the end of the input string

		if(string[0] == 'X')
			exit(0);

		else
		{
			args = Mytoc(string, ' ');	//Separate individual arguments by a ' '

			pid = fork();	//Create child process

			//if(args[1] == "|")
			if(1)
			{
				if(pid < 0)		//Child process creation was unsuccessful
				{
					perror("Fork failed\n");
					exit(1);
				}
				else if(pid == 0)	//Child process created successfully
				{
					dup2(pipe1[1], STDOUT_FILENO);
					close(pipe1[0]);
					close(pipe2[1]);
					dup2(pipe2[0], STDIN_FILENO);
					execve("/bin/ls", args, envp);
					printf("Command not found\n");	//No valid commands were identified
					exit(0);
				}
				else
				{
					wait(pid);		//Appended(Remove if needed!)
					pid2 = fork();

					if(pid2 < 0)		//Child process creation was unsuccessful
					{
						perror("Fork failed\n");
						exit(1);
					}
					else if(pid2 == 0)
					{
						dup2(pipe1[0], STDIN_FILENO);
						close(pipe1[1]);
						dup2(pipe2[1], STDOUT_FILENO);  	//Appended (Remove if needed!)
						close(pipe2[0]);					//Appended (Remove if needed!)
						execve("/bin/wc", args, envp);
						printf("Command not found\n");	//No valid commands were identified
						exit(0);
					}
					else
					{
						close(pipe1[0]);
						close(pipe1[1]);
						close(pipe2[0]);
						close(pipe2[1]);
						wait(NULL);	//Wait for the child process to end

					}
				}
			}

			else
			{
				if(pid < 0)		//Child process creation was unsuccessful
				{
					perror("Fork failed\n");
					exit(1);
				}
				else if(pid == 0)	//Child process created successfully
				{
					for(int i = 0; envp[i] != (char*)0; i++)	//Traverse envp[]
					{
						tempVec = Mytoc(envp[i], '=');	//Identify key and value by tokenizing with '='

						if(strComp(tempVec[0], "PATH"))	//If the key value is PATH
						{
							path = Mytoc(tempVec[1], ':');	//Tokenize the value of PATH with ':'
							break;	//Exit loop, path has been found
						}

						free(tempVec);	//Ready for next iteration
					}

					command = strCat("/", args[0]);	//Ready user command to be used w/ the path

					for(int j = 0; path[j] != '\0'; j++)	//Traverse the path vector until valid path is executed
					{
						free(args[0]);	//Ready args[0] to store the complete path
						args[0] = strCat(path[j], command);	//args[0] contains complete path
						printf("%s\n", args[0]);
						execve(args[0], args, envp);	//Execute the complete path if valid
					}

					printf("Command not found\n");	//No valid commands were identified
					exit(0);
				}

				else
				{
					wait(NULL);	//Wait for the child process to end
				}
			}

			free(string);	//Ready string for next buffer input

			for (int i = 0; args[i] != '\0'; i++)	//Ready args[] for next command
			{
				free(args[i]);
			}

			free(args);
		}
	}
	return 0;
}
