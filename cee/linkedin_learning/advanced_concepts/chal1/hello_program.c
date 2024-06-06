// Write a 'Hello' Program
// 1) Allocate a text input (char) buffer.
// 2) Prompt the user to type their name.
// 3) Store the name in the input buffer.
// 4) Display the text input as a greeting.

#include <stdio.h>
#include <stdlib.h>

#define SIZE 64

int main()
{
    char *buffer;

    buffer = malloc(sizeof(char)*SIZE);
    if ( buffer == NULL)
    {
	puts("Memory error");
	return(1);
    }
    else
    {
	printf("Please type your name: ");
	fgets(buffer, SIZE, stdin);
	printf("Hello %s\n", buffer);
    }
} 
