#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>
#include <iomanip>

#include "Jacobi.h"
#include "initializematrix.h"
#include "functions.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[]){
    //Command line arguments
    //string filename;

    clock_t start, finish;
    string fileout;
    ofstream ofile;
    int n;
    string method;
    double wr;
    double rho_max;
    if( argc <= 3 ){
      cout << "Error occured: " << argv[0] <<
          "\nread also output filename, n (int) and the method you want to run.\n\nRequires 4 arguments for QDot2:\nWhere the last \
argument is the frequency wr" << endl;
      exit(1);
    }
    else{
      //filename = argv[1]; // first command line argument.
      n = atoi(argv[1]);  // second command line argument.
      rho_max = atof(argv[2]);
      method = argv[3];
    }


    if (argv[4]) {
        wr = atof(argv[4]);
    } else {
        wr = 0.0;
    }


    mat V;
    mat C;



    int k; int l;



    V = Toeplitz(n, rho_max, method, wr);


    start = clock();
    eig_sym(V);
    finish = clock();
    double Arma_Time = (double) (finish - start)/(CLOCKS_PER_SEC);

    //B.print();

    C = Identity(n);
    //offdiag(B, &k, &l, n);
    double tolerance = 1.0E-10;


    int iterations = 0;
    double max_off = offdiag(V, &k, &l, n);
    double max_iterations = n*n*n;

    // cout <<"Armadillo Eigenvalue: \n"<< eig_sym(V) << endl;


    start = clock();
    while (max_off > tolerance && iterations <= max_iterations){
        max_off = offdiag(V, &k, &l, n);
        V = Jacobi(V, C, k, l, n);
        iterations++;
    }
    finish = clock();
    double Jacobi_Time = (double) (finish - start)/(CLOCKS_PER_SEC);


    cout << "Number of iterations for Jacobi: " << iterations << endl;

    vec Eigenvalue = Eigenvalues(V,n); //Extracting the diagonal elements from matrix (Eigenvalues) Found in functions.cpp
    cout << "Eigenvalues: (Computed)\n";
    for (int i = 0; i<4; i++){
        cout << fixed << setprecision(4) << Eigenvalue(i) << endl;
    }


    fileout = method + "_";
    string Add_String;
    if (method == "buckling" || method == "qdot1"){
        Add_String = to_string(n) + ".txt";
    }
    else if (method == "qdot2"){
        Add_String = to_string(n) + "_rho_max_" + to_string(int(rho_max)) + "_wr_" + to_string(wr) + ".txt";
    }
    //string Add_String = to_string(n) + ".txt";
    fileout.append(Add_String);


    ofile.open(fileout);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Method used: " << method << endl;
    ofile << "Dimension: " << n << endl;
    ofile << "Tolerance used: " << tolerance << endl;
    if (method == "buckling"){
        vec Analytical = Analytical_Eigen(n);

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
            //double RelativeError = (fabs((Analytical(i)-Eigenvalue(i))/Analytical(i)));
            double Check_Leading_Digits = fabs(Analytical(i)-Eigenvalue(i));
            ofile << setw(20) << setprecision(8) << Analytical(i);
            ofile << setw(20) << setprecision(8) << Eigenvalue(i);
            ofile << setw(20) << setprecision(4) << Check_Leading_Digits << endl;
        }

    }
    else if (method == "qdot2") {
        ofile << "Rho_max: " << rho_max;;
        ofile << "Frequency wr: " << wr << "\n";
        ofile << "Groundstate Eigenvalue: " << setprecision(8) << Eigenvalue(0) << endl;
    }
    ofile.close();
}
