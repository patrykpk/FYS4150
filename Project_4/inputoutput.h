#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "metropolis.h"

void GenerateTableTop(ofstream& ofile, int L, int MonteCarloCycles, string SpinConfig);
void GenerateTableTopMonteCarlo(ofstream& ofile, int L, double Temperature, string SpinConfig);
void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);
void WriteToFileOutputMonteCarlo(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);
void WriteToFileOutputMonteSpins(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues, mat SpinMatrix);
void GenerateTableBottom(ofstream& ofile);

#endif // INPUTOUTPUT_H
