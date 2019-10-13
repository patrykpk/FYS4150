#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
//#include <stdio.h>
//#include <stdlib.h>

#include "legendre.h"
#include "repulsion_function.h"
#include "laguerre.h"
#include "monte_carlo.h"

using namespace std;


int main()
{
    int n;
    double a, b;
    cout << "Read in the number of integration points" << endl;
    cin >> n;
    cout << "Read in integration limits" << endl;
    cin >> a >> b;

    double const  pi = 4*atan(1);




    //-----------------------------------------------------------------------------------------------------------------------
    // Legendre
    // Putte det her inn i en egen function
    //
    /*



    double *x = new double [n];
    double *w = new double [n];

    gauleg(a, b, x, w, n);


    //for (int i = 0; i < n; i++){
    //    cout << w[i] << endl;
    //}



    double int_gauss = 0.0;
    double iterations_Legendre = 0.0;
    for ( int i = 0;  i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                for (int l = 0; l < n; l++){
                    for (int p = 0; p < n; p++){
                        for (int q = 0; q < n; q++){
                            int_gauss+=w[i]*w[j]*w[k]*w[l]*w[p]*w[q]*Cartesian_Function(x[i],x[j],x[k],x[l],x[p],x[q]);
                            iterations_Legendre++;
                        }
                    }
                }
            }

        }
    }
    */


    //-----------------------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------------------------
    // Laguerre


    /*

    double *R_Gauss_Laguerre = new double [n+1];
    double *Weights_Gauss_Laguerre = new double [n+1];

    double *Theta = new double[n];
    double *Weights_Theta = new double [n];

    double *Phi = new double [n];
    double *Weights_Phi = new double [n];

    double alpha = 0.0;
    gauss_laguerre(R_Gauss_Laguerre, Weights_Gauss_Laguerre, n, alpha);   // Vektene for r_1 og r_2 og den tilsvarende mappingen
    gauleg(0, pi, Theta, Weights_Theta, n);
    gauleg(0, 2*pi, Phi, Weights_Phi, n);


    //gauleg() // På koordinatene på theta og rho?

    double int_gausslag = 0.;
    double iterations_Laguerre = 0.0;
    for ( int i = 1;  i <= n; i++){                      // r1
        for (int j = 1; j <= n; j++){                    // r2
            for (int k = 0; k < n; k++){                // Kun de to første som skal gå fra 1 til n?
                for (int l = 0; l < n; l++){
                    for (int p = 0; p < n; p++){
                        for (int q = 0; q < n; q++){
                            int_gausslag += Weights_Gauss_Laguerre[i]*Weights_Gauss_Laguerre[j]*Weights_Theta[k]*Weights_Theta[l]*Weights_Phi[p]*Weights_Phi[q]*Spherical_Function(R_Gauss_Laguerre[i],R_Gauss_Laguerre[j],Theta[k], Theta[l], Phi[p], Phi[q]);//Spherical_Coordinates()*Weights for de forskjellige koordinatene//*sin(xgl[i]);
                            iterations_Laguerre++;
                        }
                    }
                }
            }
        }
    }

    */

    //-----------------------------------------------------------------------------------------------------------------------
    // Monte Carlo


    double x[6], fx;

    double int_mc = 0.0; double variance = 0.0;
    double sum_sigma = 0.0; long idum = -1;
    double jacobidet = pow((b-a), 6);
    double length = 3.0;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 6; j++){
            //cout << (double)rand()/RAND_MAX << endl;
            //cout << ran0(&idum) << endl;
            //x[j] = -length+2*length*ran0(&idum);
            x[j] = a+(b-a)*ran0(&idum);
            //x[j] = a+(b-a)*(double)rand()/RAND_MAX;
        }
        fx = Brute_Force_MC(x);
        int_mc += fx;
        sum_sigma += fx*fx;

    }
    //sum_sigma = sum_sigma/((double) n);
    //variance = sum_sigma-(fx/((double) n))*(fx/((double) n));

    //int_mc = int_mc/((double) n);


    int_mc = jacobidet*int_mc/((double) n);
    sum_sigma = jacobidet*sum_sigma/((double) n);
    variance = sum_sigma - int_mc*int_mc; // Feil? SJekk boka

    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << "Monte Carlo = " << setw(10) << setprecision(8) << int_mc << endl;
    //cout << "Sigma = " << set(10) << setprecision(8) <<




    //cout << "Iterations Legendre: " << iterations_Legendre << endl;
    //cout << setiosflags(ios::showpoint | ios::uppercase);
    //cout << "Gaussian-Legendre quad = " << setw(20) << setprecision(15)  << int_gauss << endl;

    //cout << "--------------------------------------------------------------------------------\n";
    //cout << "Iterations Laguerre: " << iterations_Laguerre << endl;
    //cout << "Gaussian-Laguerre quad = " << setw(20) << setprecision(15)  << int_gausslag << endl;

}  // end of main program


/*
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
//#include <stdio.h>
//#include <stdlib.h>

#include "legendre.h"
#include "repulsion_function.h"
#include "laguerre.h"

using namespace std;


int main()
{
    int n;
    double a, b;
    cout << "Read in the number of integration points" << endl;
    cin >> n;
    cout << "Read in integration limits" << endl;
    cin >> a >> b;




    //-----------------------------------------------------------------------------------------------------------------------
    // Legendre
    // Putte det her inn i en egen function
    // Hardcode hva alpha er eller ta det som input for functions?

    double *x = new double [n];
    double *w = new double [n];

    gauleg(a, b, x, w, n);


    double Integral_Gauss_Legendre = 0.0;
    double Iterations_Legendre = 0.0;
    for ( int i = 0;  i < n; i++){
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                for (int l = 0; l < n; l++){
                    for (int p = 0; p < n; p++){
                        for (int q = 0; q < n; q++){
                            Integral_Gauss_Legendre+=w[i]*w[j]*w[k]*w[l]*w[p]*w[q]*Cartesian_Function(x[i],x[j],x[k],x[l],x[p],x[q]);
                            Iterations_Legendre++;
                        }
                    }
                }
            }

        }
    }
    //-----------------------------------------------------------------------------------------------------------------------

    //-----------------------------------------------------------------------------------------------------------------------
    // Laguerre

    double Iterations_Laguerre = 0.0;

    //-----------------------------------------------------------------------------------------------------------------------


    cout << "Iterations Legendre: " << Iterations_Legendre << endl;
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << "Gaussian-Legendre quad = " << setw(20) << setprecision(15)  << Integral_Gauss_Legendre << endl;

    /*

    cout << "--------------------------------------------------------------------------------\n";
    cout << "Iterations Laguerre: " << Iterations_Laguerre << endl;
    cout << "Gaussian-Laguerre quad = " << setw(20) << setprecision(15)  << Integral_Gauss_Laguerre << endl;

    */

//}








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
