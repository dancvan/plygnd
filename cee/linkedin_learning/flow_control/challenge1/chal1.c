// Output a Series of Numbers:
// 1) Code a for loop that outputs values 1 through 20
// 2) Code a while loop that outputs even values from -10 through 10 
// 3) Both loops go into the same source code file.
//
#include <stdio.h>

int main()
{
    int a;
    int b = -10;

    for(a=0;a<20;a++)
	printf("%d\n", a+1);

    do
    {
	printf("%d\n",b);
	b = b +2;
    }
    while( b <= 10 );

    return(0);
}
    

