#include <iostream>
#include "MonteCarlo.h"
#include <mpi.h>
// Include mpi greiene her

using namespace std;

int main(int nargs, char* args[]){

    // Command line argument
    int n = atoi(args[1]);

    // Initializing Parallelization MPI
    int numprocs, my_rank;
    MPI_Init(&nargs, &args);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Declaring variables to be used
    double local_sum_IS, total_sum_IS, local_sum_BF, total_sum_BF;
    double local_n = n/numprocs;

    total_sum_BF = 0.0;
    total_sum_IS = 0.0;

    // Parallel MonteCarlo Importance sampling
    double time_start_IS = MPI_Wtime();     // Starts counting
    local_sum_IS = Parallel_MonteCarlo_IS(local_n, my_rank);
    MPI_Reduce(&local_sum_IS, &total_sum_IS, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double time_end_IS = MPI_Wtime();       // Stops counting
    double total_time_IS = time_end_IS - time_start_IS;   // Time used for Importance Sampling

    //Parallel MonteCarlo Brute Force
    // Using the same [a, b] as in other methods
    double a = -3.0;
    double b = 3.0;

    double time_start_BF = MPI_Wtime();  // Starts counting
    local_sum_BF = Parallel_MonteCarlo_BF(a,  b, local_n, my_rank);
    MPI_Reduce(&local_sum_BF, &total_sum_BF, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    double time_end_BF = MPI_Wtime();    // Stops counting
    double total_time_BF = time_end_BF - time_start_BF;  // Time used for Brute Force

    if (my_rank == 0){
        cout << "-----------------------------------------------------------------------------"<<endl;
        cout << "Parallelization of Monte Carlo Importance Sampling\n";
        cout << "Integral Importance sampling: " << total_sum_IS/numprocs << endl;
        cout << "Time Monte Carlo Importance Sampling: " << total_time_IS << "\n\n";

        cout << "-----------------------------------------------------------------------------"<<endl;
        cout << "Parallelization of Monte Carlo Brute Force \n";
        cout << "Integral Brute Force: " << total_sum_BF/numprocs << endl;
        cout << "Time Monte Carlo Brute Force: " << total_time_BF << "\n\n";
    }



    MPI_Finalize();
}
