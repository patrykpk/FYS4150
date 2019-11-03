#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

#include <armadillo>
#include "inputoutput.h"
#include "metropolis.h"

using namespace arma;
using namespace std;

ofstream ofile;

int main()
{
    int L = 2;
    int MonteCarloCycles = 10000;
    double Temperature = 1.0;

    ofstream ofile;

    string SpinConfig = "Ordered";

    string Navn = "AltFunker.txt";

    ofile.open(Navn);
    MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig);
    ofile.close();

    // SingleTemperature
    // TemperatureInterval
}
