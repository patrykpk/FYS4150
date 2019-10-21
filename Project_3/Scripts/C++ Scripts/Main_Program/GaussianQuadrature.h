#ifndef INTEGRATION_LOOPS_H
#define INTEGRATION_LOOPS_H

#include <string>
using namespace std;

void GQ_legendre(double a, double b, int N, double& int_legendre, double& Legendre_time, bool WriteToFile);
void GQ_laguerre(int N, double PI, double& int_laguerre, double& Laguerre_time, bool WriteToFile);
void OutputToTerminalGQ(string Method, int n, double Integral_Value, double Time_Used);
void OutputToFile(double a, double b, int n, string outfilename);
double integration_limit();

#endif // INTEGRATION_LOOPS_H
