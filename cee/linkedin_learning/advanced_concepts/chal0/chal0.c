// Create a char Pointer
// 1) Create char variables a, b, and c, plus char pointer *p.
// 2) Assign 'A' to variable a.
// 3) Initialize pointer p to variable a.
// 4) Assign a variable b to the value referenced by pointer p.
// 5) Intialize pointer p to variable c.
// 6) Assign the value addressed by pointer p to 'Z'
// 7) Use a printf() statement to display the values of variables a, b, and c.

#include <stdio.h>

int main()
{
    char a, b, c, *p;

    a = 'A';
    p = &a;
    b = *p;
    p = &c;
    *p = 'Z';

    printf("%c %c %c\n", a, b, c);

    return(0);
}
