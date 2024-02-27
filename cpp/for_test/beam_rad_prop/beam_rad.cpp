#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


float W_z(float z){
    float lambd = 1064e-9;						// wavelength
    float W_0 = 200e-6;							// Characteristic waist
    return W_0*sqrt(1 + ((z*z*lambd*lambd)/(M_PI*M_PI*(W_0*W_0)*(W_0*W_0)))); 			// Beam radius function
}

int main() { 
    ofstream myFile; 
    myFile.open("beam_rad.csv", ios::app); 				// Creates file

    myFile << "position [m]" << ", " << "beam radius [m]" << endl;

    for (float i = 0; i <= 1.7; i = i + .1)
    {
      myFile << i << ", " << W_z(i) <<  endl;
    }
    
    myFile.close();							// Close file

    return 0;
}
