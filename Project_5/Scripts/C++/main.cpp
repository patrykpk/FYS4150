#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <armadillo>
#include <string>

#include "Solvers.h"
#include "Algorithms1D.h"
#include "Algorithms2D.h"

using namespace  std;
using namespace arma;


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
