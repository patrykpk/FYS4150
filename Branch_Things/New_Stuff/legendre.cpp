#include "legendre.h"
#include <cmath>
#define   ZERO       1.0E-10

#include <fstream>
#include <iostream>
#include <iomanip>

#include "Integration_loops.h"

ofstream ofile;

using namespace std;

void gauss_legendre(double x1, double x2, double x[], double w[], int n)
{
   int         m,j,i;
   double      z1,z,xm,xl,pp,p3,p2,p1;
   double const pi = 4*atan(1);
   double      *x_low, *x_high, *w_low, *w_high;

   m  = (n + 1)/2;                             // roots are symmetric in the interval
   xm = 0.5 * (x2 + x1);
   xl = 0.5 * (x2 - x1);

   x_low  = x;                                       // pointer initialization
   x_high = x + n - 1;
   w_low  = w;
   w_high = w + n - 1;

   for(i = 1; i <= m; i++) {                             // loops over desired roots
      z = cos(pi * (i - 0.25)/(n + 0.5));

           /*
       ** Starting with the above approximation to the ith root
           ** we enter the mani loop of refinement bt Newtons method.
           */

      do {
         p1 =1.0;
         p2 =0.0;

       /*
       ** loop up recurrence relation to get the
           ** Legendre polynomial evaluated at x
           */

     for(j = 1; j <= n; j++) {
        p3 = p2;
        p2 = p1;
        p1 = ((2.0 * j - 1.0) * z * p2 - (j - 1.0) * p3)/j;
     }

       /*
       ** p1 is now the desired Legrendre polynomial. Next compute
           ** pp its derivative by standard relation involving also p2,
           ** polynomial of one lower order.
           */

     pp = n * (z * p1 - p2)/(z * z - 1.0);
     z1 = z;
     z  = z1 - p1/pp;                   // Newton's method
      } while(fabs(z - z1) > ZERO);

          /*
      ** Scale the root to the desired interval and put in its symmetric
          ** counterpart. Compute the weight and its symmetric counterpart
          */

      *(x_low++)  = xm - xl * z;
      *(x_high--) = xm + xl * z;
      *w_low      = 2.0 * xl/((1.0 - z * z) * pp * pp);
      *(w_high--) = *(w_low++);
   }
} // End_ function gauleg()
#undef ZERO


void OutputToTerminalGQ(string Method, double n, double Integral_Value, double Time_Used){
    const double PI = atan(1.0)*4;
    double Exact_value = (5*pow(PI,2))/(256);
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Running "<< Method << endl;
    cout  << setiosflags(ios::showpoint | ios::uppercase);
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Gaussian-Legendre quadrature = "<< setw(20) << setprecision(15)  << Integral_Value << endl;
    cout << "CPU-time for N = " << n <<":" << setw(20) << setprecision(15)  << Time_Used << endl;
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

    //Looping through different iteration -values of N
    for(int N = 1; N <= n ; N++){

        double int_legendre, Legendre_time;
        GQ_legendre(a, b, N, int_legendre, Legendre_time, WriteToFile);

        double int_laguerre,Laguerre_time;
        GQ_laguerre(N,PI, int_laguerre, Laguerre_time, WriteToFile);

        //----------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------------
        //Calculating the relative error
        double relative_error_leg = (Exact_value - int_legendre)/Exact_value;
        double relative_error_lag = (Exact_value - int_laguerre)/Exact_value;
        //----------------------------------------------------------------------------------------------------------------------
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
    //Loop ended
    ofile.close();
}


