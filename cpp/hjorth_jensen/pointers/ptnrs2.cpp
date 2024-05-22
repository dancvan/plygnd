#include <iostream>
using namespace std;

int main()
{
    int var;
    int *p; 
    p = &var;
    var = 421;
    printf("Address of integer variable var : %p\n", &var); 
    printf("It's value: %d\n", var); 
    printf("Value of integer pointer p : %p\n", p); 
    printf("The value p points at : %d\n", *p); 
    printf("Address of the pointer p : %p\n", &p);
    return 0;
}
