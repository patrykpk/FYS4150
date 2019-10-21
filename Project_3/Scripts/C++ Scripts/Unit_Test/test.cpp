#define CATCH_CONFIG_MAIN
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

#include "catch.hpp"
#include "lib.h"

using namespace std;

TEST_CASE("Checking if gauleg finds correct roots for 5th degree Legendre polynomial"){

    int a = -1;
    int b = 1;
    int n = 5;

    double *x = new double [n];
    double *w = new double [n];

    gauss_legendre(a,b,x,w,n);

    // Checking for tabulated roots
    CHECK ( x[0] == Approx(-0.9061798459));
    CHECK ( x[1] == Approx(-0.5384693101));
    CHECK ( x[2] == Approx(0));
    CHECK ( x[3] == Approx(0.5384693101));
    CHECK ( x[4] == Approx(0.9061798459));
}


TEST_CASE("Checking if gauss_laguerre finds the correct roots for 4th degree Laguerre polynomial"){

    int n = 4;
    double *x = new double [n];
    double *w = new double [n];
    double alpha = 0;

    gauss_laguerre(x,w,n,alpha);

    // Checking for tabulated roots
    CHECK ( x[1] == Approx(0.3225476896));
    CHECK ( x[2] == Approx(1.745761102));
    CHECK ( x[3] == Approx(4.536620297));
    CHECK ( x[4] == Approx(9.395070912));
}
