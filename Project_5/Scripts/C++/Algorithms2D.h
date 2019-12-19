#ifndef ALGORITHMS2D_H
#define ALGORITHMS2D_H

#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <armadillo>
#include <string>

using namespace  std;
using namespace arma;

void Analytic2D(mat &u, int N, double t);
void Explicit_2D(double dx_2d);
void ForwardEuler_2D(cube &u, double alpha, int TimeSteps, int N);
void Implicit_2D(double dx_2d);

#endif // ALGORITHMS2D_H