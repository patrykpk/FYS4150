#include "Solvers.h"
#include "Algorithms1D.h"
#include "Algorithms2D.h"

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