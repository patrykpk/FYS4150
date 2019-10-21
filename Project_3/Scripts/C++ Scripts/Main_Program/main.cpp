#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
#include <string>

#include "CoordinateSystem.h"
#include "GaussianQuadrature.h"
#include "MonteCarlo.h"

using namespace std;


int main(){
    // Assigning the value of PI to constant variable
    const double PI = atan(1.0)*4;
    int n;        // Either degree of polynomial or sampling points (Based on method)
    double a,b;   // Integration limits

    int Method;
    cout << "What would you like to do?" << endl;
    cout << "Values listed below give output for one value of 'n' in the terminal\n";
    cout << "[1] Legendre, [2] Laguerre, [3] MonteCarlo\n\n";
    cout << "Remaining options write the output to file up to the given value of 'n' for \n";
    cout << "[4] Legendre & Laguerre or [5] MonteCarlo\nMethod: ";
    cin >> Method;   // Input method

    if (Method == 1){
        // Legendre to Terminal
        cout << "What degree of Legendre polynomial would you like to approximate with?" << endl;
        cin >> n;
        cout << "-----------------------------------------------------------------------------"<<endl;
        integration_limit();
        cout << "-----------------------------------------------------------------------------"<<endl;
        cout << "Read in integration limits [a,b]" << endl;
        cout << "Value of a: ";
        cin >> a;
        cout << "Value of b: ";
        cin >> b;

        bool WriteToFile = false;             // Output to terminal
        double int_legendre, Legendre_time;   // Declaring the integral and time
        GQ_legendre(a, b, n, int_legendre, Legendre_time, WriteToFile);  // Evaluating the integral

    }
    else if (Method == 2){
        // Laguerre to Terminal
        cout << "What degree of Laguerre polynomial would you like to approximate with?" << endl;
        cin >> n;

        bool WriteToFile = false;            // Output to terminal
        double int_laguerre, Laguerre_time;  // Declaring the integral and time
        GQ_laguerre(n,PI, int_laguerre, Laguerre_time, WriteToFile);     // Evaluating the integral

    }
    else if (Method == 3){
        // Monte Carlo to Terminal
        cout << "Do you want to run [1] Brute Force or [2] Importance sampling? " << endl;
        int Number;
        cin >> Number;

        bool WriteToFile = false;            // Output to terminal

        // Declaring and assigning input values for functions
        double Int_MonteCarlo = 0;
        double Time = 0;
        double Standard_Dev = 0;

        switch(Number){
            case 1:
                cout << "Read in the number of integration points 'n'" << endl;
                cin >> n;
                cout << "-----------------------------------------------------------------------------"<<endl;
                integration_limit();
                cout << "-----------------------------------------------------------------------------"<<endl;
                cout << "Read in integration limits [a,b]" << endl;
                cout << "Value of a: ";
                cin >> a;
                cout << "Value of b: ";
                cin >> b;
                MonteCarloBF(a,b,n, Int_MonteCarlo, Time, Standard_Dev, WriteToFile);
                break;

            case 2:
                cout << "Read in the number of integration points" << endl;
                cin >> n;
                MonteCarlo_IS(n, Int_MonteCarlo, Time, Standard_Dev, WriteToFile);
                break;
         }
    }
    else if (Method == 4){
        // Legendre and Laguerre to file
        cout << "Read in the number of integration points 'n'" << endl;
        cin >> n;
        cout << "-----------------------------------------------------------------------------"<<endl;
        integration_limit();  // Approximates infinity (Simple method with integers)
        cout << "-----------------------------------------------------------------------------"<<endl;
        cout << "Insert integration limits a and b" << endl;
        cin >> a >> b;
        string outfilename = "Project_3_GQ.txt"; // Filename for Legendre and Laguerre output
        OutputToFile(a, b, n, outfilename);      // Function that writes to file
    }
    else if (Method == 5){
        // Monte Carlo Brute Force and Importance Sampling to file
        cout << "Read in the maximum number of integration points (10^n) \n";
        cout << "Value of n: ";
        cin >> n;
        cout << "-----------------------------------------------------------------------------"<<endl;
        integration_limit();
        cout << "-----------------------------------------------------------------------------"<<endl;
        cout << "Read in integration limits [a,b]" << endl;
        cout << "Value of a: ";
        cin >> a;
        cout << "Value of b: ";
        cin >> b;
        string outfilename = "Project_3_MC.txt"; // Filename for Monte Carlo
        OutputToFileMC(a, b, n, outfilename);    // Function that writes to file
    }
}




