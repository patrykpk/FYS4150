#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <random>
#include "lib.h"

#include "MonteCarlo.h"
#include "CoordinateSystem.h"

using namespace std;

void MonteCarlo_IS(int n, double& Integral, double& Time_Used, double& Standard_Dev, bool WriteToFile){
    string Method = "Importance Sampling Monte Carlo";

    // Declaration of variables
    double Differential[6], fx, y;
    const double PI = atan(1.0)*4;

    // Assigning values
    double jacobidet = 4*pow(PI, 4)/16.0;
    double Sum_Sigma = 0;
    double Variance = 0;

    clock_t start_MC_IS, finish_MC_IS;

    // Random number generator (mt19937_64)
    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<double> Random_Number(0.0, 1.0);    // Random numbers between (0,1)

    start_MC_IS = clock();           // Starts counting
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 2; j++){
            y = Random_Number(gen);                    // Value between (0, 1)
            Differential[j] = -0.25*log(1.0-y);        // Value between (0, infinity) r1 and r2
        }
        for (int j = 2; j < 4; j++){
            Differential[j] = PI*Random_Number(gen);   // Value between (0, pi) theta1 and theta2
        }
        for (int j = 4; j < 6; j++){
            Differential[j] = 2*PI*Random_Number(gen); // Value between (0, 2pi) phi1 and phi2
        }
        fx = MC_Spherical_Function(Differential);
        Integral += fx;
        Sum_Sigma += fx*fx;
    }
    finish_MC_IS = clock();          // Stops counting

    // Evaluating different terms
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    Time_Used = (double) (finish_MC_IS-start_MC_IS)/(CLOCKS_PER_SEC);  // Calculates the time used

    // Checks if the output should be written to file
    if (WriteToFile == false){
        OutputToTerminal_MC(Method, n, Integral, Time_Used, Standard_Dev);
    }

}

void MonteCarloBF(double a, double b, int n, double& Integral, double& Time_Used, double& Standard_Dev, bool WriteToFile){
    string Method = "Brute Force Monte Carlo";

    // Declaration of variables
    double Differential[6], fx;
    double mu;

    // Assigning values
    double jacobidet = pow((b-a), 6);
    double Sum_Sigma = 0;
    double Variance = 0;

    // Random number generator (mt19937_64)
    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<double> Random_Number(0.0, 1.0);      // Random numbers between (0,1)

    clock_t start_MC_BF, finish_MC_BF;

    start_MC_BF = clock();                // Starts counting
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 6; j++){
            Differential[j] = a+(b-a)*Random_Number(gen);  // All dimensions are assigned a random value between [a,b]
        }                                                  // (x1, y1, z1, x2, y2, z2)
        // Evaluating the integral and sigma
        fx = Cartesian_Function(Differential[0], Differential[1], Differential[2], Differential[3], Differential[4], Differential[5]);
        mu += fx;
        Sum_Sigma += fx*fx;

    }
    finish_MC_BF = clock();      // Stops counting

    // Evaluating different terms
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = mu/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;


    Time_Used = (double) (finish_MC_BF-start_MC_BF)/(CLOCKS_PER_SEC);     // Calculating time used

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
    ofile << "|    N:    |  Monte CarloBF:  | CPU-time MonteCarlo BF: |   Relative error BF:   |  MonteCarlo IS:    |  CPU-time MonteCarloIS: |  Relative error IS:   |   Exact value:   |" << endl;
    ofile << "|          |                  |                         |                        |                    |                         |                       |                  |" << endl;

    for(int N = 2; N <= n ; N++){
            long int h = pow(10,N);            // Amount of sampling points

            for (int p = 5; p <= 50; p++){
                long int Values = h*p*0.020;   // Distributes the sampling points up to the given value
                double int_MonteCarloBF = 0;
                double MonteCarloBF_time = 0;
                double Standard_Deviation_BF = 0;
                MonteCarloBF(a, b, Values, int_MonteCarloBF, MonteCarloBF_time, Standard_Deviation_BF, WriteToFile);


                double int_MonteCarloIS = 0;
                double MonteCarloIS_time = 0;
                double Standard_Deviation_IS = 0;
                MonteCarlo_IS(Values, int_MonteCarloIS, MonteCarloIS_time, Standard_Deviation_IS, WriteToFile);

                double relative_errorBF = fabs((Exact_value - int_MonteCarloBF)/Exact_value);
                double relative_errorIS = fabs((Exact_value - int_MonteCarloIS)/Exact_value);

                // If you want the output of Standard Deviation run Method 3 in main

                cout << Values << endl;
                ofile << setw(9) << Values;
                ofile << setw(18) << setprecision(8) << int_MonteCarloBF;
                ofile << setw(20) << setprecision(8) << MonteCarloBF_time;
                ofile << setw(25) << setprecision(8) << relative_errorBF;
                ofile << setw(25) << setprecision(8) << int_MonteCarloIS;
                ofile << setw(25) << setprecision(8) << MonteCarloIS_time;
                ofile << setw(25) << setprecision(8) << relative_errorIS;
                ofile << setw(23) << setprecision(8) << Exact_value << endl;
            }
        } 
    ofile.close();
}


