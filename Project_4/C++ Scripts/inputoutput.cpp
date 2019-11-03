#include "inputoutput.h"
#include "metropolis.h"

void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues){
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    double Maverage = ExValues(2)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << setw(15) << setprecision(8) << Temperature;
    ofile << setw(15) << setprecision(8) << Eaverage/L/L;
    ofile << setw(15) << setprecision(8) << Evariance/Temperature/Temperature;
    ofile << setw(15) << setprecision(8) << Maverage/L/L;
    ofile << setw(15) << setprecision(8) << Mvariance/Temperature;
    ofile << setw(15) << setprecision(8) << Mabsaverage/L/L << endl;
}

