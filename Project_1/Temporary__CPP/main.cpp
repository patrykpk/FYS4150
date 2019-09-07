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
    double *d = new double[n+1];

    int *a = new int[n+1];
    int *b = new int[n+1];
    int *c = new int[n+1];

    double *b_tilde = new double[n+1];


    double *u = new double[n+2]; // Analytical solution

    double *v = new double[n+2]; // Numerical solution

    double *d_tilde = new double[n+1]; // Vector on right hand side updated

    v[0] = 0;

    for (int i=0; i<=n+1; i++) {
        x[i] = i*h;
        u[i] = Solution(x[i]);
        //std::cout << u[i] << endl;
    }

    General_Algorithm(x, f, a, b, c, d, d_tilde, b_tilde, v, h, n);

    double *b_special = new double[n+1]; // Diagonal element
    double *v_special = new double[n+2]; // Numerical solution
    double *f_special = new double[n+1]; // Vector on right hand side updated

    Special_Algorithm(x, f, d, b_special, v_special, f_special, h, n);

    if (argv[3]){
        cout << "Running LU" << "\n";
        LU_Decomp_Arma(x, f, h, n);
    } else if (!argv[3]){
        cout << "Not running LU";
        cout << "Error: You have to declare if you want to run LU. Input must be either [Y] or [N]" << "\n";
        exit(1);
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
    delete [] d;
    delete [] a;
    delete [] b;
    delete [] c;
    delete [] u;
    delete [] v;
    delete [] d_tilde;
    delete [] b_special;
    delete [] v_special;
    delete [] f_special;

    return 0;
}
