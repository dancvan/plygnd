#include <stdio.h>
#include <string.h>

int main()
{
    char input[64];
    int len;

    printf("Instructions: ");
    fgets(input, 64, stdin);
    len = strlen(input);
    printf("You typed %d characters of instructions.\n", len);

    return(0);
}
