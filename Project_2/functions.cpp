#include <iostream>
#include <armadillo>
#include <cmath>

#include "functions.h"

using namespace std;
using namespace arma;


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
