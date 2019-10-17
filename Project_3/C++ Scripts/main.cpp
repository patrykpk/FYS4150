#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
//#include <stdio.h>
//#include <stdlib.h>
#include <armadillo>

using namespace arma;

#include "Gauss_Quadrature.h"
#include "Coordinates.h"
#include "Monte_Carlo.h"

using namespace std;


int main()
{
    int n;
    double a, b;
    cout << "Read in the number of integration points" << endl;
    cin >> n;
    cout << "Read in integration limits" << endl;
    cin >> a >> b;

    double *x = new double [n];
    double *w = new double [n];

    gauleg(a, b, x, w, n);

    //double Arma_Random = randu(1);


    double int_gauss = 0.0;
    double iterations = 0.0;
    for ( int i = 0;  i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                for (int l = 0; l < n; l++){
                    for (int p = 0; p < n; p++){
                        for (int q = 0; q < n; q++){
                            int_gauss+=w[i]*w[j]*w[k]*w[l]*w[p]*w[q]*Cartesian_Function(x[i],x[j],x[k],x[l],x[p],x[q]);
                            iterations++;
                        }
                    }
                }
            }

        }
    }
    cout << "Iterations: " << iterations << endl;
    cout  << setiosflags(ios::showpoint | ios::uppercase);
    cout << "Gaussian-Legendre quad = "<< setw(20) << setprecision(15)  << int_gauss << endl;


    cout << "Monte carlo methods enter:" << endl;
    int N;
    double A, B;
    cout << "Read in the number of integration points" << endl;
    cin >> N;
    cout << "Read in integration limits" << endl;
    cin >> A >> B;

    MC(A, B, N);


    cout << "Test of random number generator ran0  " << endl;
    int M;
    cout << "Read in the number of integration points" << endl;
    cin >> M;
    Test(M);
}  // end of main program










//   reserve space in memory for vectors containing the mesh points
//   weights and function values for the use of the gauss-legendre
//   method
// Gauss-Laguerre is old-fashioned translation of F77 --> C++
// arrays start at 1 and end at n
//double *xgl = new double [n+1];
//double *wgl = new double [n+1];
// These arrays are used for improved Gauss-Legendre, mapping of
// x \in [-1,1] to x \in [0, infinity)
//double *r = new double [n];
//double *s = new double [n];
//   set up the mesh points and weights
