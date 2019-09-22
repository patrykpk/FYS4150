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
    string filename;
    int n;
    string method;
    double wr;
    double rho_max;
    if( argc <= 4 ){
      cout << "Error occured: " << argv[0] <<
          "\nread also output filename, n (int) and the method you want to run.\n\nRequires 4 arguments for QDot2:\nWhere the last \
argument is the frequency wr" << endl;
      exit(1);
    }
    else{
      filename = argv[1]; // first command line argument.
      n = atoi(argv[2]);  // second command line argument.
      rho_max = atof(argv[3]);
      method = argv[4];
    }


    if (argv[5]) {
        wr = atof(argv[5]);
    } else {
        wr = 0.0;
    }

    mat V;
    mat C;


    int k; int l;


    V = Toeplitz(n, rho_max, method, wr);
    //B.print();

    C = Identity(n);
    //offdiag(B, &k, &l, n);
    double tolerance = 1.0E-7;
    int iterations = 0;
    double max_off = offdiag(V, &k, &l, n);
    double max_iterations = n*n*n;

    // cout <<"Armadillo Eigenvalue: \n"<< eig_sym(V) << endl;

    while (max_off > tolerance && iterations <= max_iterations){
        max_off = offdiag(V, &k, &l, n);
        V = Jacobi(V, C, k, l, n);
        iterations++;
    }

    cout << "Number of iterations for Jacobi: " << iterations << endl;

    vec Eigenvalue = Eigenvalues(V,n);
    cout << "Eigenvalues: (Computed)\n";
    for (int i = 0; i<5; i++){
        cout << fixed << setprecision(4) << Eigenvalue(i) << endl;
    }

    //cout << iterations << endl;

    //cout << V << endl;

    /*
    cout << "K-value: " << k << endl;
    cout << "L-value: " << l << endl;
    */

    //cout << B.n_rows;


    //cout << (B) << endl;
}
