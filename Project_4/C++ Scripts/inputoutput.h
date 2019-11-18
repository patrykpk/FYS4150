#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "metropolis.h"

void AskForInput(int L, int MonteCarloCycles, int Approach, string SpinConfig);
void GenerateTableTop(ofstream& ofile, int L, int MonteCarloCycles, string SpinConfig);
void GenerateTableTopMonteCarlo(ofstream& ofile, int L, double Temperature, string SpinConfig);
void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);
void WriteToFileMCvsExpect(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);
void WriteToFileOutputMonteCarlo(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, double Energy);
void WriteToFileOutputMonteSpins(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues, mat SpinMatrix);
void WriteAccepted(ofstream& ofile, int MonteCarloCycles, double Accepted_Flips, int L);
void GenerateTableBottom(ofstream& ofile);

#endif // INPUTOUTPUT_H
