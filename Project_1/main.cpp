# include <iostream>
# include <fstream>
# include <iomanip>
# include <cmath>
#include <string>
#include <armadillo>
#include "time.h"

#include "algorithms.h"

using namespace arma;
using namespace std;
ofstream ofile;


double Solution(double x) {return 1.0-(1.0-exp(-10.0))*x-exp(-10.0*x);}

double f(double x) {return 100*exp(-10*x);}


int main(int argc, char* argv[]) {

    char *outfilename;
    int n;

    if( argc <= 2 ){
      cout << "Error occured: " << argv[0] <<
          " read also output filename, n (int) and if you want to run LU on same line" << endl;
      exit(1);
    }
    else{
      outfilename = argv[1];
      n = atoi(argv[2]);
      char* Add_Amount = argv[2];
      string str = ".txt";
      char* Extension = &str[0];

      strcat(outfilename,Add_Amount);
      strcat(outfilename, Extension);
    }

    double h = 1.0/(n+1.0);
    double *x = new double[n+2];
    double *u = new double[n+2]; // Analytical solution

    for (int i=0; i<=n+1; i++) {
        x[i] = i*h;
        u[i] = Solution(x[i]);
    }
    u[0] = 0;
    u[n+1] = 0;

    double *v = new double[n+2];
    v = General_Algorithm(x, f, h, n);

    double *v_special = new double[n+2];
    v_special = Special_Algorithm(x, f, h, n);

    if (argv[3]){
        cout << "Running LU" << "\n";
        LU_Decomp_Arma(x, f, h, n);
    } else if (!argv[3]){
        cout << "--------------"<< "\n";
        cout << "Not running LU" << endl;
        cout << "--------------"<< "\n";
        cout << "If you want to run LU decomposition enter an arbitrary third argument,\nbut keep in mind that the program will crash at n = 10^5" << "\n";
        //exit(1);
    }

    // Open file and write results to file:
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "       x:             u(x):          v(x):          v_special         RelativeError_General        RelativeError_Special" << endl;
    for (int i=0;i<=n+1;i++) {
      double RelativeError_S = log10(fabs((u[i]-v_special[i])/u[i]));
      double RelativeError_G = log10(fabs((u[i]-v[i])/u[i]));
       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << u[i];
       ofile << setw(15) << setprecision(8) << v[i];
       ofile << setw(15) << setprecision(8) << v_special[i];
       ofile << setw(15) << setprecision(8) << RelativeError_G;
       ofile << setw(15) << setprecision(8) << RelativeError_S << endl;
    }
    ofile.close();


    delete [] x;
    delete [] u;
    delete [] v;
    delete [] v_special;


    return 0;
}
