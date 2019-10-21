#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
#include <string>

#include "lib.h"
#include "CoordinateSystem.h"
#include "GaussianQuadrature.h"

ofstream ofile;

using namespace std;

//----------------------------------------------------------------------------------------------------------------------
// Gaussian-Legendre quadrature
//----------------------------------------------------------------------------------------------------------------------
void GQ_legendre(double a, double b, int N, double& int_legendre, double& Legendre_time, bool WriteToFile){
    clock_t start_legendre, finish_legendre;
    string Method = "Gaussian-Legendre quadrature";

    // Defining pointers: mesh-point and weights
    double *x = new double [N];
    double *w = new double [N];

    // Calling the function which calculates the mesh-points and weights in Gaussian-Legendre
    gauss_legendre(a, b, x, w, N);

    //Summation over all six variables, where the sum is stored in int_leg
    double int_leg = 0.0;                    // Initializing the integral
    double iterations = 0.0;                 // Intiializing the iteration count
    start_legendre = clock();                // Starts counting

    for ( int i = 0;  i < N; i++){                      // x1
        for (int j = 0; j < N; j++){                    // y1
            for (int k = 0; k < N; k++){                // z1
                for (int l = 0; l < N; l++){            // x2
                    for (int p = 0; p < N; p++){        // y2
                        for (int q = 0; q < N; q++){    // z2
                            double Weights = w[i]*w[j]*w[k]*w[l]*w[p]*w[q];                       // Weights for corresponding dimension
                            int_leg+=Weights*Cartesian_Function(x[i],x[j],x[k],x[l],x[p],x[q]);   // Evaluating the integral
                            iterations++;
                        }
                    }
                }
            }
        }
    }
    finish_legendre = clock();              // Stops counting

    Legendre_time = (double) (finish_legendre - start_legendre)/(CLOCKS_PER_SEC);    // Calculates timed used
    int_legendre = int_leg;

    // Checks if the output should be written to file
    if (WriteToFile == false){
        OutputToTerminalGQ(Method, N, int_legendre, Legendre_time);
    }

    delete [] x;
    delete [] w;
}
// End integration loop Legendre


