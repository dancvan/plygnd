#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main (int argc, char* argv[])
{
    int i;
    int terms[32]; // storage of a0, a1, etc, up to 32 bits
    int number = atoi(argv[1]);
    // initialise the term a0, a1, etc
    for (int i=0; i < 32 ; i++) terms [i] = 0;
    for (int i=0; i < 32 ; i++){
	terms[i] = number%2; 	// modulo division done by %
	number /= 2;
    }
    // write out results
    cout << "Number of bytes used= " << sizeof(number) << endl;
    for (i=0; i < 32 ; i++){
	cout << " Term nr: " << i << " Value= " << terms [i];
	cout << endl;
    }
    return 0;
}
