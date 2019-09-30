#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>
#include <iomanip>

#include "Jacobi.h"              /* Contains: Jacobi() */
#include "initializematrix.h"    /* Contains: Identity() and Toeplitz() */
#include "functions.h"           /* Contains: offdiag(), Eigenvalues() and Analytical_Eigen */

using namespace std;
using namespace arma;

// Main program reads in the dimensions of matrix (n), rho_max, method and frequency wr (Omega) for the last method.
int main(int argc, char* argv[]){

    // Declaration of output filename and writing to file
    string fileout;
    ofstream ofile;

    // Declaration of command line arguments
    int n;
    string method;
    double wr;
    double rho_max;

    // Checking if enough command line arguments are given, otherwise interrupts the execution of this script
    if( argc <= 3 ){
      cout << "Error occured: " << argv[0] <<
          "\nRequires the dimension of matrix (n), rho_max and frequency wr (Omega) as input to run.\n\n\
            Requires 4 arguments for QDot2:\n\
            Where the last argument is the frequency wr" << endl;
      exit(1);
    }
    else{
      n = atoi(argv[1]);            // First command line argument
      rho_max = atof(argv[2]);      // Second command line argument
      method = argv[3];             // Third command line argument
    }

    if (argv[4]){                   // Checking if fourth argument is given
        wr = atof(argv[4]);
    } else {
        wr = 0.0;                   // Default value if no fourth argument is given
    }

    // Declaring two matrices
    mat V;
    mat C;

    // Decalring two integers
    int k; int l;

    V = Toeplitz(n, rho_max, method, wr);  // Initizaling a Toeplitz matrix

    // Declaring the timer
    clock_t start, finish;

    start = clock();                      // Counting time
    eig_sym(V);                           // Eigenvalues of the given matrix (Armadillo)
    finish = clock();                     // Stops counting

    // Time used to diagonalize the matrix using Armadillo
    double Arma_Time = (double) (finish - start)/(CLOCKS_PER_SEC);

    //Initializing identity matrix
    C = Identity(n);

    double tolerance = 1.0E-10;               // Tolerance for off-diagonal elements in matrix (Used in Jacobi)
    int iterations = 0;                       // Iterations for diagonaliztion
    double max_off = offdiag(V, &k, &l, n);   // Finds the maximum value of a non-diagonal element in matrix
                                              // and assigns the element to k and l

    double max_iterations = n*n*n;            // Limit for iterations

    start = clock();      // Counting time
    while (max_off > tolerance && iterations <= max_iterations){
        max_off = offdiag(V, &k, &l, n);    // Finds new max value for non-diagonal element
        V = Jacobi(V, C, k, l, n);          // Performs Jacobi
        iterations++;                       // Keeps track of iterations used
    }
    finish = clock();    // Stops counting

    // Time used to achieve diagonal matrix
    double Jacobi_Time = (double) (finish - start)/(CLOCKS_PER_SEC);

    // Writing out the amount of iterations to the terminal
    cout << "Number of iterations for Jacobi: " << iterations << endl;

    vec Eigenvalue = Eigenvalues(V,n);     // Extracting the diagonal elements from matrix (Eigenvalues) Found in functions.cpp
    cout << "Eigenvalues: (Computed)\n";
    for (int i = 0; i<4; i++){             // Writing out the first 4 eigenvalues to terminal
        cout << fixed << setprecision(4) << Eigenvalue(i) << endl;
    }

    //--------------------------------------------------------------------------------------------------------------------------
    /* This section is for the output of files. Choosing the name for output and the content of the file based on method */

    // Chooses the output filename based on method and other important input
    fileout = method + "_";
    string Add_String;

    if (method == "buckling" || method == "qdot1"){
        Add_String = to_string(n) + ".txt";
    }
    else if (method == "qdot2"){
        if (rho_max < 10){
            Add_String = to_string(n) + "_rho_max_" + "0" + to_string(int(rho_max)) + "_wr_" + to_string(wr) + ".txt";
        }
        else {
            Add_String = to_string(n) + "_rho_max_" + to_string(int(rho_max)) + "_wr_" + to_string(wr) + ".txt";
        }
    }
    fileout.append(Add_String);

    // Writing to all files regardless of method used
    ofile.open(fileout);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Method used: " << method << endl;
    ofile << "Dimension: " << n << endl;
    ofile << "Tolerance used: " << tolerance << endl;

    // Different output based on method used
    if (method == "buckling"){
        vec Analytical = Analytical_Eigen(n);    // Assigns the analytical values to a vector

        ofile << setw(10) << setprecision(4) << "Number of iterations for Jacobi: " << iterations << endl;
        ofile << setw(10) << setprecision(8) << "Time used for Jacobi: " << Jacobi_Time << endl;
        ofile << setw(10) << setprecision(8) << "Time used for Armadillo: " << Arma_Time << "\n\n";
        ofile << "|      Analytical        |       Computed        |   Relative Error:   \n";
        for (int i = 0; i < n; i++){
            double RelativeError = (fabs((Analytical(i)-Eigenvalue(i))/Analytical(i)));
            ofile << setw(20) << setprecision(8) << Analytical(i);
            ofile << setw(20) << setprecision(8) << Eigenvalue(i);
            ofile << setw(20) << setprecision(4) << RelativeError << endl;
        }


    }
    else if (method == "qdot1") {
        ofile << "Rho_max: " << rho_max << "\n\n";
        vec Analytical;
        Analytical << 3 << 7 << 11 << 15 << endr;
        ofile << "|     Analytical      |       Computed        |       Absolute Error      |\n";
        for (int i = 0; i < Analytical.size(); i++){
            double Check_Leading_Digits = fabs(Analytical(i)-Eigenvalue(i));
            ofile << setw(20) << setprecision(8) << Analytical(i);
            ofile << setw(20) << setprecision(8) << Eigenvalue(i);
            ofile << setw(20) << setprecision(4) << Check_Leading_Digits << endl;
        }

    }
    else if (method == "qdot2") {
        ofile << "Rho_max: " << rho_max << endl;
        ofile << "Frequency wr: " << wr << endl;
        ofile << "Groundstate Eigenvalue: " << setprecision(8) << Eigenvalue(0) << endl;
    }
    ofile.close();
}
