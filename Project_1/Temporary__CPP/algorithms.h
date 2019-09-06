#ifndef ALGORITHMS_H
#define ALGORITHMS_H

void LU_Decomp_Arma(double *x, double (*f)(double), double h, int n);
void General_Algorithm(double *x, double (*f)(double), int *a, int *b, int *c, double *d, double *d_tilde, double *b_tilde, double *v, double h, int n);
void Special_Algorithm(double *x, double (*f)(double), double *d, double *b_special, double *v_special, double *f_special, double h, int n);

#endif // ALGORITHMS_H

