#include "metropolis.h"
#include "inputoutput.h"


// Periodic Boundary Condition
int PeriodicBC(int InitialPos, int MatrixSize, int Neighbor){
  return (InitialPos+MatrixSize+Neighbor) % (MatrixSize);
}

void Initialize(int L, mat& SpinMatrix, double& Energy, double& Magnetization, string SpinConfig){

    if (SpinConfig == "Ordered"){
        SpinMatrix.fill(1);          // Fills all elements with ones
    }
    else if (SpinConfig == "Unordered"){
        // Random Number Generator (mt19937_64)
        random_device rd;
        mt19937_64 gen(rd());
        uniform_real_distribution<double> RandomNumb(0.0, 1.0);

        // Randomizes the content of the matrix with either 1 or -1
        for (int x = 0; x < L; x++){
            for (int y = 0; y < L; y++){
                if (RandomNumb(gen) >= 0.5){
                    SpinMatrix(x,y) = 1.0;
                }
                else{
                    SpinMatrix(x,y) = -1.0;
                }
            }
        }
    }
    // Initial Energy has to be evaluated in seperate for loop so all elements of the matrix are initialized
    // before performing any sort of calculations
    for (int x = 0; x < L; x++){
        for (int y = 0; y < L; y++){
            Magnetization += (double) SpinMatrix(x,y);
            Energy -= (double) SpinMatrix(x,y)*(SpinMatrix(x,PeriodicBC(y,L,-1))+SpinMatrix(PeriodicBC(x, L, -1),y));
        }
    }
}

double Metropolis(int L, mat& SpinMatrix, double& Energy, double& Magnetization, vec w, int& Accepted_Flips){
    // Random Number Generator (mt19937_64)
    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<double> RandomNumb(0.0, 1.0);

    int Accepted = 0;

    int MaxIteration = L*L; // Possibilites to flip
    for (int Iteration = 0; Iteration < MaxIteration; Iteration++){

        // Randomly choosing an element in the lattice
        int Rx = (int) (RandomNumb(gen)*(double) L);
        int Ry = (int) (RandomNumb(gen)*(double) L);

        int dE = 2*SpinMatrix(Rx, Ry)*
                (SpinMatrix(Rx, PeriodicBC(Ry,L,-1))+
                 SpinMatrix(Rx, PeriodicBC(Ry,L, 1))+
                 SpinMatrix(PeriodicBC(Rx,L,-1), Ry)+
                 SpinMatrix(PeriodicBC(Rx,L,1), Ry));

        // Randomly choosing a number between (0, 1) and flipping the spin
        // if this statement is true
        if (RandomNumb(gen) <= w(dE+8)){
            SpinMatrix(Rx,Ry) *= -1;
            Magnetization += (double) 2*SpinMatrix(Rx, Ry);
            Energy += (double) dE;
            Accepted_Flips += 1; // Adds accepted flips to a variable for all Monte Carlo cyclces
            Accepted += 1;       // Adds accepted flips to variable for this Monte Carlo cycle
        }
    }
    return Accepted; // Returns the amount of accepted flips for this Monte Carlo cycle
}


void MonteCarloAlgorithm(ofstream& ofile, int L, double Temperature, int MonteCarloCycles, string SpinConfig, int Approach, int Equilibrium){
    mat SpinMatrix = zeros<mat>(L,L); // 
    vec ExValues = zeros<vec>(5);     // 
    double Energy = 0.0, Magnetization = 0.0;

    vec w = zeros<vec>(17);
    for (int dE = -8; dE <= 8; dE+=4){
        w(dE+8)=exp(-dE/Temperature);
    }

    int Accepted_Flips = 0; // Total amount of accepted flips for Monte Carlo cycles
    int Accepted = 0;       // Accepted flips for a single Monte Carlo cycle

    Initialize(L, SpinMatrix, Energy, Magnetization, SpinConfig); // Initializing the Spin Matrix

    for (int Cycles = 1; Cycles <= MonteCarloCycles; Cycles++){
        Accepted = Metropolis(L, SpinMatrix, Energy, Magnetization, w, Accepted_Flips);
        // Adds new values to the vector
        ExValues(0) += Energy;          ExValues(1) += Energy*Energy;
        ExValues(2) += Magnetization;   ExValues(3) += Magnetization*Magnetization;
        ExValues(4) += fabs(Magnetization);

        // Rest of the code is output that is dependent on the approach chosen in AskForInput()
        if (Cycles>=Equilibrium and Approach == 3){
            WriteToFileOutputMonteCarlo(ofile, L, Cycles, Temperature, Energy);
        }
        else if (Approach == 5){
            WriteAccepted(ofile, Cycles, Accepted_Flips, L);
        }
        else if (Cycles >= Equilibrium and Approach == 6){
            WriteToFileMCvsExpect(ofile, L, Cycles, Temperature, ExValues);
        }
    }
    if (Approach == 1 or Approach == 2){
        WriteToFileOutput(ofile, L, MonteCarloCycles, Temperature, ExValues);
    }
    else if(Approach == 4){
        WriteToFileOutputMonteSpins(ofile, L, MonteCarloCycles, Temperature, ExValues, SpinMatrix);
    }
}

