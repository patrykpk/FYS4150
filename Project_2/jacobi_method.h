#ifndef JACOBI_METHOD_H
#define JACOBI_METHOD_H

#include <iostream>
#include <armadillo>


using namespace arma;

mat Jacobi(mat V, mat W, int k, int l, int n);
double offdiag(mat V, int *k, int *l, int n);

#endif // JACOBI_METHOD_H
