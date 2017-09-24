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

#define BUFFERSIZE 150 /****Defines the max size of buffer.****/

int main()
{
	int i, tokenCount;
	char delim = ' ';
	char* string;
	char** tokenVec;

	while(1) /****Program runs input prompt until X is typed in.****/
	{
		string = (char*) malloc(BUFFERSIZE); /****String used to hold the input.****/

		write(1, "$ ", 2);
		read(0, string, BUFFERSIZE); /****Reads the input to the string variable.****/

		if(string[0] == 'X')
			exit(0);

		else
		{
			tokenCount = tokenCounter(string, delim);
			tokenVec = Mytoc(string, delim); /****Call to Mytoc() function to obtain a vector of tokens.****/

			for (i = 0; i < tokenCount; i++) /****Loop to print the contents of the token vector.****/
			{
				printf("[%d] : %s\n", i, tokenVec[i]);
			}

			for (i = 0; tokenVec[i] != '\0'; i++)
			{
				free(tokenVec[i]);
			}
			free(tokenVec);//****Frees the memory allocated to the token vector before moving on the the next input.****/
		}
		free(string);
		tokenCount = 0;
	}

	return 0;
}
