#ifndef INITIALIZEMATRIX_H
#define INITIALIZEMATRIX_H

#include <iostream>
#include <armadillo>

using namespace arma;

mat Toeplitz(int n, double h);
mat Identity(int n);

#endif // INITIALIZEMATRIX_H
