#define CATCH_CONFIG_MAIN
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include "catch.hpp"
#include "metropolis.h"


using namespace arma;
using namespace std;


TEST_CASE("Checking if Initialize correctly initalizes the spin matrix with ordered configuration."){

    // Initialize all parameters
    int L = 2;
    double Energy = 0.0;
    double Magnetization = 0.0;
    mat SpinMatrix = zeros<mat>(L,L);
    string SpinConfig = "Ordered";

    // Initialize the matrix with ordered spins
    Initialize(L, SpinMatrix, Energy, Magnetization, SpinConfig);

    // Checking against analytical solutions
    CHECK ( Energy/(L*L) == Approx(-2));
    CHECK ( Magnetization/(L*L) == Approx(1));
}


TEST_CASE("Check if code reproduces analytical results with desired prescision after 1m MC cycles."){

    // Initialize all parameters
    int L = 2;
    int Accepted_Flips = 0;
    int Accepted = 0;
    int MonteCarloCycles = 1000000;
    double Temperature = 1.0;
    double Energy = 0.0;
    double Magnetization = 0.0;
    string SpinConfig = "Unordered";
    mat SpinMatrix = zeros<mat>(L,L);
    vec ExValues = zeros<vec>(5);
    vec w = zeros<vec>(17);

    // Fills the vector w
    for (int dE = -8; dE <= 8; dE+=4){
        w(dE+8)=exp(-dE/Temperature);
    }

    // Initializes the spin matrix with unordered spins
    Initialize(L, SpinMatrix, Energy, Magnetization, SpinConfig);

    // Runs 1m Monte Carlo cycles using the Metropolis algorithm
    for (int Cycles = 1; Cycles <= MonteCarloCycles; Cycles++){
        Accepted = Metropolis(L, SpinMatrix, Energy, Magnetization, w, Accetped_Flips);
        ExValues(0) += Energy;          ExValues(1) += Energy*Energy;
        ExValues(2) += Magnetization;   ExValues(3) += Magnetization*Magnetization;
        ExValues(4) += fabs(Magnetization);
    }

    // Monte Carlo normalization factor
    double Normalization = 1./(MonteCarloCycles);

    // Analytical solutions
    double AnalyticalEnergy = -1.99598821;
    double AnalyticalHeatCapacity = 0.03208233;
    double AnalyticalMagnetization = 0.99866073;
    double AnalyticalSusceptibility = 0.00401074;

    // Calculating parameters
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;
    double EnergyVariance = (E2average- Eaverage*Eaverage);
    double MagneticVariance = (M2average - Mabsaverage*Mabsaverage);

    // Checking against analytical solutions per spin
    CHECK (fabs(AnalyticalEnergy-Eaverage/(L*L)) <= 1E-3);
    CHECK (fabs(AnalyticalHeatCapacity-EnergyVariance/(L*L*Temperature*Temperature)) <= 1E-3);
    CHECK (fabs(AnalyticalMagnetization-Mabsaverage/(L*L)) <= 1E-3);
    CHECK (fabs(AnalyticalSusceptibility-MagneticVariance/(L*L*Temperature)) <= 1E-3);
}
