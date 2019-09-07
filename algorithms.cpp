#include <iostream>
#include <algorithm>
#include <armadillo>
#include "time.h"
#include <fstream>
#include <iomanip>

using namespace arma;

void LU_Decomp_Arma(double *x, double (*f)(double), double h, int n){

    mat A = zeros<mat>(n,n);
    vec d_LU(n);

    clock_t start, finish;
    A(0,0) = 2.0;  A(0,1) = -1;   d_LU(0) =  h*h*f(x[1]);
    d_LU(n-1) = h*h*f(x[n]);
    for (int i = 1; i < n-1; i++){
     d_LU(i) = h*h*f(x[i+1]);
     A(i,i-1)  = -1.0;
     A(i,i)    = 2.0;
     A(i,i+1)  = -1.0;
    }
    A(n-1,n-1) = 2.0; A(n-2,n-1) = -1.0; A(n-1,n-2) = -1.0;

    // solve Av = d
    start = clock();
    vec v_LU  = solve(A,d_LU);
    finish = clock();

    double time_LU = (double) (finish - start)/(CLOCKS_PER_SEC);
    printf("--------------------------------------------------\n");
    printf("Performing LU required: %.8fs\n", time_LU);
    printf("--------------------------------------------------\n");
}


void General_Algorithm(double *x, double (*f)(double), int *a, int *b, int *c, double *d, double *d_tilde, double *b_tilde, double *v, double h, int n){
    for (int i=1; i<=n; i++) {
        d[i] = h*h*f(x[i]);
        b[i] = 2;
        a[i] = -1;
        c[i] = -1;
    }
    d[0] = 0;
    c[n] = 0;
    a[1] = 0;


    clock_t start, finish;
    b_tilde[1] = b[1];
    d_tilde[1] = d[1];
    start = clock();
    for (int i=2;i<=n;i++) {
       b_tilde[i] = b[i] - (a[i]*c[i-1])/b_tilde[i-1];
       d_tilde[i] = d[i]-(d_tilde[i-1]*a[i])/b_tilde[i-1];
    }

    v[n] = (d_tilde[n])/b_tilde[n];
    v[0] = 0;
    for (int i=n;i>1;i--) {
        v[i-1] = (d_tilde[i-1]-c[i-1]*v[i])/b_tilde[i-1];
    }

    finish = clock();
    double time_general = (double) (finish - start)/((double) CLOCKS_PER_SEC);
    printf("/////////////////////////////////////////////////////////////\n");
    printf("Checking time while performing general and special algorithm:\n");
    printf("/////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("Performing general algorithm required: %.8fs\n", time_general);

}

void Special_Algorithm(double *x, double (*f)(double), double *d, double *b_special, double *v_special, double *f_special, double h, int n){
    clock_t start, finish;
    for (int i = 1; i <= n; i++) {
        b_special[i] = (i+1.0)/((double) i);
    }
    v_special[0] = 0;
    f_special[1] = h*h*f(x[1]);
    start = clock();
    for (int i = 2; i <= n; i++) {
        f_special[i] = d[i] + ((i-1.0)*f_special[i-1])/((double) i);
    }

   v_special[n] = f_special[n]/b_special[n];
   for (int i = n; i >= 2; i--) {
   v_special[i-1] = ((i-1.0)/((double)i)) * (f_special[i-1]+v_special[i]);
   }

   finish = clock();
   double time_special = (double) (finish - start)/((double) CLOCKS_PER_SEC);
   printf("Performing special algorithm required: %.8fs\n", time_special);
   printf("--------------------------------------------------\n");

}
