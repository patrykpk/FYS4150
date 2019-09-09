#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>
#include "time.h"

#include "algorithms.h"

using namespace arma;
using namespace std;
ofstream ofile;

//Functions
double Solution(double x) {return 1.0-(1.0-exp(-10.0))*x-exp(-10.0*x);}   // Known solution

double f(double x) {return 100*exp(-10*x);}   // Source term

//Main program starts here
int main(int argc, char* argv[]) {

    char *outfilename;
    int n;

    // Checking if enough arguments are given in the command line
    if( argc <= 2 ){
      cout << "Error occured: " << argv[0] <<
          "Required arguments are the output filename without extension and a value of n (int)" << endl;
      cout << "Optional: Inserting an arbitary third argument will also run LU" << endl;
      exit(1);
    }
    else{
      outfilename = argv[1];          // First command line argument - Filename
      n = atoi(argv[2]);              // Second command line argument - Value of n

      char* Add_Amount = argv[2];     // Pointer to the n value
      string str = ".txt";            // Extension to the file
      char* Extension = &str[0];

      strcat(outfilename,Add_Amount);  // Adding the n value to the output name
      strcat(outfilename, Extension);  // Adding the extension to the output name

      // Resulting filename "outfilenamen.txt"
    }

    double h = 1.0/(n+1.0);            // Step length

    //Dynamic allocation of memory
    double *x = new double[n+2];      // Grid points
    double *u = new double[n+2];      // Analytical solution

    // Filling the arrays with values
    for (int i=0; i<=n+1; i++) {
        x[i] = i*h;
        u[i] = Solution(x[i]);
    }
    u[0] = 0;    // Making sure that the boundary conditions
    u[n+1] = 0;  // are satisfied

    // Acquiring the values for general algorithm
    double *v = new double[n+2];
    v = General_Algorithm(x, f, h, n);           // Function from algorithms.cpp

    //Acquiring the values for special algorithm
    double *v_special = new double[n+2];
    v_special = Special_Algorithm(x, f, h, n);   // Function from algorithms.cpp

    // Checking if third command line argument is given
    if (argv[3]){
        cout << "You have entered a third argument: Running LU" << endl;
        LU_Decomp_Arma(x, f, h, n);              // Function from algorithms.cpp
    } else if (!argv[3]){
        cout << "--------------"<< endl;
        cout << "Not running LU" << endl;
        cout << "--------------"<< endl;
        cout << "If you want to run LU decomposition enter an arbitrary third argument,\n"
                "but keep in mind that the program will crash at n = 10^5" << endl;
    }

    // Open file and write results to file:
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "         x:             u(x):         v(x):       v_special:   RelError_Gen:  RelError_Spec:" << endl;
    for (int i=0;i<=n+1;i++) {
      double RelativeError_S = log10(fabs((u[i]-v_special[i])/u[i]));  // Calculating the relative error for special case
      double RelativeError_G = log10(fabs((u[i]-v[i])/u[i]));          // Calculating the relative error for general case

       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << u[i];
       ofile << setw(15) << setprecision(8) << v[i];
       ofile << setw(15) << setprecision(8) << v_special[i];
       ofile << setw(15) << setprecision(8) << RelativeError_G;
       ofile << setw(15) << setprecision(8) << RelativeError_S << endl;
    }
    ofile.close();

    // Freeing the memory for arrays
    delete [] x;
    delete [] u;
    delete [] v;
    delete [] v_special;

    return 0;
}
