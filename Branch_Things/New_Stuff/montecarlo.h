#ifndef MONTECARLO_H
#define MONTECARLO_H

#include <string>
using namespace std;

void MonteCarloBF(double a, double b, int n, double& Integral, double& Time_Used, double& Variance, double& Sum_Sigma, double& Standard_Dev, bool WriteToFile);
void MonteCarlo_IS(int n, double Integral, double Time_Used, double Variance, double Sum_Sigma, double Standard_Dev, bool WriteToFile);
void OutputToTerminal_MC(string Method, int n, double int_MonteCarlo, double MonteCarlo_time, double standard_deviation);
void OutputToFileMC(double a, double b, int n, string outfilename);
//void OutputToFileMC(a, b, n, outfilename);
double ran0(long *idum);

#endif // MONTECARLO_H
