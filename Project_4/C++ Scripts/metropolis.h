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
void Metropolis(int L, mat& SpinMatrix, double& Energy, double& Magnetization, vec w);
void MonteCarloAlgorithm(ofstream& ofile, int L, double Temperature, int MonteCarloCycles, string SpinConfig);
void WriteToFile(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);

#endif // METROPOLIS_H
