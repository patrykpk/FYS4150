#ifndef SOLVERS_H
#define SOLVERS_H

#include "Algorithms1D.h"
#include "Algorithms2D.h"

void JacobiSolv(mat &u, double dx, double dt, double tol, int Iteration_Limit, double MaxTime);
void TridiagSolv(rowvec &x, rowvec y, int N, double b, double d);

#endif // SOLVERS_H