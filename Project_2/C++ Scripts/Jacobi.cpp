#include <iostream>
#include <armadillo>
#include <cmath>

using namespace arma;
using namespace std;

mat Jacobi(mat V, mat W, int k, int l, int n){
    double sin, cos, tan, tau;      // Declaring variables

    if (V(k,l) != 0.0){                             // Checks if the element in matrix is different from 0
        tau = (V(l,l)-V(k,k))/(2*V(k,l));           // Defining the variable tau
        if (tau >= 0.0){
            tan = 1.0/(tau+sqrt(1.0+tau*tau));
        }
        else{
            tan = -1.0/(-tau+sqrt(1.0+tau*tau));
        }
        cos = 1.0/(sqrt(1.0+tan*tan));
        sin = cos*tan;
    }
    else{
        cos = 1.0;  // No transformation required if V(k,l) == 0
        sin = 0.0;  // No transformation required if V(k,l) == 0
    }
    double v_kk, v_ll, v_ik, v_il, w_ik, w_il;

    v_kk = V(k,k);      // Assigning the value from matrix to a new variable
    v_ll = V(l,l);      // Assigning the value from matrix to a new variable
    V(k,k) = cos*cos*v_kk-2.0*cos*sin*V(k,l) + sin*sin*v_ll;    // Result from similiarity transformation
    V(l,l) = sin*sin*v_kk+2.0*cos*sin*V(k,l) + cos*cos*v_ll;    // Result from similarity transformation
    V(k,l) = 0.0;       // Requiring this to be 0
    V(l,k) = 0.0;       // This aswell, due to the matrix being symmetric

    // Matrix elements changed due to similarity transformation
    for (int i = 0; i < n; i++){
        if (i != k && i != l) {
            v_ik = V(i,k);
            v_il = V(i,l);
            V(i,k) = cos*v_ik-sin*v_il;
            V(k,i) = V(i,k);    // Symmetric
            V(i,l) = cos*v_il+sin*v_ik;
            V(l,i) = V(i,l);    // Symmetric
        }
        w_ik = W(i,k);
        w_il = W(i,l);

        W(i,k) = cos*w_ik - sin*w_il;
        W(i, l) = cos*w_il + sin*w_ik;
    }
    return V;     // Returning the matrix after performing the transformation

}
