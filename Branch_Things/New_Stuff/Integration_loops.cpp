#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
#include <string>
//#include <stdio.h>
//#include <stdlib.h>

#include "legendre.h"
#include "Laguerre.h"
#include "repulsion_function.h"


using namespace std;

//----------------------------------------------------------------------------------------------------------------------
// Gaussian-Legendre quadrature
//----------------------------------------------------------------------------------------------------------------------
void GQ_legendre(double a, double b, int N, double& int_legendre, double& Legendre_time, bool WriteToFile){
    clock_t start_legendre, finish_legendre;
    string Method = "Gaussian-Legendre quadrature";
    //Defining pointers: mesh-point and weights
    double *x = new double [N];
    double *w = new double [N];

    //Calling the function which calculates the mesh-points and weights in Gaussian-Legendre
    gauss_legendre(a, b, x, w, N);

    //Summation over all six variables, where the sum is stores in int_gauss
    double int_leg = 0.0;
    double iterations = 0.0;
    start_legendre = clock();                    //Starts counting
    for ( int i = 0;  i < N; i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                for (int l = 0; l < N; l++){
                    for (int p = 0; p < N; p++){
                        for (int q = 0; q < N; q++){
                            int_leg+=w[i]*w[j]*w[k]*w[l]*w[p]*w[q]*Cartesian_Function(x[i],x[j],x[k],x[l],x[p],x[q]);
                            iterations++;
                        }
                    }
                }
            }
        }
    }
    finish_legendre = clock();                   // Stops counting

    Legendre_time = (double) (finish_legendre - start_legendre)/(CLOCKS_PER_SEC); // Stops counting
    int_legendre = int_leg;

    if (WriteToFile == false){
        OutputToTerminalGQ(Method, N, int_legendre, Legendre_time);
    }

    delete [] x;
    delete [] w;
}
// End integration loop legendre


//----------------------------------------------------------------------------------------------------------------------
// Gaussian-Laguerre quadrature
//----------------------------------------------------------------------------------------------------------------------
void GQ_laguerre(int N, double PI, double& int_laguerre, double& Laguerre_time, bool WriteToFile){

    string Method = "Gauss-Laguerre Quadrature";
    clock_t start_laguerre, finish_laguerre;

    //Defining various pointers: mesh-points and weights for three variables.
    double *R_Gauss_Laguerre = new double [N+1];
    double *Weights_Gauss_Laguerre = new double [N+1];

    double *Theta = new double[N];
    double *Weights_Theta = new double [N];

    double *Phi = new double [N];
    double *Weights_Phi = new double [N];

    //Choosing alpha=2.0, we are then left with a factor of (1024)^-1
    double alf = 2.0;
    double norm = 1.0/1024;

    //Calling the function which calculates the mesh-points and weights in Gaussian-Laguerre
    gauss_laguerre(R_Gauss_Laguerre, Weights_Gauss_Laguerre, N, alf);
    //Calling the function which calculates the mesh-points and weights in Gaussian-Legendre
    gauss_legendre(0, PI, Theta, Weights_Theta, N);
    gauss_legendre(0, 2*PI, Phi, Weights_Phi, N);

    //Summation over all six variables, where the sum is stores in int_gausslag
    double int_lag = 0.0;
    double iterations_Laguerre = 0.0;
    start_laguerre = clock();
    for ( int i = 1;  i <= N; i++){                      // r1
        for (int j = 1; j <= N; j++){                    // r2
            for (int k = 0; k < N; k++){                 // Kun de to første som skal gå fra 1 til n?
                for (int l = 0; l < N; l++){
                    for (int p = 0; p < N; p++){
                        for (int q = 0; q < N; q++){
                            double weights = Weights_Gauss_Laguerre[i]*Weights_Gauss_Laguerre[j]*Weights_Theta[k]*Weights_Theta[l]*Weights_Phi[p]*Weights_Phi[q];
                            int_lag += weights*Spherical_Function(R_Gauss_Laguerre[i],R_Gauss_Laguerre[j],Theta[k], Theta[l], Phi[p], Phi[q]); //Spherical_Coordinates()*Weights for de forskjellige koordinatene//*sin(xgl[i]);
                            iterations_Laguerre++;
                        }
                    }
                }
            }
        }
    }
    finish_laguerre = clock();
    Laguerre_time = (double) (finish_laguerre - start_laguerre)/(CLOCKS_PER_SEC); // Stops counting
    int_lag *= norm;
    int_laguerre = int_lag;

    if (WriteToFile == false){
        OutputToTerminalGQ(Method, N, int_laguerre, Laguerre_time);
    }


    delete [] R_Gauss_Laguerre;
    delete [] Weights_Gauss_Laguerre;
    delete [] Theta;
    delete [] Weights_Theta;
    delete [] Phi;
    delete [] Weights_Phi;


}
// End integration loop laguerre


//----------------------------------------------------------------------------------------------------------------------
// //Checking for valid integration limits [Lambda], is manipulated by adjusting ZERO.
//----------------------------------------------------------------------------------------------------------------------
double integration_limit(){
    int c;
    double int_limit = 0;
    for (int l = 1;  l < 100; l++){
        c = l;
        for ( int i = 0;  i < c; i++){
            for (int j = 0; j < c; j++){
                for (int k = 0; k < c; k++){
                    int_limit = integration_limit(i,j,k);
                    }
                }
            }
    //If the exponetial value is lower than the defined zero
    //we set the integration limit, as well as breaking the loop
    if (int_limit < 10e-5){
        double h = sqrt(c*c + c*c+ c*c);
        cout <<  "Integration limits can be set to:" << "["<< setprecision(1)  << -h <<","<< setprecision(1)  << h << "]" << endl;
        break;}
    }
    //cout << "Value of exponential = "<< setw(20) << setprecision(15)  << int_limit << endl;
    return int_limit;
}
// End integration loop for finding limit


/*
double integration_limit(){
    int c;

    int l, i, j, k;

    double int_limit = 0;
    for (l = 1;  l < 100; l++){
        c = l;
        for (i = 0;  i < c; i++){
            for (j = 0; j < c; j++){
                for (k = 0; k < c; k++){
                    int_limit = integration_limit(i,j,k);
                    }
                }
            }
    //If the exponetial value is lower than the defined zero
    //we set the integration limit, as well as breaking the loop
    if (int_limit < 10e-4){
        cout << i << endl << j << endl << k << endl;
        double h = sqrt(i*i + j*j+ k*k);
        cout <<  "Integration limits can be set to:" << "["<< setprecision(1)  << -h <<","<< setprecision(1)  << h << "]" << endl;
        break;}
    }
    //cout << "Value of exponential = "<< setw(20) << setprecision(15)  << int_limit << endl;
    return int_limit;
}
*/
