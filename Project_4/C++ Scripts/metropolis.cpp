#include "metropolis.h"
#include "inputoutput.h"
#include <chrono>


// Periodic Boundary Condition
int PeriodicBC(int InitialPos, int MatrixSize, int Neighbor){
  return (InitialPos+MatrixSize+Neighbor) % (MatrixSize);
}

void Initialize(int L, mat& SpinMatrix, double& Energy, double& Magnetization, string SpinConfig){

    if (SpinConfig == "Ordered"){
        SpinMatrix.fill(1);          // Fills all elements with ones
    }
    else if (SpinConfig == "Unordered"){
        //random_device rd;
        //mt19937_64 gen(rd());
        mt19937_64 mt_rand(time(0));

        uniform_real_distribution<double> RandomNumb(0.0, 1.0);
        for (int x = 0; x < L; x++){
            for (int y = 0; y < L; y++){
                // DEN HER ER IKKE RANDOM! SAMME SEED UANSETT KJØRING
                if (RandomNumb(mt_rand) >= 0.5){
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
            Energy -= (double) SpinMatrix(x,y)*(SpinMatrix(PeriodicBC(x, L, -1),y)+SpinMatrix(x,PeriodicBC(y,L,-1)));
        }
    }
}

void Metropolis(int L, mat& SpinMatrix, double& Energy, double& Magnetization, vec w){
    random_device rd;
    mt19937_64 gen(rd());
    //auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    //cout << seed << endl;

    //mt19937_64 mt_rand(seed);
    uniform_real_distribution<double> RandomNumb(0.0, 1.0);

    //Initialize(L, SpinMatrix, Energy, Magnetization, SpinConfig);


    int MaxIteration = L*L;
    for (int Iteration = 0; Iteration < MaxIteration; Iteration++){
        int Rx = (int) (RandomNumb(gen)*(double) L);
        int Ry = (int) (RandomNumb(gen)*(double) L);

        int dE = 2*SpinMatrix(Rx, Ry)*
                (SpinMatrix(Rx, PeriodicBC(Ry,L,-1))+
                 SpinMatrix(PeriodicBC(Rx,L,-1), Ry)+
                SpinMatrix(Rx, PeriodicBC(Ry,L,1))+
                SpinMatrix(PeriodicBC(Rx,L,1), Ry));

        if (RandomNumb(gen) <= w(dE+8)){
            cout << "Flipped" << endl;
            SpinMatrix(Rx,Ry) *= -1;
            Magnetization += (double) 2*SpinMatrix(Rx, Ry);
            Energy += (double) dE;
        }
    }
}


void MonteCarloAlgorithm(ofstream& ofile, int L, double Temperature, int MonteCarloCycles, string SpinConfig){
    mat SpinMatrix = zeros<mat>(L,L); // Her eller i main?
    vec ExValues = zeros<vec>(5);
    double Energy = 0.0, Magnetization = 0.0;

    vec w = zeros<vec>(17);
    for (int dE = -8; dE <= 8; dE+=4){
        w(dE+8)=exp(-dE/Temperature);
    }

    Initialize(L, SpinMatrix, Energy, Magnetization, SpinConfig);

    for (int Cycles = 1; Cycles <= MonteCarloCycles; Cycles++){
        Metropolis(L, SpinMatrix, Energy, Magnetization, w);
        // Sett kommentar på hva som er hva
        ExValues(0) += Energy;          ExValues(1) += Energy*Energy;
        ExValues(2) += Magnetization;   ExValues(3) += Magnetization*Magnetization;
        ExValues(4) += fabs(Magnetization);

    }
    WriteToFileOutput(ofile, L, MonteCarloCycles, Temperature, ExValues);

    // Algortime for å skrive til fil her

}


/*
for ( double temperature = initial_temp; temperature <= final_temp; temperature+=temp_step){
  //    initialise energy and magnetization
  E = M = 0.;
  // setup array for possible energy changes
  for( int de =-8; de <= 8; de++) w[de+8] = 0;
  for( int de =-8; de <= 8; de+=4) w[de+8] = exp(-de/temperature);
  // initialise array for expectation values
  for( int i = 0; i < 5; i++) average[i] = 0.;
  initialize(n_spins, temperature, spin_matrix, E, M);
  // start Monte Carlo computation
  for (int cycles = 1; cycles <= mcs; cycles++){
    Metropolis(n_spins, idum, spin_matrix, E, M, w);
    // update expectation values
    average[0] += E;    average[1] += E*E;
    average[2] += M;    average[3] += M*M; average[4] += fabs(M);
  }
  // print results
  output(n_spins, mcs, temperature, average);
}
*/
