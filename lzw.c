#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TABLE 4000 //Maximum amount of elements in the table
#define MAX_STRING 1000 //Maximum length of a string in the table

int main()
{
	int input[] = {85, 119, 85, 32, 79, 119, 79, 32, 110, 121, 97, 263, 265, 259, 261, 32, 118, 101, 114, 121, 32, 99, 117, 116, 101, 32, 256, 258, 99, 111, 109, 112, 114, 101, 115, 115, 105, 111, 110, 32, 101, 120, 97, 286, 108, 101}; //"UwU OwO nya nya OwO very cute UwU compression example" in LZW

	//Allocate string array (table)
	unsigned char** table = malloc(MAX_TABLE*sizeof(unsigned char*));
	for(int i = 0; i < MAX_TABLE; i++)
	{
		table[i] = malloc(MAX_STRING);
	}
	
	//This boolean arary will store whether an element exists in the table
	bool* marked = malloc(MAX_TABLE*sizeof(bool));

	//Fill the table with initial values: all possible bytes
	for(int i = 0; i < 256; i++)
	{
		table[i][0] = i;
		table[i][1] = 0;
		marked[i] = true;
	}

	//OLD is the first input value
	int old = input[0];
	int n;
	char* s = malloc(MAX_STRING);
	strcpy(s, table[old]); //Set s as retrieving the first input value from the table
	char* c = malloc(MAX_STRING);
	c[0] = s[0]; //C is the first value of s
	c[1] = 0;
	printf("%s", s);
	int count = 256;
	char* result = malloc(MAX_STRING);
	for(int i = 0; i < (sizeof(input)/sizeof(int)) - 1 /*size of input - 1*/; i++)
	{
		n = input[i + 1]; //NEW is the next input value
		if(marked[n]) //Does n exist in the table?
		{
			strcpy(s, table[n]); //If yes, retrieve it
		}
		else
		{
			//If not, take the current (OLD) value from the table
			strcpy(s, table[old]);
			//And simply concatenate it with C
			strcat(s, c);
		}
		printf("%s", s); //We have our output for now!
		memset(c, 0, strlen(c)); //Reset C
		c[0] = s[0]; //And set it as the fist symbol of S again
		strcat(result, table[old]);
		strcat(result, c);
		strcpy(table[count], result); //Add a new entry to the table that contains a combination that might be retrieved later
		marked[count] = true; //The entry now exists
		count++;
		old = n;
		memset(result, 0, strlen(result));
	}
	printf("\n");
	printf("%d\n", sizeof(input)/sizeof(int));
	
	//Free all the memory
	free(s);
	free(c);
	free(result);
	free(marked);
	for(int i = 0; i < MAX_TABLE; i++)
	{
		free(table[i]);
	}
	free(table);
}
