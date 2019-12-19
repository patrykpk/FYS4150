#define CATCH_CONFIG_MAIN
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <armadillo>
#include <string>

#include "catch.hpp"
#include "Solvers.h"
#include "Algorithms1D.h"
#include "Algorithms2D.h"

using namespace  std;
using namespace arma;


TEST_CASE("Checking if 1D CN gives the analytical steady-state answer at t=2 for dx=0.1 and dt=0.05."){

    double dx = 0.1;
    double dt = 0.05;   // Use this value in terminal
    double T = 2;       // Use this value in terminal
    int n = int(T/dt)+1;

    mat A = Diffusion_1D_CN(dx);

    // Analytical steady state f(x)=x
    CHECK(A(n-1,0) == Approx(0));
    CHECK(A(n-1,1) == Approx(0.111111));
    CHECK(A(n-1,2) == Approx(0.222222));
    CHECK(A(n-1,3) == Approx(0.333333));
    CHECK(A(n-1,4) == Approx(0.444444));
    CHECK(A(n-1,5) == Approx(0.555555));
    CHECK(A(n-1,6) == Approx(0.666666));
    CHECK(A(n-1,7) == Approx(0.777777));
    CHECK(A(n-1,8) == Approx(0.888888));
    CHECK(A(n-1,9) == Approx(1));
}


TEST_CASE("Check if Analytic2D correctly imposes initial condition at t=0."){

    mat Initial = zeros<mat>(101, 101);
    Analytic2D(Initial,100,0);

    CHECK(Initial(50,50)   == 1 );  // Mid point
    CHECK(Initial(0,0)     == 0 );  // SW corner
    CHECK(Initial(0,100)   == 0 );  // NW corner
    CHECK(Initial(100,0)   == 0 );  // SE corner
    CHECK(Initial(100,100) == 0 );  // NE corner
    CHECK(Initial(0,50)    == 0 );  // Mid S point
    CHECK(Initial(50,0)    == 0 );  // Mid W point
    CHECK(Initial(50,100)  == 0 );  // Mid N point
    CHECK(Initial(100,50)  == 0 );  // Mid E point

}
