#ifndef INITIALIZEMATRIX_H
#define INITIALIZEMATRIX_H

#include <iostream>
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

mat Identity(int n);
mat Toeplitz(int n, double rho_max, string method, double wr);
#endif // INITIALIZEMATRIX_H
