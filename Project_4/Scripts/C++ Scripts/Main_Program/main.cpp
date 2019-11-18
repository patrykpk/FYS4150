#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <armadillo>
#include "inputoutput.h"
#include "metropolis.h"

#include <omp.h>

using namespace arma;
using namespace std;

ofstream ofile;

int main(){
    int Approach, MonteCarloCycles, L, Config;
    string SpinConfig;

    cout << "Do you want to run for a single temperature [1] or a temperature interval[2], output after equilibrium is reached for Monte Carlo[3], Spin configuration matrix[4],\n Accepted Flips [5], Monte vs Expect [6]?" << endl;
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