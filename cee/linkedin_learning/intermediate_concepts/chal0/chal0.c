// Build a String
// 1) Create storage for two strings
// 2) Fetch input for both strings.
// 3) Concatenate (append) the second string to the end of the first string
// 4) Display the final string.

#include <stdio.h> 
#include <string.h>

int main()
{
    char input1[32];
    char input2[32];
    char buffer[64];

    printf("First name: ");
    fgets(input1, 32, stdin);
    printf("Last name: ");
    fgets(input2, 32, stdin);

    strcpy(buffer, input1);
    strcat(buffer, input2);
    printf("%s", buffer);

    return(0);
}
