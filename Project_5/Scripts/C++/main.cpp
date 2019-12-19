#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>

using namespace  std;
using namespace arma;

void Diffusion_1D_FE(double dx);
void Diffusion_1D_BE(double dx);
void Diffusion_1D_CN(double dx);

void Analytic2D(mat &u, int N, double t);
void Explicit_2D(double dx_2d);
void ForwardEuler_2D(cube &u, double alpha, int TimeSteps, int N);
void Implicit_2D(double dx_2d);

void JacobiSolv(mat &u, double dx, double dt, double tol, int Iteration_Limit, double MaxTime);
void TridiagSolv(rowvec &x, rowvec y, int N, double b, double d);

int main(){
  int DiffDim;
  int Algorithm;

  // Asking for either Diffusion in 1D or 2D
  cout << "Would you like to run the 1D or 2D case?\n";
  cout << "Choose by writing either 1 or 2:\n";
  cin >> DiffDim; //Diffusion dimension


  if (DiffDim == 1){
    cout << "What algorithm would you like to run?\n";
    cout << "Forward Euler[1], Backward Euler[2] or Crank-Nicolson[3]\n";
    cin >> Algorithm;

    double dx;
    cout << "Choose step-length for \u0394x:\n"; // Asks for Δx in the terminal
    cin >> dx;

    // Forward Euler
    if (Algorithm == 1){
      Diffusion_1D_FE(dx);
    }
    // Backward Euler
    else if (Algorithm == 2){
      Diffusion_1D_BE(dx);
    }
    // Crank-Nicolson
    else if (Algorithm == 3){
      Diffusion_1D_CN(dx);
    }

  }
  //-----------------------Two Dimensions----------------------------------
  if (DiffDim == 2){
    int Scheme;
    cout << "Dimension 2D\n" << endl;
    cout << "Would you like to run Explicit[1] or Implicit[2] scheme for 2D?" << endl;
    cin >> Scheme;

    double dx_2d;
    cout << "Choose step-length for \u0394x:\n";
    cin >> dx_2d;
    if (Scheme == 1){
      Explicit_2D(dx_2d);
    }
    else if (Scheme == 2){
      Implicit_2D(dx_2d);
    }
  }

  return 0;
}

void TridiagSolv(rowvec &x, rowvec y, int N, double b, double d){

  vec Diagonal = zeros<vec>(N);
  Diagonal(1) = d;

  for (int i = 2; i < N-1; i++){
    Diagonal(i) = d - (b*b)/Diagonal(i-1); // Updating the diagonal
    y(i) = y(i)-(y(i-1)*b)/Diagonal(i-1);  // Updating right side
  }

  x(0) = 0; 
  x(N-1) = 1;

  for (int i = N-2; i > 0; i--){
    x(i) = (y(i)-b*x(i+1))/Diagonal(i);    // Numerical solution for x
  }
  

  return;
}

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

void Explicit_2D(double dx_2d){
  ofstream ofile;
  double pi = 4*atan(1);
  double dt_2;

  dt_2 = 0.25*dx_2d*dx_2d;
  double alpha_2dim = dt_2/(dx_2d*dx_2d);
  int N_2dim = int(1.0/dx_2d);

  // Final time for the calculation
  double T;
  cout << "Choose how long you want to run the calculation (s):" << endl;
  cin >> T;

  int TimeSteps = int(T/dt_2);

  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N_2dim << endl;
  cout << "Step-Length \u0394x = " << dx_2d << endl;
  cout << "Step length \u0394t = " << dt_2 << endl;
  cout << "Total time T = " << T << endl;
  cout << "Number of time iterations n = " << TimeSteps << endl; 
  cout << "Alpha \u03B1 = " << alpha_2dim << endl;
  cout << "--------------------------------" << endl;

  cube u_2dim = zeros<cube>(N_2dim+1,N_2dim+1,TimeSteps+1);

  for (int i = 1; i < N_2dim; i++){
    for (int j = 1; j < N_2dim; j++){
      u_2dim(i,j,0) = sin(i*dx_2d*pi)*sin(j*pi*dx_2d);
    }
  }
  //---------------------------------------------------------
  mat u_analytic = zeros<mat>(N_2dim+1, N_2dim+1);
  cube u_cube = zeros<cube>(N_2dim+1, N_2dim+1, TimeSteps+1);
  double Time;
  for (int t = 0; t <= TimeSteps; t++){
    Time = t*dt_2;
    Analytic2D(u_analytic, N_2dim, Time);
    u_cube.slice(t) = u_analytic;
  }
  //--------------------------------------------------------

  string Choice;
  cout << "Would you like to save the values to a file (Y/N)?\n";
  cin >> Choice;

  if (Choice == "Y"){
    string Terminal;
    cout << "Do you want to print out the results to the terminal? (Y/N)\n";
    cin >> Terminal;

    string Compare;
    cout << "Compare Analytic vs Explicit?(Y/N)\n";
    cin >> Compare;

    if (Compare == "Y"){
      ofile.open("Compare_Explicit_vs_Analytic_"+to_string(dx_2d)+".txt");
      ForwardEuler_2D(u_2dim, alpha_2dim, TimeSteps, N_2dim);
      int SingleOutput;
      cout << "Output all values[1] or only the last one[2]?" << endl;
      cin >> SingleOutput;
      if (SingleOutput == 1){
        for (int i = 1; i <= TimeSteps; i++){
          ofile << u_cube.slice(i)-u_2dim.slice(i) << endl;
        }
      }
      else if (SingleOutput == 2){
        ofile << u_cube.slice(TimeSteps)-u_2dim.slice(TimeSteps) << endl;
      }
    ofile.close();
    }
    else if (Compare == "N"){
      ofile.open("Explicit2D_"+to_string(dx_2d)+".txt");
      ForwardEuler_2D(u_2dim, alpha_2dim, TimeSteps, N_2dim);
      int SingleOutput;
      cout << "Output all values[1] or only the last one[2]?" << endl;
      cin >> SingleOutput;
      if (SingleOutput == 1){
        for (int i = 1; i <= TimeSteps; i++){
          ofile << u_2dim.slice(i) << endl;
        }
      }
      else if (SingleOutput == 2){
        ofile << u_2dim.slice(TimeSteps);
      }
    ofile.close();
    }

    if (Terminal == "Y"){
      cout << u_2dim << endl;
    }
  }

  return;
}