double Parallel_MonteCarlo_IS(int n, int rank){
    string Method = "Importance Sampling Monte Carlo";

    // Declaration of variables
    double Differential[6], fx, y;

    // Assigning values
    const double PI = atan(1.0)*4;
    double jacobidet = 4*pow(PI, 4)/16.0;
    double Sum_Sigma = 0;
    double Variance = 0;
    double Integral = 0;
    double Standard_Dev = 0;

    // Random number generator (mt19937_64)
    random_device rd;
    mt19937_64 gen(rd()+rank);          // Different seed for every process run during Parallelization
    uniform_real_distribution<double> Random_Number(0.0, 1.0);


    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 2; j++){
            y = Random_Number(gen);              // Value between (0, 1)
            Differential[j] = -0.25*log(1.0-y);  // Value between (0, infinity) r1 and r2
        }
        for (int j = 2; j < 4; j++){
            Differential[j] = PI*Random_Number(gen);   // Value between (0, pi)
        }
        for (int j = 4; j < 6; j++){
            Differential[j] = 2*PI*Random_Number(gen); // Value between (0, 2pi)
        }
        fx = MC_Spherical_Function(Differential);
        Integral += fx;
        Sum_Sigma += fx*fx;
    }
    // Evaluating different terms
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = Integral/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    return Integral;

}

double Parallel_MonteCarlo_BF(double a, double b, int n, int rank){
    string Method = "Importance Sampling Monte Carlo";

    // Declaration of variables
    double Differential[6], fx, mu;

    // Assigning values
    double jacobidet = pow((b-a), 6);
    double Sum_Sigma = 0;
    double Variance = 0;
    double Integral = 0;
    double Standard_Dev = 0;

    // Random number generator (mt19937_64)
    random_device rd;
    mt19937_64 gen(rd()+rank);          // // Different seed for every process run during Parallelization
    uniform_real_distribution<double> Random_Number(0.0, 1.0);

    for (int i = 1; i <= n; i++){
        for (int j = 0; j < 6; j++){
            Differential[j] = a+(b-a)*Random_Number(gen);   // All dimensions are assigned a random value between [a,b]
        }                                                   // (x1, y1, z1, x2, y2, z2)
        fx = Cartesian_Function(Differential[0], Differential[1], Differential[2], Differential[3], Differential[4], Differential[5]);
        mu += fx;
        Sum_Sigma += fx*fx;

    }
    // Evaluating different terms
    Sum_Sigma = Sum_Sigma/((double) n);
    Integral = mu/((double) n);
    Variance = Sum_Sigma - Integral*Integral;
    Standard_Dev = jacobidet*sqrt(Variance/((double) n));
    Integral = jacobidet*Integral;

    return Integral;

}

