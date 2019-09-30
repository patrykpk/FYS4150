#include <iostream>
#include <armadillo>
#include <cmath>

#include "functions.h"

using namespace std;
using namespace arma;

vec Analytical_Eigen(int n){
    double h = 1.0/n;            // Step length
    double a = -1.0/(h*h);       // Non-diagonal element
    double d = 2.0/(h*h);        // Diagonal element

    vec Analytical(n);           // Declaring a vector for storing the eigenvalues
    double pi = 4*atan(1);
    for (int i = 1; i < n+1; i++){
        Analytical(i-1) = d + 2*a*cos(i*pi/(n+1));  // Stores the analytical values in the vector
    }
    return Analytical;          // Returning the vector
}

//--------------------------------------------------------------------------------------------------------


double offdiag(mat V, int *k, int *l, int n){
    double max;                               // Declaring a variable

    for (int i = 0; i < n; i++){              // Looping through the upper triangular part of the matrix
        for (int j = i+1; j < n; j++){        // Checking the elements above diagonal only
            double aij = fabs(V(i,j));
            if (aij > max){
                 max = aij; *k = i; *l = j;  // Assigning the new maximum value and changing
                                             // the value of k and l
             }
        }
    }
    return max;                              // Returns the highest value for non-diagonal element
}

//--------------------------------------------------------------------------------------------------------

vec Eigenvalues(mat A, int n){
    vec Eigen(n);             // Declaring a vector with given size

    for (int i = 0; i < n; i++){
        Eigen(i) = A(i,i);    // Stores the diagonal elements in a matrix in a vector
    }
    Eigen = sort(Eigen);      // Sorting the eigenvalues

    return Eigen;             // Returning the vector containing eigenvealues

}

//--------------------------------------------------------------------------------------------------------

/* If you instead have a non-symmetric matrix and want to find the maximum
 * value for all non-diagonal elements (Not only upper triangular part) use
 * the function below instead.(It is commented out since it is not being used) */

/*
double Generaloffdiag(mat A, int *k, int *l, int n){
    double max;                                 // Declaring a variable

    for (int i = 0; i < n; i++){                // Looping through the whole matrix to find
        for (int j = 0; j < n; j++){            // the maximum value for non-diagonal elements
            if (j != i){
             double aij = fabs(A(i,j));
             if (aij > max){
                 max = aij; *k = i; *l = j;     // Assigning the new maximum value and changing
             }                                  // the value of k and l
            }
        }
    }
    return max;
}
*/

