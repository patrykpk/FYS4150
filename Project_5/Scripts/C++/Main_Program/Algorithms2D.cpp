#include "Solvers.h"
#include "Algorithms1D.h"
#include "Algorithms2D.h"

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

  // Outputs information to the terminal
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

      // Writes to file the difference between analytical and computed
      if (SingleOutput == 1){
        for (int i = 1; i <= TimeSteps; i++){
          ofile << u_cube.slice(i)-u_2dim.slice(i) << endl;
        }
      }
      // Writes to file the difference between analytical and computed
      // for the last value only
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

      // Writes the output to file 
      if (SingleOutput == 1){
        for (int i = 1; i <= TimeSteps; i++){
          ofile << u_2dim.slice(i) << endl;
        }
      }
      // Writes the last value to file
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

  // Outputs information to the terminal
  cout << "--------------------------------" << endl;
  cout << "Information for the calculation:" << endl;
  cout << "Amount of points N = " << N_2dim << endl;
  cout << "Step-Length \u0394x = " << dx_2d << endl;
  cout << "Step length \u0394t = " << dt_2 << endl;
  cout << "Total time T = " << Time << endl;
  cout << "Number of time iterations n = " << TimeSteps << endl; 
  cout << "Alpha \u03B1 = " << alpha_2dim << endl;
  cout << "--------------------------------" << endl;

  // Assigning values to matrix
  mat u_implicit = zeros<mat>(N_2dim+1,N_2dim+1);
  for (int i = 1; i < N_2dim; i++){
    for (int j = 1; j < N_2dim; j++){
      u_implicit(i,j) = sin(i*dx_2d*pi)*sin(j*pi*dx_2d);
    }
  }
  double tolerance = 1e-12;
  int Iteration_Limit = 10000;
  JacobiSolv(u_implicit, dx_2d, dt_2, tolerance, Iteration_Limit, Time);
  return;
}

void ForwardEuler_2D(cube &u, double alpha, int TimeSteps, int N){
  // Performing Forward Euler
  // Assigning a value to the 3-dimensional array
  for (int t = 0; t < TimeSteps; t++){
    for (int i = 1; i < N; i++){
      for (int j = 1; j < N; j++){
        u(i,j,t+1) = u(i,j,t)+alpha*(u(i+1,j,t)+u(i-1,j,t)+u(i,j+1,t)+u(i,j-1,t)-4*u(i,j,t));
      }
    }
  }
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