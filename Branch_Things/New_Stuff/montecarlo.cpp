#include <cmath>
#include <iostream>
#include "montecarlo.h"
#include "repulsion_function.h"
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;


void MonteCarlo_IS(int n, double Integral, double Time_Used, double Variance, double Sum_Sigma, double Standard_Dev, bool WriteToFile){
    string Method = "Importance Sampling Monte Carlo";
    double x[6], fx, y;
    //double int_mc = 0.0;
    long idum = -1;
    const double PI = atan(1.0)*4;
    //double jacobidet_r = pow((b-a), 6);
    double jacobidet = 4*pow(PI, 4)/16.0;


    //double int_MonteCarloIS;
    //double MonteCarloIS_time;
    //double variance;
    //double standard_deviation;


    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 2; j++){
            y = ran0(&idum);
            x[j] = -0.25*log(1.0-y);
        }
        for (int j = 2; j < 4; j++){
            x[j] = PI*ran0(&idum);
        }
        for (int j = 4; j < 6; j++){
            x[j] = 2*PI*ran0(&idum);
        }
        //fx = Brute_Force_MC(x);
        fx = MC_Spherical_Function(x);
        Integral += fx;
        Sum_Sigma += fx*fx;
    }
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    if (WriteToFile == false){
        OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    }

}


void MonteCarloBF(double a, double b, int n, double& Integral, double& Time_Used, double& Variance, double& Sum_Sigma, double& Standard_Dev, bool WriteToFile){
    string Method = "Brute Force Monte Carlo";
    double x[6], fx;
    //double int_mc = 0.0;
    long idum = -1;
    double jacobidet = pow((b-a), 6);

    //double int_MonteCarloBF;
    //double MonteCarloBF_time;
    //double variance;
    //double standard_deviation;

    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 6; j++){
            x[j] = a+(b-a)*ran0(&idum);
        }
        //fx = Brute_Force_MC(x);
        fx = Cartesian_Function(x[0], x[1], x[2], x[3], x[4], x[5]);
        Integral += fx;
        Sum_Sigma += fx*fx;

    }

    // Spørre om det her i gruppetime
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;
    //OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    if (WriteToFile == false){
        OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    }

}


void OutputToTerminal_MC(string Method, int n, double int_MonteCarlo, double MonteCarlo_time, double standard_deviation){
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Running " << Method << endl;
    cout << setiosflags(ios::showpoint | ios::uppercase);
    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Monte Carlo = "<< setw(20) << setprecision(15)  << int_MonteCarlo << endl;
    cout << "CPU-time for N = " << n <<":" << setw(20) << setprecision(15)  << MonteCarlo_time << endl;
    cout << "Standard Deviation = " << setw(20) << setprecision(15) << standard_deviation << endl;
}


void OutputToFileMC(double a, double b, int n, string outfilename){
    const double PI = atan(1.0)*4;
    double Exact_value = (5*pow(PI,2))/(256);

    ofstream ofile;

    bool WriteToFile = true;

    cout << "------------------------------------------------------------------------------ " << endl;
    cout << "Running Monte Carlo and writing to file"<< endl;
    cout  << setiosflags(ios::showpoint | ios::uppercase);
    cout << "------------------------------------------------------------------------------ " << endl;

    // Open file and write results to file:
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "|   N:  |  Monte Carlo:    |" << endl; // FIX THIS LATER
    ofile << "|       |                  |" << endl;

    for(int N = 1; N <= n ; N++){

        int h = pow(10,N);

        cout << h << endl;

        double int_MonteCarloBF;
        double MonteCarloBF_time;
        double Variance_BF;
        double Sum_Sigma_BF;
        double Standard_Deviation_BF;
        MonteCarloBF(a, b, n, int_MonteCarloBF, MonteCarloBF_time, Variance_BF, Sum_Sigma_BF, Standard_Deviation_BF, WriteToFile);


        double int_MonteCarloIS;
        double MonteCarloIS_time;
        double variance_IS;
        double Sum_Sigma_IS;
        double standard_deviation_IS;

        //GQ_legendre(a, b, N, int_legendre, Legendre_time, WriteToFile);


        //GQ_laguerre(N,PI, int_laguerre, Laguerre_time, WriteToFile);

        //----------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------------


    }
    //Loop ended
    ofile.close();

}



#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

double ran0(long *idum){
   long     k;
   double   ans;

   *idum ^= MASK;
   k = (*idum)/IQ;
   *idum = IA*(*idum - k*IQ) - IR*k;
   if(*idum < 0) *idum += IM;
   ans=AM*(*idum);
   *idum ^= MASK;
   return ans;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef MASK

