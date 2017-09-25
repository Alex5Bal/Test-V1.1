#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 150

int main(int argc, char** argv, char** envp)
{
	char** args, path;
	char* string, program;
	int pid;

	while(1)
	{
		string = (char*) malloc(BUFFERSIZE);

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE);

		if(strComp(string, "exit\n"))
			exit(0);

		else
		{
			args = Mytoc(string, ' ');

			pid = fork();

			if(pid < 0)
			{
				fprintf(stderr, "fork() failed\n");
				exit(1);
			}
			else if(pid == 0)
			{
				printf("hello");
				exit(0);
			}
		}

		free(string);
	}
}
