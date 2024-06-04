#include <stdio.h>

void cheers(void)
{
    int x;

    for(x=0;x<3;x++)
	printf("Huzzah! ");
    putchar('\n');
}

int main()
{
    puts("Everyone gets free dinner!");
    cheers();
    puts("Everyone gets free dessert!");
    cheers();

    return(0); 
}

