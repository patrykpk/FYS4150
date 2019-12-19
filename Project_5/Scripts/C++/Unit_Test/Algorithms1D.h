#ifndef ALGORITHMS1D_H
#define ALGORITHMS1D_H
#include <armadillo>
using namespace  std;
using namespace arma;

void Diffusion_1D_FE(double dx);
void Diffusion_1D_BE(double dx);
mat Diffusion_1D_CN(double dx);


#endif // ALGORITHMS1D_H
