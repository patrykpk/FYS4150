#include "Solvers.h"
#include "Algorithms1D.h"
#include "Algorithms2D.h"

void Diffusion_1D_FE(double dx){
  ofstream ofile;
  string filename = "FE_1D_";

  string Add_String = to_string(dx);
  filename.append(Add_String+".txt");

  ofile.open(filename);

  // Parameters that will be used
  int N = int(1.0/(dx));      // Amount of points for 1D
  double dt = 0.5*dx*dx;      // Deciding step length for time based on stability condition
  double alpha = dt/(dx*dx);  // Assigning the value for alpha

  // Final time for the calculation
  double T;
  cout << "Choose how long you want to run the calculation (s):" << endl;
  cin >> T;

  int n = int(T/dt)+1;
  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N << endl;
  cout << "Step-Length \u0394x = " << dx << endl;
  cout << "Step length \u0394t = " << dt << endl;
  cout << "Total time T = " << T << endl;
  cout << "Number of time iterations n = " << n << endl; 
  cout << "Alpha \u03B1 = " << alpha << endl;
  cout << "--------------------------------" << endl;

  string Choice;
  cout << "Would you like to save the values to a file (Y/N)?\n";
  cin >> Choice;

  // Generating n x N matrix filled with zeros
  mat u = zeros<mat>(n,N);

  // Assigning the last element to be 1 (All other elements are 0)
  for (int i = 0; i < n; i++){
    u(i,N-1) = 1;
  }

  for (int i = 0; i < n-1; i++) {
    for (int j = 1; j < N - 1; j++) {
        u(i+1, j) = alpha*(u(i, j+1) + u(i, j-1)) + (1 - 2*alpha)*u(i, j);
    }
  }
  string Terminal;
  cout << "Do you want to print out the results to the terminal? (Y/N)\n";
  cin >> Terminal;

  if (Terminal == "Y"){
    cout << u << endl;
  }

  if (Choice == "Y"){
    ofile << u << endl;
    ofile.close();
  }
  return;
}

void Diffusion_1D_BE(double dx){
  ofstream ofile;
  string filename = "BE_1D_";

  string Add_String = to_string(dx);
  filename.append(Add_String+".txt");

  ofile.open(filename);

  // Parameters that will be used
  int N = int(1.0/(dx));      // Amount of points for 1D
  double dt;                  // Step length for time (No stability condition required)
  cout << "Choose step length for time \u0394t" << endl;
  cin >> dt;
  double alpha = dt/(dx*dx);  // Assigning the value for alpha


  // Final time for the calculation
  double T;
  cout << "Choose how long you want to run the calculation (s):" << endl;
  cin >> T;


  int n = int(T/dt)+1;
  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N << endl;
  cout << "Step-Length \u0394x = " << dx << endl;
  cout << "Step length \u0394t = " << dt << endl;
  cout << "Total time T = " << T << endl;
  cout << "Number of time iterations n = " << n << endl; 
  cout << "Alpha \u03B1 = " << alpha << endl;
  cout << "--------------------------------" << endl;

  string Choice;
  cout << "Would you like to save the values to a file (Y/N)?\n";
  cin >> Choice;

  // Generating n x N matrix filled with zeros
  mat u = zeros<mat>(n,N);

  // Assigning the last element to be 1 (All other elements are 0)
  for (int i = 0; i < n; i++){
    u(i,N-1) = 1;
  }

  double Diagonal_d = 1+2*alpha; // Value of the elements along the diagonal
  double Offdiagonal_b = -alpha; // Elements above and below the diagonal

  rowvec u_new(N);

  for (int i = 1; i < n; i++) {
    TridiagSolv(u_new, u.row(i-1), N, Offdiagonal_b, Diagonal_d);
    u.row(i) = u_new;

  }
  string Terminal;
  cout << "Do you want to print out the results to the terminal? (Y/N)\n";
  cin >> Terminal;

  if (Terminal == "Y"){
    cout << u << endl;
  }
  
  if (Choice == "Y"){
    ofile << u << endl;
    ofile.close();
  }
  return;
}

void Diffusion_1D_CN(double dx){
  ofstream ofile;
  string filename = "CN_1D_";

  string Add_String = to_string(dx);
  filename.append(Add_String+".txt");

  ofile.open(filename);

  // Parameters that will be used
  int N = int(1.0/(dx));      // Amount of points for 1D
  double dt;                  // Step length for time (No stability condition required)
  cout << "Choose step length for time \u0394t" << endl;
  cin >> dt;
  double alpha = dt/(dx*dx);  // Assigning the value for alpha


  // Final time for the calculation
  double T;
  cout << "Choose how long you want to run the calculation (s):" << endl;
  cin >> T;


  int n = int(T/dt)+1;
  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N << endl;
  cout << "Step-Length \u0394x = " << dx << endl;
  cout << "Step length \u0394t = " << dt << endl;
  cout << "Total time T = " << T << endl;
  cout << "Number of time iterations n = " << n << endl; 
  cout << "Alpha \u03B1 = " << alpha << endl;
  cout << "--------------------------------" << endl;

  // Generating n x N matrix filled with zeros
  mat u = zeros<mat>(n,N);

  // Assigning the last element to be 1 (All other elements are 0)
  for (int i = 0; i < n; i++){
    u(i,N-1) = 1;
  }

  double Diagonal_d = 2+2*alpha; // Value of the elements along the diagonal
  double Offdiagonal_b = -alpha; // Elements above and below the diagonal

  rowvec temp_u_row(N);
  rowvec u_val = u.row(0);

  double FE_alpha = 2-2*alpha;

  for (int i = 1; i < n; i++){
    temp_u_row = u.row(i-1);
    for (int j = 1; j < N-1; j++){
      u_val(j) = alpha*(temp_u_row(j+1)+temp_u_row(j-1))+FE_alpha*temp_u_row(j);
    }
    TridiagSolv(temp_u_row, u_val, N, -alpha, 2+2*alpha);
    u.row(i) = temp_u_row;
  }


  string Choice;
  cout << "Would you like to save the values to a file (Y/N)?\n";
  cin >> Choice;

  string Terminal;
  cout << "Do you want to print out the results to the terminal? (Y/N)\n";
  cin >> Terminal;

  if (Terminal == "Y"){
    cout << u << endl;
  }

  if (Choice == "Y"){
    ofile << u << endl;
    ofile.close();
  }
  return;
}