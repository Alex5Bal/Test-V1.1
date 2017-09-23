/*
 * Author: Alejandro Balderrama
 * Class: Theory of Operating Systems
 * Professor: Dr. Freudenthal
 * Project: Tokenizer
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mytoc.h"
#include "mystrlib.h"

#define BUFFERSIZE 200 /****Defines the max size of buffer.****/

int main()
{
	int i;
	char delim = ' ';

	while(1) /****Program runs input prompt until X is typed in.****/
	{
		char *string = (char*) malloc(BUFFERSIZE); /****String used to hold the input.****/

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE); /****Reads the input to the string variable.****/

		if(strComp(string, "exit\n"))
			exit(0);

		else
		{
			int tokenCount = tokenCounter(string, delim);
			char** tokenVec = Mytoc(string, delim); /****Call to Mytoc() function to obtain a vector of tokens.****/

			for (i = 0; i < tokenCount; i++) /****Loop to print the contents of the token vector.****/
			{
				printf("[%d] : ", i);

				printf("%s", tokenVec[i]);

				printf("\n");
				tokenCount = tokenCounter(string, delim);
			}

			for (i = 0; i < tokenCount; i++)
			{
				free(tokenVec[i]);
			}
			free(tokenVec); /****Frees the memory allocated to the token vector before moving on the the next input.****/
		}
		free(string);
	}

	return 0;
}
