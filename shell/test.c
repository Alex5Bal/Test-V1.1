#include <stdio.h>
#include <stdlib.h>
#include "mystrlib.h"

int main()
{
	char string1[] = "hello";
	char string2[] = "world";

	int match = strComp(string1, string2);
	printf("Match: %d\n", match);

	int length1 = strLen(string1);
	int length2 = strLen(string2);
	printf("Length 1: %d\n", length1);
	printf("Length 2: %d\n", length2);

	char* catStr = strCat(string1, string2);
	printf("Concatenated: %s\n", catStr);

	char* copiedStr = malloc(strLen(catStr));
	strCopy(copiedStr, catStr);
	printf("Copied: %s", copiedStr);
}
