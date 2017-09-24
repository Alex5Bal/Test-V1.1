/*
 * Author: Alejandro Balderrama
 * Class: Theory of Operating Systems
 * Professor: Dr. Freudenthal
 * Project: Tokenizer
 *
 * Description: The following program implements a string tokenizer. This implementation works by reading in an input string from the user,
 * 			    partitioning its individual tokens by the ' ' character, then storing each token into a vector. The initial input is
 * 			    printed line-by-line along with its vector position.
 */
#include <stdio.h>
#include <stdlib.h>
#include "mytoc.h"

int tokenCounter(char* stringIn, char delim) /****Returns the number or tokens in a given string.****/
{
	int i = 0, numTokens = 1;

	while (stringIn[i] != '\n') /****Traverse the string until the null character is reached.****/
	{
		if (stringIn[i] == delim) /****While traversing, if a space is encountered add 1 to the token counter.****/
		{
			numTokens++;
		}
		i++;
	}
	return numTokens;
}

int* characterCounter(char* stringIn, int numTokens, char delim) /****Returns an int vector containing the number of characters per token.****/
{
	int i, j, k = 0, x = 0, numChars = 0;
	int* numCharacters  = (int*)calloc(numTokens + 1, sizeof(int)); /****In-method int array used to store the # of characters per token.****/

	for (i = 0; stringIn[i] != '\n'; i++) /****Loop to traverse the entire string.****/
	{
		if (stringIn[i] == delim) /****While traversing, if a space is encountered...****/
		{
			for (j = x; stringIn[j] != delim; j++) /****Index j returns to the last location of x...****/
			{									 /****x points to the beginning of the last token before the space was encountered.****/
				numChars++;						 /****The # of characters is counted until the space is reached.****/
			}
			numCharacters[k] = numChars; /****Stores the number of characters for the current token.****/
			numChars = 0; /****Reset the variable before moving on to the next token.****/
			x = i + 1; /****Ensures the index is pointing to the beginning of the next token and not to space.****/
			k++;
		}
	}

	for (j = x + 1; stringIn[j] != '\0'; j++) /****Loop used to count the number of characters in the last token of the string.****/
	{
		numChars++;
	}
	numCharacters[k] = numChars;

	return numCharacters;
}

char** Mytoc(char* stringIn, char delim) /****Returns a string vector of space delimited tokens.****/
{
	int i, j = 0, x = 0, tokenCount = tokenCounter(stringIn, delim);
	char** tokenVecOut = (char**)calloc(tokenCount + 1, sizeof(char*)); /****Memory allocation to hold each token.****/
	int* numCharacters = characterCounter(stringIn, tokenCount, delim);

	for (i = 0; i < tokenCount; i++)
	{
		tokenVecOut[i] = (char*)malloc((numCharacters[i] + 1) * sizeof(char)); /****Memory allocation to hold characters of tokens.****/
	}

	i = 0;

	while (stringIn[x] != '\n') /****Traverse the entire string.****/
	{
		if (stringIn[x] != delim) /****If the current character is not equal to the delimiter...****/
		{
			tokenVecOut[i][j] = stringIn[x]; /****Copy the current character to the vector.****/
			j++;
		}
		if (stringIn[x] == delim) /****If the current character is equal to the delimiter...****/
		{
			tokenVecOut[i][j] = '\0'; /****Assign a null character to the end of the token.****/
			i++;
			j = 0; /****Reset j before continuing to next token.****/
		}
		x++;
	}
	tokenVecOut[tokenCount] = (char*)0;

	return tokenVecOut;

}