//----------------------------------------------------------------------------------------------------------------------
// Gaussian-Laguerre quadrature
//----------------------------------------------------------------------------------------------------------------------
void GQ_laguerre(int N, double PI, double& int_laguerre, double& Laguerre_time, bool WriteToFile){

    string Method = "Gauss-Laguerre Quadrature";
    clock_t start_laguerre, finish_laguerre;

    // Defining various pointers: mesh-points and weights for three variables.
    double *R_Gauss_Laguerre = new double [N+1];
    double *Weights_Gauss_Laguerre = new double [N+1];

    double *Theta = new double[N];
    double *Weights_Theta = new double [N];

    double *Phi = new double [N];
    double *Weights_Phi = new double [N];

    // Choosing Alpha = 2.0, we are then left with a factor of (1024)^-1
    double alf = 2.0;
    double norm = 1.0/1024;

    // Calling the function which calculates the mesh-points and weights in Gaussian-Laguerre
    gauss_laguerre(R_Gauss_Laguerre, Weights_Gauss_Laguerre, N, alf);

    // Calling the function which calculates the mesh-points and weights in Gaussian-Legendre
    gauss_legendre(0, PI, Theta, Weights_Theta, N);
    gauss_legendre(0, 2*PI, Phi, Weights_Phi, N);

    // Summation over all six variables, where the sum is stored in int_lag
    double int_lag = 0.0;
    double iterations_Laguerre = 0.0;

    start_laguerre = clock();       // Starts counting

    for ( int i = 1;  i <= N; i++){                      // r1
        for (int j = 1; j <= N; j++){                    // r2
            for (int k = 0; k < N; k++){                 // theta1
                for (int l = 0; l < N; l++){             // theta2
                    for (int p = 0; p < N; p++){         // phi1
                        for (int q = 0; q < N; q++){     // phi2
                            double weights = Weights_Gauss_Laguerre[i]*Weights_Gauss_Laguerre[j]*Weights_Theta[k]*Weights_Theta[l]*Weights_Phi[p]*Weights_Phi[q];
                            int_lag += weights*Spherical_Function(R_Gauss_Laguerre[i],R_Gauss_Laguerre[j],Theta[k], Theta[l], Phi[p], Phi[q]); // Evaluating the integral
                            iterations_Laguerre++;
                        }
                    }
                }
            }
        }
    }
    finish_laguerre = clock();    // Stops counting
    Laguerre_time = (double) (finish_laguerre - start_laguerre)/(CLOCKS_PER_SEC);       // Evaluates the time used
    int_lag *= norm;
    int_laguerre = int_lag;

    // Checks if the output should be written to file
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
// End integration loop Laguerre

void OutputToTerminalGQ(string Method, int n, double Integral_Value, double Time_Used){
    const double PI = atan(1.0)*4;
    double Exact_value = (5*pow(PI,2))/(256);
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Running "<< Method << endl;
    cout  << setiosflags(ios::showpoint | ios::uppercase);
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Gaussian-Legendre quadrature = "<< setw(20) << setprecision(15)  << Integral_Value << endl;
    cout << "CPU-time for N = " << n << ":" << setw(20) << setprecision(15)  << Time_Used << endl;
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Excact result = "<< Exact_value << endl;
    cout << "------------------------------------------------------------------------------ " << endl;
}

void OutputToFile(double a, double b, int n, string outfilename){
    const double PI = atan(1.0)*4;
    double Exact_value = (5*pow(PI,2))/(256);

    bool WriteToFile = true;

    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Running Legendre and Laguerre"<< endl;
    cout  << setiosflags(ios::showpoint | ios::uppercase);
    cout << "------------------------------------------------------------------------------ " << endl;

    // Open file and write results to file:
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "|   N:  |  Legendre:    |  CPU-time Legendre:    | Relative error Legendre: |   Laguerre:  | CPU-time Laguerre | Relative error Laguerre: |  Excact result: |" << endl;
    ofile << "|       |               |                        |                          |              |                   |                          |                 |" << endl;

    //Looping through different iteration values of N
    for(int N = 1; N <= n ; N++){

        double int_legendre, Legendre_time;
        GQ_legendre(a, b, N, int_legendre, Legendre_time, WriteToFile);

        double int_laguerre,Laguerre_time;
        GQ_laguerre(N,PI, int_laguerre, Laguerre_time, WriteToFile);


        //----------------------------------------------------------------------------------------------------------------------
        // Calculating the relative error
        double relative_error_leg = fabs((Exact_value - int_legendre)/Exact_value);
        double relative_error_lag = fabs((Exact_value - int_laguerre)/Exact_value);
        //----------------------------------------------------------------------------------------------------------------------

        cout << N << endl;

        //Writing results in file.
        ofile << setw(5) << N;
        ofile << setw(18) << setprecision(8) << int_legendre;
        ofile << setw(20) << setprecision(8) << Legendre_time;
        ofile << setw(23) << setprecision(8) << relative_error_leg;
        ofile << setw(22) << setprecision(8) << int_laguerre;
        ofile << setw(20) << setprecision(8) << Laguerre_time;
        ofile << setw(23) << setprecision(8) << relative_error_lag;
        ofile << setw(22) << setprecision(8) << Exact_value << endl;

    }
    // Loop ended
    ofile.close();
}




//----------------------------------------------------------------------------------------------------------------------
// //Checking for valid integration limits [Lambda], is manipulated by adjusting ZERO.
//----------------------------------------------------------------------------------------------------------------------
double integration_limit(){
    int l, i, j, k;
    double int_limit = 0;
    for (l = 1;  l < 100; l++){
        for (i = 0;  i < l; i++){
            for (j = 0; j < l; j++){
                for (k = 0; k < l; k++){
                    int_limit = integration_limit(i,j,k);
                    }
                }
            }
    //If the exponetial value is lower than the defined zero
    //we set the integration limit, as well as breaking the loop
    if (int_limit < 10e-4){
        //cout << i << endl << j << endl << k << endl;
        double h = sqrt(i*i + j*j+ k*k);
        cout <<  "Integration limits can be set to:" << "["<< setprecision(1)  << -h <<","<< setprecision(1)  << h << "]" << endl;
        break;}
    }
    return int_limit;
}




// End integration loop for finding limit



