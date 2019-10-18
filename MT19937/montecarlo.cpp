#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>


#include <random>

#include <lib.h>
#include "MonteCarlo.h"
#include "CoordinateSystem.h"

using namespace std;

void MonteCarlo_IS(int n, double& Integral, double& Time_Used, double& Standard_Dev, bool WriteToFile){
    string Method = "Importance Sampling Monte Carlo";

    double x[6], fx, y;
    //long idum = -1;
    const double PI = atan(1.0)*4;
    //double jacobidet_r = pow((b-a), 6);
    double jacobidet = 4*pow(PI, 4)/16.0;
    double Sum_Sigma = 0;
    double Variance = 0;

    clock_t start_MC_IS, finish_MC_IS;


    //double int_MonteCarloIS;
    //double MonteCarloIS_time;
    //double variance;
    //double standard_deviation;
    random_device rd;
    mt19937_64 gen(rd());

    uniform_real_distribution<double> Random_Number(0.0, 1.0);


    start_MC_IS = clock();
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 2; j++){
            y = Random_Number(gen);
            x[j] = -0.25*log(1.0-y);
        }
        for (int j = 2; j < 4; j++){
            x[j] = PI*Random_Number(gen);
        }
        for (int j = 4; j < 6; j++){
            x[j] = 2*PI*Random_Number(gen);
        }
        //fx = Brute_Force_MC(x);
        fx = MC_Spherical_Function(x);
        Integral += fx;
        Sum_Sigma += fx*fx;
    }
    finish_MC_IS = clock();
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    Time_Used = (double) (finish_MC_IS-start_MC_IS)/(CLOCKS_PER_SEC);

    if (WriteToFile == false){
        OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    }

}


void MonteCarloBF(double a, double b, int n, double& Integral, double& Time_Used, double& Standard_Dev, bool WriteToFile){
    string Method = "Brute Force Monte Carlo";
    double x[6], fx;
    double mu;
    //double int_mc = 0.0;
    long idum = -1;
    double jacobidet = pow((b-a), 6);

    double Sum_Sigma = 0;
    double Variance = 0;

    random_device rd;
    mt19937_64 gen(rd());

    uniform_real_distribution<double> Random_Number(0.0, 1.0);

    clock_t start_MC_BF, finish_MC_BF;


    //double int_MonteCarloBF;
    //double MonteCarloBF_time;
    //double variance;
    //double standard_deviation;


    start_MC_BF = clock();
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 6; j++){
            x[j] = a+(b-a)*Random_Number(gen);
        }
        //fx = Brute_Force_MC(x);
        fx = Cartesian_Function(x[0], x[1], x[2], x[3], x[4], x[5]);
        mu += fx;
        Sum_Sigma += fx*fx;

    }
    finish_MC_BF = clock();

    // Spørre om det her i gruppetime
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = mu/((double) n);
    Variance = jacobidet*((Sum_Sigma - Integral*Integral)/((double) n));
    Standard_Dev = sqrt(Variance);
    Integral = jacobidet*Integral;


    Time_Used = (double) (finish_MC_BF-start_MC_BF)/(CLOCKS_PER_SEC);

    //OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    if (WriteToFile == false){
        OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    }

}


double Parallel_MonteCarlo_IS(int n, int rank){
    string Method = "Importance Sampling Monte Carlo";

    double x[6], fx, y;
    //long idum = -1;
    const double PI = atan(1.0)*4;
    //double jacobidet_r = pow((b-a), 6);
    double jacobidet = 4*pow(PI, 4)/16.0;
    double Sum_Sigma = 0;
    double Variance = 0;
    double Time_Used;

    double Integral = 0;
    double Standard_Dev = 0;

    clock_t start_MC_IS, finish_MC_IS;


    //double int_MonteCarloIS;
    //double MonteCarloIS_time;
    //double variance;
    //double standard_deviation;
    random_device rd;
    mt19937_64 gen(rd()+rank);

    uniform_real_distribution<double> Random_Number(0.0, 1.0);


    start_MC_IS = clock();
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 2; j++){
            y = Random_Number(gen);
            x[j] = -0.25*log(1.0-y);
        }
        for (int j = 2; j < 4; j++){
            x[j] = PI*Random_Number(gen);
        }
        for (int j = 4; j < 6; j++){
            x[j] = 2*PI*Random_Number(gen);
        }
        //fx = Brute_Force_MC(x);
        fx = MC_Spherical_Function(x);
        Integral += fx;
        Sum_Sigma += fx*fx;
    }
    finish_MC_IS = clock();
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    Time_Used = (double) (finish_MC_IS-start_MC_IS)/(CLOCKS_PER_SEC);

    return Integral;

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
    ofile << "|     N:     |  Monte CarloBF:  | CPU-time MonteCarloBF: |   Standard DeviationBF:   |  Monte CarloIS:    |  CPU-time MonteCarloIS: |  Standard DeviationIS:   |   Exact value:   |" << endl;
    ofile << "|                |                  |                        |                           |                    |                         |                          |                  |" << endl;

    for(int N = 2; N <= n ; N++){
        int h = pow(10,N);

        for (int p = 2; p <= 10; p++){
            int Values = h*p*0.10;
            //cout << "Current value of N: " << Values << endl;
            double int_MonteCarloBF = 0;
            double MonteCarloBF_time = 0;
            double Standard_Deviation_BF = 0;
            MonteCarloBF(a, b, Values, int_MonteCarloBF, MonteCarloBF_time, Standard_Deviation_BF, WriteToFile);


            double int_MonteCarloIS = 0;
            double MonteCarloIS_time = 0;
            double Standard_Deviation_IS = 0;
            MonteCarlo_IS(Values, int_MonteCarloIS, MonteCarloIS_time, Standard_Deviation_IS, WriteToFile);

            //GQ_legendre(a, b, N, int_legendre, Legendre_time, WriteToFile);


            //GQ_laguerre(N,PI, int_laguerre, Laguerre_time, WriteToFile);
            ofile << setw(10) << Values;
            ofile << setw(18) << setprecision(8) << int_MonteCarloBF;
            ofile << setw(20) << setprecision(8) << MonteCarloBF_time;
            ofile << setw(23) << setprecision(8) << Standard_Deviation_BF;
            ofile << setw(22) << setprecision(8) << int_MonteCarloIS;
            ofile << setw(20) << setprecision(8) << MonteCarloIS_time;
            ofile << setw(23) << setprecision(8) << Standard_Deviation_IS;
            ofile << setw(22) << setprecision(8) << Exact_value << endl;
        }



        //----------------------------------------------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------------


    }
    //Loop ended
    ofile.close();

}
