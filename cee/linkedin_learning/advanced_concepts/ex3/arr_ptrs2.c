#include <stdio.h>

int main()
{
    int array[] = { 11, 13, 17, 19 };
    int *aptr;

    //aptr = &array[1];
    aptr = array;
    //aptr = aptr + 1;

    printf("The element is %d\n", *(aptr+3));

    printf("The element is %d\n", array[3]);

    return(0);
}
