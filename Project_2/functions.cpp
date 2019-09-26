#include <iostream>
#include <armadillo>
#include <cmath>

#include "functions.h"

using namespace std;
using namespace arma;

vec Analytical_Eigen(int n){
    double lambda;
    double h = 1.0/n;
    double a = -1.0/(h*h);
    double d = 2.0/(h*h);

    vec Analytical(n);
    double pi = 4*atan(1);
    for (int i = 1; i < n+1; i++){
        Analytical(i-1) = d + 2*a*cos(i*pi/(n+1));
    }
    return Analytical;

}

double offdiag(mat V, int *k, int *l, int n){
    double max;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            double aij = fabs(V(i,j));
            if (aij > max){
                 max = aij; *k = i; *l = j;
             }
            }
        }
    return max;
}

vec Eigenvalues(mat A, int n){
    vec Eigen(n);
    for (int i = 0; i < n; i++){
        Eigen(i) = A(i,i);
    }
    Eigen = sort(Eigen);

    return Eigen;

}