void Implicit_2D(double dx_2d){
  double pi = 4*atan(1);
  double dt_2;
  cout << "Choose step length for time \u0394t" << endl;
  cin >> dt_2;
  double alpha_2dim = dt_2/dx_2d/dx_2d;

  int N_2dim = int(1.0/dx_2d);

  // Final time for the calculation
  double Time;
  cout << "Choose how long you want to run the calculation (s):" << endl;
  cin >> Time;

  int TimeSteps = int(Time/dt_2);

  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N_2dim << endl;
  cout << "Step-Length \u0394x = " << dx_2d << endl;
  cout << "Step length \u0394t = " << dt_2 << endl;
  cout << "Total time T = " << Time << endl;
  cout << "Number of time iterations n = " << TimeSteps << endl; 
  cout << "Alpha \u03B1 = " << alpha_2dim << endl;
  cout << "--------------------------------" << endl;


  mat u_implicit = zeros<mat>(N_2dim+1,N_2dim+1);
  for (int i = 1; i < N_2dim; i++){
    for (int j = 1; j < N_2dim; j++){
      u_implicit(i,j) = sin(i*dx_2d*pi)*sin(j*pi*dx_2d);
    }
  }

  cout << u_implicit << endl;

  double tolerance = 1e-12;
  int maxiter = 10000;
  JacobiSolv(u_implicit, dx_2d, dt_2, tolerance, maxiter, Time);
  return;
}

void ForwardEuler_2D(cube &u, double alpha, int TimeSteps, int N){
  for (int t = 0; t < TimeSteps; t++){
    for (int i = 1; i < N; i++){
      for (int j = 1; j < N; j++){
        u(i,j,t+1) = u(i,j,t)+alpha*(u(i+1,j,t)+u(i-1,j,t)+u(i,j+1,t)+u(i,j-1,t)-4*u(i,j,t));
      }
    }
  }
  return;
}


void JacobiSolv(mat &u, double dx, double dt, double tol, int Iteration_Limit, double MaxTime){
  mat Previous_u = u;
  ofstream ofile;

  
  int T = int(MaxTime/dt)+1;
  int N = int(1/dx)+1;

  double alpha = dt/(dx*dx);
  double MatSize = N*N;
  double delta;
  double Difference;

  //--------------------------------------------
  mat u_analytic = zeros<mat>(N, N);
  cube u_cube = zeros<cube>(N, N, T+1);
  double Time;
  for (int t = 0; t <= T; t++){
    Time = t*dt;
    Analytic2D(u_analytic, N-1, Time);
    u_cube.slice(t) = u_analytic;
  }
  //--------------------------------------------

  string Compare;
  cout << "Compare Analytic vs Implicit?(Y/N)\n";
  cin >> Compare;

  if (Compare == "Y"){
    ofile.open("Compare_Implicit2D_vs_Analytic_"+to_string(dx)+".txt");
  }
  else if (Compare == "N"){
    ofile.open("Implicit2D_"+to_string(dx)+".txt");
  }
  //ofile << u << endl;

  int SingleOutput;
  cout << "Output all values[1] or only the last one[2]?" << endl;
  cin >> SingleOutput;

  for (int t=0; t<=T; t++){
    int iterations = 0;
    Difference = 1;

    mat u_guess = ones<mat>(N,N);
    while (iterations < Iteration_Limit && Difference > tol){
      Difference = 0;

      for (int j=1; j<N-1; j++){
        for (int i = 1; i <N-1; i++){
          delta = (u_guess(i,j+1)+u_guess(i,j-1)+u_guess(i+1,j)+u_guess(i-1,j));
          u(i,j) = 1.0/(1.0+4*alpha)*(alpha*delta+Previous_u(i,j));
          Difference += fabs(u(i,j)-u_guess(i,j));
        }
      }
      u_guess = u;
      Difference /= MatSize;
      iterations++;
    }
    Previous_u = u;   // Last time step
    
    mat Analytic = u_cube.slice(t);
    if (SingleOutput == 1){
      if (Compare == "Y"){
        ofile << (Analytic-u) << endl;
      }
      else if (Compare == "N"){
        ofile << u << endl;
      }
    }
    else if (SingleOutput == 2 && t==T){
      if (Compare == "Y"){
        ofile << (Analytic-u) << endl;
      }
      else if (Compare == "N"){
        ofile << u << endl;
      }

    }


  }
  ofile.close();
  return;

}

void Analytic2D(mat &u, int N, double t){
  double pi = 4*atan(1);

  vec x = linspace<vec>(0,1,N+1);
  vec y = linspace<vec>(0,1,N+1);

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      u(i,j) = sin(pi*x(i))*sin(pi*y(j))*exp(-2*pi*pi*t);
    }
  }
}