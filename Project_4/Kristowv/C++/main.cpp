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
    double Temperature; int MonteCarloCycles; int L;

    ofstream ofile;

    string SpinConfig;

    string single_temp = "Singel_temp.txt";
    string Temp = "Temperature.txt";
    string Monte = "MonteCarloCycles.txt";
    string Spins = "SpinConfig.txt";
    int TemperatureChoice;

    cout << "Do you want to run for a single temperature [1] or a temperature interval[2], Monte Carlo interval[3], Spin configuration matrix[4]?" << endl;
    cin >> TemperatureChoice;
    cout << "Ordered or Unordered spin configuration:" << endl;
    cin >> SpinConfig;

    if (TemperatureChoice == 1){
        cout << "Size of Spin-matrix:" << endl;
        cin >> L;
        cout << "Numbers of Monte Carlo cycles:" << endl;
        cin >> MonteCarloCycles;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        ofile.open(single_temp);
        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
        MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, TemperatureChoice);
        GenerateTableBottom(ofile);
        ofile.close();
    }
    else if (TemperatureChoice == 2){
        double initial_temp, final_temp, temp_step;
        cout << "Size of Spin-matrix:" << endl;
        cin >> L;
        cout << "Numbers of Monte Carlo cycles:" << endl;
        cin >> MonteCarloCycles;
        cout << "Insert choice of initial temp" << endl;
        cin >> initial_temp;
        cout << "Insert final temperture" << endl;
        cin >> final_temp;
        cout << "Insert temp step" << endl;
        cin >> temp_step;

        ofile.open(Temp);

        GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);

        for (double Temperature = initial_temp; Temperature <= final_temp; Temperature+=temp_step){
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, TemperatureChoice);
            cout << Temperature << endl;
        }
        GenerateTableBottom(ofile);
        ofile.close();
    }
    else if(TemperatureChoice == 3){
        int initial_mont, final_mont, mont_step;
        cout << "Size of Spin-matrix:" << endl;
        cin >> L;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        cout << "Insert initial Monte Carlo cycles" << endl;
        cin >> initial_mont;
        cout << "Insert final Monte Carlo cycles" << endl;
        cin >> final_mont;
        cout << "Insert Monte Carlo cycles-step" << endl;
        cin >> mont_step;

        ofile.open(Monte);
        GenerateTableTopMonteCarlo(ofile, L, Temperature, SpinConfig);
        for (int MonteCarloCycles = initial_mont; MonteCarloCycles <= final_mont; MonteCarloCycles+=mont_step){
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, TemperatureChoice);
            cout << MonteCarloCycles << endl;
        }
        GenerateTableBottom(ofile);
        ofile.close();
    }
    else if(TemperatureChoice == 4){
        int initial_mont, final_mont, mont_step;
        cout << "Size of Spin-matrix:" << endl;
        cin >> L;
        cout << "Insert Temperature" << endl;
        cin >> Temperature;
        cout << "Insert initial Monte Carlo cycles" << endl;
        cin >> initial_mont;
        cout << "Insert final Monte Carlo cycles" << endl;
        cin >> final_mont;
        cout << "Insert Monte Carlo cycles-step" << endl;
        cin >> mont_step;

        ofile.open(Spins);
        for (int MonteCarloCycles = initial_mont; MonteCarloCycles <= final_mont; MonteCarloCycles+=mont_step){
            MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig, TemperatureChoice);
        }
        ofile.close();
    }
    // SingleTemperature
    // TemperatureInterval
}
