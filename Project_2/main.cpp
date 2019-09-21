#include <iostream>
#include <armadillo>
#include <cmath>

#include "jacobi_method.h"
#include "initializematrix.h"

using namespace std;
using namespace arma;

int main(int argc, char* argv[]){
    //Skrive hva h er og ikke hardcode den
    char *outfilename;
    int n;
    outfilename = argv[1];
    n = atoi(argv[2]);

    mat V;
    mat C;


    int k; int l;
    double h = 1.0/n;

    V = Toeplitz(n,h);
    //B.print();

    C = Identity(n);
    //offdiag(B, &k, &l, n);
    double tolerance = 1.0E-10;
    int iterations = 0;
    double max_off = offdiag(V, &k, &l, n);
    double max_iterations = n*n*n;

    cout <<"Armadillo Eigenvalue: \n"<< eig_sym(V) << endl;

    while (max_off > tolerance && iterations <= max_iterations){
        max_off = offdiag(V, &k, &l, n);
        V = Jacobi(V, C, k, l, n);
        iterations++;
    }

    vec Eigenvalue(n);

    for (int i = 0; i < n; i++){
        Eigenvalue(i) = V(i,i);
        //cout << "Eigenvalue " << i << " " << V(i,i) << endl;
    }
    Eigenvalue = sort(Eigenvalue);
    cout << "Egenverdier: \n" << Eigenvalue;

    //cout << iterations << endl;




    cout << "K-value: " << k << endl;
    cout << "L-value: " << l << endl;


    //cout << B.n_rows;


    //cout << (B) << endl;
}
