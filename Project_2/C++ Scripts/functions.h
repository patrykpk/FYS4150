#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <armadillo>

using namespace arma;
using namespace std;

double offdiag(mat V, int *k, int *l, int n);
vec Eigenvalues(mat A, int n);
vec Analytical_Eigen(int n);

#endif // FUNCTIONS_H
