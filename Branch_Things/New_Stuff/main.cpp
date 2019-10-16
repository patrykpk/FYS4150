#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>  //setiosflags, setw, setprecision
#include <string>

#include "repulsion_function.h"
#include "Integration_loops.h"
#include "montecarlo.h"
#include "legendre.h"

using namespace std;


int main(){
    // Assigning constant PI and calculating exact value of integral.
    const double PI = atan(1.0)*4;
    double Exact_value = (5*pow(PI,2))/(256);
    int n;
    double a,b;

    int Method;
    cout << "What would you like to do?" << endl;
    cout << "Values listed below give output for one value of 'n' in the terminal\n";
    cout << "[1] Legendre, [2] Laguerre, [3] MonteCarlo\n\n";
    cout << "Remaining options write the output to file up to the given value of 'n'\n";
    cout << "[4] Legendre & Laguerre up to N, [5] MonteCarlo up to... \nMethod: ";
    cin >> Method;

    if (Method == 1){
        // Legendre
        cout << "Read in the number of integration points" << endl;
        cin >> n;
        cout << "Read in integration limits" << endl;
        cin >> a >> b;

        bool WriteToFile = false;
        double int_legendre, Legendre_time;
        GQ_legendre(a, b, n, int_legendre, Legendre_time, WriteToFile);

    }
    else if (Method == 2){
        // Laguerre
        cout << "Read in the number of integration points" << endl;
        cin >> n;

        bool WriteToFile = false;
        double int_laguerre, Laguerre_time;
        GQ_laguerre(n,PI, int_laguerre, Laguerre_time, WriteToFile);

    }
    else if (Method == 3){
        cout << "Do you want to run [1] Brute Force or [2] Importance sampling? " << endl;
        int Number;
        cin >> Number;
        bool WriteToFile = false;

        double Int_MonteCarlo;
        double Time;
        double Variance;
        double Sum_Sigma;
        double Standard_Dev;

        switch(Number){
            case 1:
                cout << "Read in the number of integration points" << endl;
                cin >> n;
                cout << "Insert integration limits a and b" << endl;
                cin >> a >> b;
                MonteCarloBF(a,b,n, Int_MonteCarlo, Time, Variance, Sum_Sigma, Standard_Dev, WriteToFile);
                break;

            case 2:
                cout << "Read in the number of integration points" << endl;
                cin >> n;
                MonteCarlo_IS(n, Int_MonteCarlo, Time, Variance, Sum_Sigma, Standard_Dev, WriteToFile);
                break;
         }
    }
    else if (Method == 4){
        cout << "Read in the number of integration points" << endl;
        cin >> n;
        cout << "Insert integration limits a and b" << endl;
        cin >> a >> b;
        string outfilename = "Project_3.txt"; // DEN HER MÅ FIKSES
        OutputToFile(a, b, n, outfilename);
    }
    else if (Method == 5){
        cout << "Read in the highest power of n you would like to use\n";
        cin >> n;
        cout << "Integration limits\n";
        cin >> a >> b;
        string outfilename = "Project_3.dat"; // Den her må fikses
        OutputToFileMC(a, b, n, outfilename);
    }


    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------
    cout << "-----------------------------------------------------------------------------"<<endl;
    integration_limit();
    cout << "-----------------------------------------------------------------------------"<<endl;
    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------

    //Reading in Number of iterations and integration limits.

    //----------------------------------------------------------------------------------------------------------------------
    //----------------------------------------------------------------------------------------------------------------------

    // Declaration of command line arguments

    //----------------------------------------------------------------------------------------------------------------------
    // If test for running both Legendre and laguere, and producing file.
    //----------------------------------------------------------------------------------------------------------------------
    /*else if (argc == 2){
        string outfilename;
        outfilename = argv[1];
        cout << "------------------------------------------------------------------------------ " << endl;
        cout << "Running Legendre and Laguerre"<< endl;
        cout  << setiosflags(ios::showpoint | ios::uppercase);
        cout << "------------------------------------------------------------------------------ " << endl;
        // Open file and write results to file:
        ofile.open(outfilename);
        ofile << setiosflags(ios::showpoint | ios::uppercase);
        ofile << "|   N:  |  Legendre:    |  CPU-time Legendre:    | Relative error Legendre: |   Laguerre:  | CPU-time Laguerre | Relative error Laguerre: |  Excact result: |" << endl;
        ofile << "|       |               |                        |                          |              |                   |                          |                 |" << endl;

        //Looping through different iteration -values of N
        for(int N = 1; N <= n ; N++){

            double int_legendre, Legendre_time;
            GQ_legendre(a, b, N, int_legendre, Legendre_time);

            double int_laguerre,Laguerre_time;
            GQ_laguerre(N,PI, int_laguerre, Laguerre_time);

            //----------------------------------------------------------------------------------------------------------------------
            //----------------------------------------------------------------------------------------------------------------------
            //Calculating the relative error
            double relative_error_leg = (Exact_value - int_legendre)/Exact_value;
            double relative_error_lag = (Exact_value - int_laguerre)/Exact_value;
            //----------------------------------------------------------------------------------------------------------------------
            //----------------------------------------------------------------------------------------------------------------------
            cout << N << endl;
            //Writing results in file.
            ofile << setw(5) << N;
            ofile << setw(18) << setprecision(8) << int_legendre;
            ofile << setw(20) << setprecision(8) << Legendre_time;
            ofile << setw(23) << setprecision(8) << relative_error_leg;
            ofile << setw(22) << setprecision(8) << int_laguerre;
            ofile << setw(20) << setprecision(8) << Laguerre_time;
            ofile << setw(23) << setprecision(8) << relative_error_lag;
            ofile << setw(22) << setprecision(8) << Exact_value << endl;

        }
        //Loop ended
        ofile.close();}
    //----------------------------------------------------------------------------------------------------------------------
    // If test for either Legendre or Laguerre
    //----------------------------------------------------------------------------------------------------------------------
    else if (argc == 3){
        string outfilename;
        string method;
        outfilename = argv[1];
        method = argv[2];

        if (method == "Legendre"){
            double int_legendre, Legendre_time;
            GQ_legendre(a, b, n,int_legendre, Legendre_time);

            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Running Gaussian-Legendre quadrature"<< endl;
            cout  << setiosflags(ios::showpoint | ios::uppercase);
            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Gaussian-Legendre quadrature = "<< setw(20) << setprecision(15)  << int_legendre << endl;
            cout << "CPU-time for N = " << n <<":" << setw(20) << setprecision(15)  << Legendre_time << endl;
            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Excact result = "<< Exact_value << endl;
            cout << "------------------------------------------------------------------------------ " << endl;
        }
        else if (method == "Laguerre"){
            double int_laguerre,Laguerre_time;
            GQ_laguerre(n,PI, int_laguerre, Laguerre_time);

            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Running Gauss-Laguerre Quadrature" << endl;
            cout << setiosflags(ios::showpoint | ios::uppercase);
            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Gaussian-Laguerre quadrature = "<< setw(20) << setprecision(15)  << int_laguerre << endl;
            cout << "CPU-time for N = " << n <<":" << setw(20) << setprecision(15)  << Laguerre_time << endl;
            cout << "------------------------------------------------------------------------------ " << endl;
            cout << "Excact result = "<< Exact_value << endl;
            cout << "------------------------------------------------------------------------------ " << endl;
        }
        else if (method == "MonteCarlo"){
            cout << "Do you want to run [1] Brute Force or [2] Importance sampling? " << endl;
            int Number;
            cin >> Number;
            switch(Number){
                case 1:
                    double a, b;
                    cout << "Insert integration limits a and b" << endl;
                    cin >> a >> b;
                    MonteCarloBF(a,b,n);
                    break;

                case 2: MonteCarlo_IS(n);
            }
        }

    }

}  // end of main program

*/
}


/*    switch(Method){
        case 1:
            // Legendre
            double a,b;
            cout << "Read in the number of integration points" << endl;
            cin >> n;
            cout << "Read in integration limits" << endl;
            cin >> a >> b;

            string WriteToFile = "No";

            GQ_legendre(a, b, n, WriteToFile);
            break;

        case 2:
            // Laguerre
            cout << "Read in the number of integration points" << endl;
            cin >> n;

            GQ_laguerre(n,PI);
            break;

    } */
