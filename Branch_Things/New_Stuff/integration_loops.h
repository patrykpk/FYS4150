#ifndef INTEGRATION_LOOPS_H
#define INTEGRATION_LOOPS_H

#include <string>
using namespace std;

double GQ_legendre(double a, double b, int N, double& int_legendre, double& Legendre_time, bool WriteToFile);
double GQ_laguerre(int N, double PI, double& int_laguerre, double& Laguerre_time, bool WriteToFile);
double integration_limit();

#endif // INTEGRATION_LOOPS_H
