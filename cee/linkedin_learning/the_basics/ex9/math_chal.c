#include <stdio.h>
#include <math.h>

int main() 
{
    float a, b;

    printf("Input first number to operate with:");
    scanf("%f", &a);
    printf("Input second number to operate with:");
    scanf("%f", &b);

    printf("%f + %f = %f\n", a, b, a+b);
    printf("%f - %f = %f\n", a, b, a-b);
    printf("%f * %f = %f\n", a, b, a*b);
    printf("%f / %f = %f\n", a, b, a/b);
    printf("%f^%f = %f\n", a, b, pow(a,b));
    printf("sqrt(a) = %f and sqrt(b) = %f\n", sqrt(a), sqrt(b));

    return(0);
}



