#define CATCH_CONFIG_MAIN
#include <iostream>
#include <armadillo>
#include <cmath>
#include <string>
#include <iomanip>
#include "Jacobi.h"
#include "initializematrix.h"
#include "functions.h"
#include "catch.hpp"
using namespace std;
using namespace arma;


TEST_CASE("Checking if offdiag finds the largest offdiagonal component."){

    int n = 5;
    int i, j;

    mat A;
    A << 1.0 << 0.5 << 2.7 << 9.0 << 0.8 << endr
      << 0.5 << 2.0 << 4.3 << 6.0 << 3.4 << endr
      << 2.7 << 4.3 << 3.0 << 9.3 << 1.7 << endr
      << 9.0 << 6.0 << 9.3 << 5.2 << 8.2 << endr
      << 0.8 << 3.4 << 1.7 << 8.2 << 9.9 << endr;

    double max;
    max = offdiag(A, &i, &j, n);

    CHECK ( max == 9.3 );
}

TEST_CASE("Chekcing if Jacobi method gives right eigenvalues."){

    int n = 50;
    double r = 1;
    string a = "buckling";
    int k, l;

    mat A = Toeplitz(n,r,a,0);
    mat I = Identity(n);

    double tolerance = 1.0E-10;
    int iterations = 0;
    double max_off = offdiag(A, &k, &l, n);
    double max_iterations = n*n*n;

    while (max_off > tolerance && iterations <= max_iterations){
        max_off = offdiag(A, &k, &l, n);
        A = Jacobi(A, I, k, l, n);
        iterations++;
    }

    vec ArmadilloEigenvalue(n);
    vec JacobiEigenvalue(n);

    for (int i = 0; i < n; i++){
        JacobiEigenvalue(i) = A(i,i);
        ArmadilloEigenvalue(i) = eig_sym(A)[i];
    }

    JacobiEigenvalue = sort(JacobiEigenvalue);
    vec Analytical_Eigenvalue = Analytical_Eigen(n);

    for (int i = 0; i < n; i++){
    CHECK (JacobiEigenvalue[i] == Approx(Analytical_Eigenvalue[i]));
    }
}
