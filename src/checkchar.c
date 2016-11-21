#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int checkChar(char string[], char searchFor)
{
	int length;
	int i;
	length = strlen(string);
	for(i = 0; i < length; i++)
	{
		if (string[i] == searchFor)
		{
			return 1;
			break;
		}
	}
return 0;
}

