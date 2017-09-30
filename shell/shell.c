#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 150

int main(int argc, char** argv, char** envp)
{
	char** arg;
	char** tempVec;
	char** path;
	char* string;
	char* command;
	pid_t pid;


//	for(i = 0; envp[i] != (char*)0; i++)
//	{
//		printf("envp[%d] = %s\n", i, envp[i]);
//	}
//	printf("\n\n\n");
//	i = 0;

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);

		if(string[0] == 'X')
			exit(0);

		else
		{
			arg = Mytoc(string, ' ');

			pid = fork();

			if(pid < 0)
			{
				fprintf(stderr, "Unsuccessful fork()\n");
				exit(1);
			}
			else if(pid == 0)
			{
				for(int i = 0; envp[i] != (char*)0; i++)
				{
					tempVec = Mytoc(envp[i], '=');

					if(strComp(tempVec[0], "PATH"))
					{
						path = Mytoc(tempVec[1], ':');
					}

					free(tempVec);
				}

				//printVector(path);

				command = strCat("/", arg[0]);

				for(int j = 0; path[j] != '\0'; j++)
				{
					free(arg[0]);
					arg[0] = strCat(path[j], command);
					execve(arg[0], arg, envp);
				}

				printf("Command not found\n");
				exit(0);
			}

			else
			{
				wait(NULL);
			}
		}
		free(string);

		for (int i = 0; arg[i] != '\0'; i++)
		{
			free(arg[i]);
		}

		free(arg);
	}
	return 0;
}
