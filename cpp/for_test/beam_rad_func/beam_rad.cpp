#include <iostream>
#include <cmath>
using namespace std;


float W_z(float z){
    float lambd = 1064e-9;
    float W_0 = 200e-6;
    return W_0*sqrt(1 + ((z*lambd)/(M_PI*(W_0*W_0))));
}

int main()
{ 
    float z = .333;
    cout << W_z(z) << endl;
    return 0;
}
