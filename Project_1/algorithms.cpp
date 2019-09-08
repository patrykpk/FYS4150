#include <iostream>
#include <algorithm>
#include <armadillo>
#include "time.h"
#include <fstream>
#include <iomanip>

using namespace arma;

void LU_Decomp_Arma(double *x, double (*f)(double), double h, int n){
    // This function uses Armadillo

    mat A = zeros<mat>(n,n);  //Creating a n x n matrix filled with zeros
    vec d_LU(n);              //Array on the right-hand side

    clock_t start, finish;

    // Setting up the matrix and the right-hand side vector with correct values
    A(0,0) = 2.0;  A(0,1) = -1;   d_LU(0) =  h*h*f(x[1]);
    d_LU(n-1) = h*h*f(x[n]);
    for (int i = 1; i < n-1; i++){
     d_LU(i) = h*h*f(x[i+1]);
     A(i,i-1)  = -1.0;
     A(i,i)    = 2.0;
     A(i,i+1)  = -1.0;
    }
    A(n-1,n-1) = 2.0; A(n-2,n-1) = -1.0; A(n-1,n-2) = -1.0;

    // Solving Av = d
    start = clock();     // Starting the timer
    vec v_LU  = solve(A,d_LU);
    finish = clock();    // Stopping the timer

    // Calculates time used for the loop
    double time_LU = (double) (finish - start)/(CLOCKS_PER_SEC);
    printf("--------------------------------------------------\n");
    printf("Performing LU required: %.8fs\n", time_LU);
    printf("--------------------------------------------------\n");
}


double *General_Algorithm(double *x, double (*f)(double), double h, int n){

    //Dynamic allocation of memory for arrays
    int *a = new int[n+1];        // Elements below the diagonal
    int *b = new int[n+1];        // Diagonal elements
    int *c = new int[n+1];        // Elements above the diagonal
    double *d = new double[n+1];  // Right-hand side

    double *b_tilde = new double[n+1];  // Updated diagonal elements
    double *d_tilde = new double[n+1];  // Vector on right hand side updated
    double *v = new double[n+2];        // Numerical solution

    // Setting up arrays
    for (int i=1; i<=n; i++) {
        d[i] = h*h*f(x[i]);
        b[i] = 2;
        a[i] = -1;
        c[i] = -1;
    }
    d[0] = 0;  //Filling in a spot for one value

    // Arrays below and above diagonal contain one less value
    c[n] = 0; // Overwriting the value
    a[1] = 0;


    clock_t start, finish;
    b_tilde[1] = b[1];
    d_tilde[1] = d[1];

    // Forward substitution - Row reduction
    start = clock();     // Starting the timer
    for (int i=2;i<=n;i++) {
       b_tilde[i] = b[i] - (a[i]*c[i-1])/b_tilde[i-1];       // Updating the diagonal elements
       d_tilde[i] = d[i]-(d_tilde[i-1]*a[i])/b_tilde[i-1];   // Updating the right hand side
    }

    v[0] = 0;    // Boundary condition
    v[n+1] = 0;  // Boundary condition
    v[n] = (d_tilde[n])/b_tilde[n];   // Precalculating

    // Backward substitution
    for (int i=n;i>1;i--) {
        v[i-1] = (d_tilde[i-1]-c[i-1]*v[i])/b_tilde[i-1];
    }

    finish = clock();  // Stopping the timer

    // Calculates time used for the loop
    double time_general = (double) (finish - start)/((double) CLOCKS_PER_SEC);
    printf("/////////////////////////////////////////////////////////////\n");
    printf("Checking time while performing general and special algorithm:\n");
    printf("/////////////////////////////////////////////////////////////\n");
    printf("\n");
    printf("--------------------------------------------------\n");
    printf("Performing general algorithm required: %.8fs\n", time_general);

    // Freeing the memory for arrays
    delete [] d;
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] d_tilde;

    return v;  // Returning the numerical solution

}

double *Special_Algorithm(double *x, double (*f)(double), double h, int n){

    double *b_special = new double[n+1]; // Diagonal elements
    double *v_special = new double[n+2]; // Numerical solution
    double *d = new double[n+1];         // Vector on the right hand side
    double *d_special = new double[n+1]; // Vector on right hand side updated
    clock_t start, finish;

    // Setting up the right hand side and diagonal elements
    for (int i = 1; i <= n; i++) {
        b_special[i] = (i+1.0)/((double) i);
        d[i] = h*h*f(x[i]);
    }
    v_special[0] = 0;      // Boundary condition
    v_special[n+1] = 0;    // Boundary condition
    d_special[1] = h*h*f(x[1]);

    //Updating the right hand side
    for (int i = 2; i <= n; i++) {
        d_special[i] = d[i] + ((i-1.0)*d_special[i-1])/((double) i);
   }

   v_special[n] = d_special[n]/b_special[n];  // Precalculated

   // Backward substitution
   start = clock();      // Starting the timer
   for (int i = n; i >= 2; i--) {
   v_special[i-1] = ((i-1.0)/((double)i)) * (d_special[i-1]+v_special[i]);
   }
   finish = clock();    // Stopping the timer

   // Calculates time used for the loop
   double time_special = (double) (finish - start)/((double) CLOCKS_PER_SEC);
   printf("Performing special algorithm required: %.8fs\n", time_special);
   printf("--------------------------------------------------\n");

   // Freeing the memory for arrays
   delete [] b_special;
   delete [] d_special;
   delete [] d;


   return v_special;  // Returning the numerical solution
}
