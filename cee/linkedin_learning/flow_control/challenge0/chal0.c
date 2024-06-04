#include <stdio.h>

int main()
{
    int a;
    printf("Please type an integer:");
    scanf("%d", &a);

    if(a == 1)
    {
	puts("Red");
    }
    else if(a == 2)
    {
	puts("Green");
    }
    else if(a == 3)
    {
	puts("Blue");
    }
    else
    {
	puts("Invalid input");
    }

    return 0;

}
