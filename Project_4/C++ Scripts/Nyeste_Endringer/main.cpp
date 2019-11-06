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
    int MonteCarloCycles = 10;
    double Temperature;
    ofstream ofile;

    string SpinConfig = "Unordered";


    string Navn = "AltFunker.txt";

    int TemperatureChoice;

    cout << "Do you want to run for a single temperature [1] or a temperature interval[2]?" << endl;
    cin >> TemperatureChoice;

    if (TemperatureChoice == 1){
	    cout << "Insert Temperature" << endl;
	    cin >> Temperature;
	    ofile.open(Navn);
	    GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);
	    MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig);
	    GenerateTableBottom(ofile);
	    ofile.close();
    }
    else if (TemperatureChoice == 2){
	    double initial_temp, final_temp, temp_step;
	    cout << "Insert choice of initial temp" << endl;
	    cin >> initial_temp;
	    cout << "Insert final temperture" << endl;
	    cin >> final_temp;
	    cout << "Insert temp step" << endl;
	    cin >> temp_step;

	    ofile.open(Navn);

	    GenerateTableTop(ofile, L, MonteCarloCycles, SpinConfig);

	    for (double Temperature = initial_temp; Temperature <= final_temp; Temperature+=temp_step){
		    MonteCarloAlgorithm(ofile, L, Temperature, MonteCarloCycles, SpinConfig);
		    cout << Temperature << endl;
	    }
	    GenerateTableBottom(ofile);
	    ofile.close();
    }

    // SingleTemperature
    // TemperatureInterval
}
