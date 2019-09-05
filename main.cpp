# include <iostream>
# include <fstream>
# include <iomanip>
# include <cmath>
#include <string>
#include <armadillo>
#include "time.h"

using namespace arma;
using namespace std;
ofstream ofile;





// Declaring two functions that will be used:
double Solution(double x) {return 1.0-(1-exp(-10))*x-exp(-10*x);}

double f(double x) {return 100*exp(-10*x);}

// Main program reads filename and n from command line:
int main(int argc, char* argv[]) {


    // declarations of variables


    // start = clock();
    // your code is here, do something and then get final time
    // finish = clock();
    // ( (finish - start)/CLOCKS_PER_SEC );


    // Declaration of initial variables:
    char *outfilename;
    int n;

    // Read in output file and n,
    // abort if there are too few command-line arguments:
    if( argc <= 2 ){
      cout << "Bad Usage: " << argv[0] <<
          " read also output file and n (int) on same line" << endl;
      exit(1);
    }
    else{
      outfilename = argv[1]; // first command line argument.
      n = atoi(argv[2]);  // second command line argument.
    }

    // Constants of the problem:
    double h = 1.0/(n+1.0);
    double hh = h*h;
    double *x = new double[n+2];
    double *d_tilde = new double[n+1]; // construction with n+1 points to make
                                       // indexing close to mathematics.
    d_tilde[0] = 0;

    // The constituents of the tridiagonal matrix A:
    // Zeroth element not needed, but included to make indexing easy:
    int *a = new int[n+1];
    int *b = new int[n+1];
    int *c = new int[n+1];

    // Temporal variabel in Gaussian elimination:
    double *b_tilde = new double[n+1]; // Updated diagonal element

    // Real solution and approximated one:
    double *u = new double[n+2]; // Analytical solution

    double *v = new double[n+2]; // Numerical solution

    double *d = new double[n+1]; // Vector on right hand side updated

    // Including extra points to make the indexing easy:
    u[0] = 0;
    v[0] = 0;

    // Filling up x-array, making x[0] = 0 and x[n+1] = 1:
    for (int i=0; i<=n+1; i++) {
        x[i] = i*h;
        // Could print results to check:
        //cout << "x = " << x[i] << " and " << "h^2*f(x) = " << h*h*f(x[i]) << endl;
    }

    // Filling up dle array, i.e. right hand side of equation:
    for (int i=1; i<=n; i++) {
        d[i] = hh*f(x[i]);
        // Could print here to check:
        //cout << "d = " << d[i] << "for x = " << x[i] << endl;
        u[i] = Solution(x[i]);
        //cout << "u = " << u[i] << " for x = " << x[i] <<  endl;
        b[i] = 2;
        a[i] = -1;
        c[i] = -1;
    }
    c[n] = 0;
    a[1] = 0;



    // General algorithm

    clock_t start, finish; // declare start and final time
    start = clock();
    // Algorithm for finding v:
    // a(i)*v(i-1) + b(i)*v(i) + c(i)*v(i+1) = d(i)
    // Row reduction; forward substitution:
    b_tilde[1] = b[1];
    d_tilde[1] = d[1];
    for (int i=2;i<=n;i++) {
       // Temporary value needed also in next loop:
      // b_tilde[i] = c[i-1]/b_temp;
       // Updating diagonal element:
       b_tilde[i] = b[i] - (a[i]*c[i-1])/b_tilde[i-1];
       // Updating right hand side of matrix equation:
       d_tilde[i] = d[i]-(d_tilde[i-1]*a[i])/b_tilde[i-1];
    }

    // Row reduction; backward substition:
    // Defining v[n] = d_tilde[n]/b_tilde[n]
    v[n] = (d_tilde[n])/b_tilde[n];
    for (int i=n;i>=1;i--) {
        v[i-1] = (d_tilde[i-1]-c[i-1]*v[i])/b_tilde[i-1];
    }

    finish = clock();
    double time_general = (double) (finish - start)/((double) CLOCKS_PER_SEC);
    printf("Time used by general algorithm: %.10f\n", time_general);


    // Special algorithm

    // Temporal variabel in Gaussian elimination:
    double *b_special = new double[n+1]; // Diagonal element

    double *v_special = new double[n+2]; // Numerical solution

    double *d_special = new double[n+1]; // Vector on right hand side updated


    for (int i = 1; i <= n; i++) {
        // Updating diagonal element:
        b_special[i] = (i+1.0)/((double) i);
    }

    start = clock();

    d_special[1] = hh*f(x[1]);
    for (int i = 2; i <= n; i++) {
        // Updating right hand side of matrix equation:
        d_special[i] = d[i] + ((i-1.0)*d_special[i-1])/((double) i);
    }

   // Row reduction; backward substition:
   // Defining v[n] = f_special[n]/b_special[n]
   v_special[n] = d_special[n]/b_special[n];
   for (int i = n; i >= 2; i--) {
   v_special[i-1] = ((i-1.0)/((double)i)) * (d_special[i-1]+v_special[i]);
   }

   finish = clock();
   double time_special = (double) (finish - start)/((double) CLOCKS_PER_SEC);
   printf("Time used by special algorithm: %.10f\n", time_special);



 /*

   // LU-DECOMPOSITION (Egil)

         // Define matrix and arrays
         mat A = zeros<mat>(n,n);  vec diagonal_lu(n); vec solution_lu(n+2);
         // Set up the endpoints of v
         solution_lu(0) = 0; solution_lu(n+1) = 0;
         // Setup of the matrix and b_tilde
         A(n-1,n-1) = 2.0; diagonal_lu(n-1) = h*h*f(x[n]);
         for (int i = 0; i <= n-2; i++){
           A(i,i+1)  = -1.0;
           A(i,i)    = 2.0;
           A(i+1,i)  = -1.0;
       diagonal_lu(i) = h*h*f(x[i+1]);
         }

         // Run and time
         start = clock();
         // Solve Av = b
         solution_lu(span(1,n)) = solve(A,diagonal_lu);
         finish = clock();
         double time_lu = (double) (finish - start)/(CLOCKS_PER_SEC);

         printf("Time used by LU-decomposition algorithm: %.4f\n", time_lu);
 */

// /*

   // LU-Decomposition (Morten)

   mat A = zeros<mat>(n,n);
   // Set up arrays for the simple case
   vec d_lu(n);  // d_lu is the vector on the right hand side
   vec x_lu(n);  // x_lu is the x-values for the function.
   A(0,0) = 2.0;  A(0,1) = -1;  x_lu(0) = h;  d_lu(0) =  hh*f(x_lu(0));
   x_lu(n-1) = x_lu(0)+(n-1)*h; d_lu(n-1) = hh*f(x_lu(n-1));
   for (int i = 1; i < n-1; i++){
    x_lu(i) = x_lu(i-1)+h;
    d_lu(i) = hh*f(x_lu(i));
    A(i,i-1)  = -1.0;
    A(i,i)    = 2.0;
    A(i,i+1)  = -1.0;
   }
   A(n-1,n-1) = 2.0; A(n-2,n-1) = -1.0; A(n-1,n-2) = -1.0;

   // solve Av = d
   vec v_lu  = solve(A,d_lu);

   finish = clock();
   double time_lu = (double) (finish - start)/(CLOCKS_PER_SEC);

    printf("Time used by LU-decomposition algorithm: %.4f\n", time_lu);

// */
    // Open file and write results to file:
    ofile.open(outfilename);
    ofile << setiosflags(ios::showpoint | ios::uppercase);
    ofile << "       x:             u(x):          v(x):          v_special:       LU:       RelativeError:" << endl;
    for (int i=1;i<=n;i++) {
      double RelativeError = log10(fabs((u[i]-v_special[i])/u[i]));
       ofile << setw(15) << setprecision(8) << x[i];
       ofile << setw(15) << setprecision(8) << u[i];
       ofile << setw(15) << setprecision(8) << v[i];
       ofile << setw(15) << setprecision(8) << v_special[i];
       ofile << setw(15) << setprecision(8) << v_lu[i-1];
       ofile << setw(15) << setprecision(8) << RelativeError << endl;
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
    delete [] d_special;

    return 0;
}
