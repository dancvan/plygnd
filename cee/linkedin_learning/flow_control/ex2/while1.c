#include <stdio.h>

int main()
{
    int x;

    x = 2;
    while( x <= 10 )
    {
	printf("%d\n",x);
	x = x + 2;
    }

    return(0);
}
