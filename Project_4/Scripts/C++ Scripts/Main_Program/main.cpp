#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include "inputoutput.h"
#include "metropolis.h"

// Comment out if you don't want to run Pragma (Parallelization)
// You'll have to comment out some parts in inputoutput.cpp as well
#include <omp.h>

using namespace arma;
using namespace std;

ofstream ofile;

int main(){
    // Declaring variables to be used
    int Approach, MonteCarloCycles, L, Config;
    string SpinConfig;

    cout << "Do you want to run calculations for a Single Temperature [1], Temperature Interval[2],"
    "\nOutput after equilibrium is reached for Monte Carlo[3], Spin configuration matrix[4],"
    "\nAccepted Flips[5] or for  Monte Carlo vs. Expectation values[6]?" << endl;

    cin >> Approach;
    cout << "Size of Spin-matrix:" << endl;
    cin >> L;
    cout << "Numbers of Monte Carlo cycles:" << endl;
    cin >> MonteCarloCycles;
    cout << "Do you want to use ordered[1] or unordered[2] matrix?" << endl;
    cin >> Config;

    if (Config == 1){
        SpinConfig ="Ordered";
    }
    else if (Config == 2){
        SpinConfig = "Unordered";
    }
    AskForInput(L, MonteCarloCycles, Approach, SpinConfig);
}