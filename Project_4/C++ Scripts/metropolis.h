#ifndef METROPOLIS_H
#define METROPOLIS_H

#include <iomanip>
#include <armadillo>
#include <random>
#include <cmath>

using namespace arma;
using namespace std;

int PeriodicBC(int InitialPos, int MatrixSize, int Neighbor);
void Initialize(int L, mat& SpinMatrix, double& Energy, double& Magnetization, string SpinConfig);
double Metropolis(int L, mat& SpinMatrix, double& Energy, double& Magnetization, vec w, int& Accepted_Flips);
void MonteCarloAlgorithm(ofstream& ofile, int L, double Temperature, int MonteCarloCycles, string SpinConfig, int Approach, int Equilibrium);
#endif // METROPOLIS_H
