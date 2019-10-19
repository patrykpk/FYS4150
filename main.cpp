#include <iostream>
#include "MonteCarlo.h"

// Include mpi greiene her

using namespace std;

int main(){
    int n;
    double a,b;
    cout << "Parallelization of Monte Carlo\n";
    cout << "Read in the number of integrations points" << endl;
    cin >> n;
    cout << "Insert integration limits a and b" << endl;
    cin >> a >> b;

    int numprocs, my_rank;
    double local_sum, total_sum;
    double local_n = n/numprocs;

    total_sum = 0.0;

    local_sum = Parallel_MonteCarlo_IS(local_n, my_rank);

    if (my_rank == 0){
        cout << "Summen: " << total_sum << endl;
        cout << "Time: " << "SETTE INN TOTAL TIME GREIE HER" << endl;
    }
}
