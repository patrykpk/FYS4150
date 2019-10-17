#ifndef LEGENDRE_H
#define LEGENDRE_H

#include <string>
using namespace std;

void gauss_legendre(double x1, double x2, double x[], double w[], int n);
void OutputToTerminalGQ(string Method, double n, double Integral_Value, double Time_Used);
void OutputToFile(double a, double b, int n, string outfilename);

#endif // LEGENDRE_H
