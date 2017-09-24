#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 150

char** programEnvironment(char **envp);

int main(int argc, char** argv, char** envp)
{
	char** args, path;
	char* string, program;
	pid_t pid;

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);

		if(string[0] == 'X')
			exit(0);

		args = Mytoc(string, ' ');

		pid = fork();

		if(pid < 0)
		{
			fprintf(stderr, "fork() failed\n");
			exit(1);
		}
		else if(pid == 0)
		{
			path = programEnvironment(envp);
			program = strCat("/", args[0]);

			while(*path)
			{
				free(args[0]);
				args[0] = strCat(*path, program);
				execve(args[0], args, envp);
				path++;
			}
			printf("Command not found\n");
			exit(0);
		}
		else
		{
			wait(NULL);
		}
		free(string);

		for (int i = 0; args[i] != '\0'; i++)
		{
			free(args[i]);
		}

		free(args);

	}
	return 0;
}

char** programEnvironment(char **envp)
{
    char** tokenVec, pathVec;
    char* path;

    while(*envp)
    {
        tokenVec = Mytoc(*envp, '=');

        if(strComp(*tokenVec, "PATH"))
        {
            path = strCopy(tokenVec[1]);
        }

        for (int i = 0; tokenVec[i] != '\0'; i++)
        {
        	free(tokenVec[i]);
        }
        free(tokenVec);
        envp++;
    }

    pathVec = Mytoc(path, ':');

    free(path);

    return pathVec;

}
