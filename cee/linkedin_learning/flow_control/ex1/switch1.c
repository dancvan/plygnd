#include <stdio.h>

int main()
{
    char a;

    printf("Your choice (A,B,C): ");
    scanf("%c", &a);
    
    switch(a)
    {
	case 'A':
	case 'a':
		puts("Excellent choice!");
		break;
	case 'B':
	case 'b':
		puts("This is the most common choice.");
		break;
	case 'C':
	case 'c':
		puts("I question your decision.");
		break;
	default:
		puts("That's not a valid choice.");
    }

    return(0);
}
