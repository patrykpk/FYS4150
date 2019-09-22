#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>

#include "jacobi_method.h"
#include "initializematrix.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[]){
    string filename = argv[1];
    int n = atoi(argv[2]);
    string method = argv[3];

    if (argv[4]) {
        double wr = atof(argv[4]);
    } else {
        double wr = 0.0;
    }

    mat V;
    mat C;


    int k; int l;


    V = Toeplitz(n, 10.0, method, wr);
    //B.print();

    C = Identity(n);
    //offdiag(B, &k, &l, n);
    double tolerance = 1.0E-10;
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

    vec Eigenvalue(n);

    for (int i = 0; i < n; i++){
        Eigenvalue(i) = V(i,i);
        //cout << "Eigenvalue " << i << " " << V(i,i) << endl;
    }
    Eigenvalue = sort(Eigenvalue);

    for (int i = 0; i <= 4; i++){
        cout <<"Eigenvalue " << i << " " << Eigenvalue[i]/2.0 << endl;
    }


    //cout << iterations << endl;

    //cout << V << endl;


    cout << "K-value: " << k << endl;
    cout << "L-value: " << l << endl;


    //cout << B.n_rows;


    //cout << (B) << endl;
}
