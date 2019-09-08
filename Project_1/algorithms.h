#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void LU_Decomp_Arma(double *x, double (*f)(double), double h, int n);
double *General_Algorithm(double *x, double (*f)(double), double h, int n);
double *Special_Algorithm(double *x, double (*f)(double), double h, int n);

#endif // ALGORITHMS_H
