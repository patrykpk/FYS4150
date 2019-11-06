#include "inputoutput.h"
#include "metropolis.h"


void GenerateTableTop(ofstream& ofile, int L, int MonteCarloCycles, string SpinConfig){
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "Spin Matrix: " << L << "x" << L << endl;
    ofile << "Number of Monte Carlo Cycles: " << MonteCarloCycles << endl;
    ofile << "Spin Configuration: " << SpinConfig << endl;
    ofile << "All values are given per spin!\n";
    ofile << "╔═══════════════╤══════════════╤═══════════════╤═══════════════╤════════════════╗\n";
    ofile << "║  Temperature  │    Energy    │ Heat Capacity │ Magnetization │ Susceptibility ║" << endl;
    ofile << "╟───────────────┼──────────────┼───────────────┼───────────────┼────────────────╢\n";

}



void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues){
    double Normalization = 1/((double) (MonteCarloCycles));  // divided by total number of cycles
    double Eaverage = ExValues(0)*Normalization;
    double E2average = ExValues(1)*Normalization;
    //double Maverage = ExValues(2)*Normalization;
    double M2average = ExValues(3)*Normalization;
    double Mabsaverage = ExValues(4)*Normalization;

    // all expectation values are per spin, divide by 1/n_spins/n_spins
    double Evariance = (E2average- Eaverage*Eaverage)/L/L;
    double Mvariance = (M2average - Mabsaverage*Mabsaverage)/L/L;

    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "║   " << fixed <<setprecision(7) << Temperature  << "   ";
    ofile << "│  " << fixed <<setprecision(7)  << Eaverage/L/L << "  ";
    ofile << "│   " << fixed << setprecision(7) << Evariance/Temperature/Temperature << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mabsaverage/L/L << "   ";
    ofile << "│   " << fixed <<setprecision(7) << Mvariance/Temperature << "    ║" << endl;
    //ofile << setw(15) << setprecision(8) << Maverage/L/L << endl;
}

void GenerateTableBottom(ofstream& ofile){
    ofile << "╚═══════════════╧══════════════╧═══════════════╧═══════════════╧════════════════╝\n";
}
