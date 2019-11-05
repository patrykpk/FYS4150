#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include "metropolis.h"

void GenerateTableTop(ofstream& ofile, int L, int MonteCarloCycles);
void WriteToFileOutput(ofstream& ofile, int L, int MonteCarloCycles, double Temperature, vec ExValues);
void GenerateTableBottom(ofstream& ofile);



#endif // INPUTOUTPUT_H
