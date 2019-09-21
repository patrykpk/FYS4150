#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

mat Toeplitz(int n, double h){

    mat A = zeros<mat>(n,n);

    double Diagonal = 2.0/(h*h);
    double NonDiagonal = -1.0/(h*h);

    //Indexing the missing values at start and end
    //Since Diagonal contains one more value
    A(0,0) = Diagonal; A(0,1) = NonDiagonal;
    A(n-1,n-1) = Diagonal; A(n-1, n-2) = NonDiagonal;

    for (int i = 1; i < n-1; i++){
        A(i,i) = Diagonal;
        A(i,i-1) = NonDiagonal;
        A(i,i+1) = NonDiagonal;
    }
    return A;
}

mat Identity(int n){

    mat A = zeros<mat>(n,n);
    for (int i = 0; i<n; i++){
        A(i,i) = 1.0;
    }

    return A;
}

mat Toeplitz_2d(int n){

    mat A = zeros<mat>(n,n);



    vec rho(n);
    // start point;
    rho(0) = 0.0;
    // End point which is approximated to infinity
    rho(n-1) = 10.0;

    // Calculating the step size
    double h = (rho(n-1) - rho(0))/ (double) n;

    for (int i =1; i<n-2; i++)
    {
        rho(i) = i*h;

    }


    double Diagonal = 2.0/(h*h);
    double NonDiagonal = -1.0/(h*h);

    //Indexing the missing values at start and end
    //Since Diagonal contains one more value
    //A(0,0) = Diagonal; A(0,1) = NonDiagonal;
    A(n-1,n-1) = Diagonal+rho(n-2)*rho(n-2); A(n-1, n-2) = NonDiagonal;

    for (int i = 1; i < n-1; i++){
        A(i,i) = Diagonal + rho(i)*rho(i);
        A(i,i-1) = NonDiagonal;
        A(i,i+1) = NonDiagonal;
    }
    return A;
}
