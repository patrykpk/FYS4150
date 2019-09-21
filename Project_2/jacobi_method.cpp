#include <iostream>
#include <armadillo>
#include <cmath>

using namespace arma;

using namespace std;

mat Jacobi(mat V, mat W, int k, int l, int n){
    double sin, cos, tan, tau;
    if (V(k,l) != 0.0){
        tau = (V(l,l)-V(k,k))/(2*V(k,l));
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
        cos = 1.0;
        sin = 0.0;
    }
    double v_kk, v_ll, v_ik, v_il, w_ik, w_il;

    v_kk = V(k,k);
    v_ll = V(l,l);
    V(k,k) = cos*cos*v_kk-2.0*cos*sin*V(k,l) + sin*sin*v_ll;
    V(l,l) = sin*sin*v_kk+2.0*cos*sin*V(k,l) + cos*cos*v_ll;
    V(k,l) = 0.0;
    V(l,k) = 0.0;

    for (int i = 0; i < n; i++){
        if (i != k && i != l) {
            v_ik = V(i,k);
            v_il = V(i,l);
            V(i,k) = cos*v_ik-sin*v_il;
            V(k,i) = V(i,k);
            V(i,l) = cos*v_il+sin*v_ik;
            V(l,i) = V(i,l);
        }
        w_ik = W(i,k);
        w_il = W(i,l);

        W(i,k) = cos*w_ik - sin*w_il;
        W(i, l) = cos*w_il + sin*w_ik;
    }
    return V;

}


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

/*
double Generaloffdiag(mat A, int *k, int *l, int n){
    double max = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (j != i){
             double aij = fabs(A(i,j));
             if (aij > max){
                 max = aij; *k = i; *l = j;
             }
            }
        }
    }
    return max;
}

*/
