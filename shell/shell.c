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
	char* string;	//Stores the buffer input
	char* command;	//Stores the command given by the user
	int pid;		//Stores value of child process after fork()

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);	//Read buffer input into 'string'

		string[2] = '\0';

		if(string[0] == 'X')
			exit(0);

		else
		{
			args = Mytoc(string, ' ');	//Separate individual arguments by a ' '

			pid = fork();	//Create child process

			if(pid < 0)		//Child process creation was unsuccessful
			{
				fprintf(stderr, "Unsuccessful fork()\n");
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
	return 0;
}
