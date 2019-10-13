#include "repulsion_function.h"
#include <cmath>
#include "monte_carlo.h"

#define   ZERO       1.0E-7

#include <iostream>

using namespace std;

double Cartesian_Function(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2){

    double Denominator = sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)+(z_1-z_2)*(z_1-z_2));


    if (Denominator < ZERO){
        return 0;
    }
    else{
        // evaluate the different terms of the exponential
        double r_1 = sqrt((x_1*x_1)+(y_1*y_1)+(z_1*z_1));
        double r_2 = sqrt((x_2*x_2)+(y_2*y_2)+(z_2*z_2));

        double Exponent = exp(-4*(r_1+r_2));


        double Function = Exponent/Denominator;
        return Function;
    }
}


double Brute_Force_MC(double *x){
    double Denominator = sqrt((x[0]-x[3])*(x[0]-x[3])+(x[1]-x[4])*(x[1]-x[4])+(x[2]-x[5])*(x[2]-x[5]));

    if (Denominator > ZERO){
        // evaluate the different terms of the exponential
        double r_1 = sqrt((x[0]*x[0])+(x[1]*x[1])+(x[2]*x[2]));
        double r_2 = sqrt((x[3]*x[3])+(x[4]*x[4])+(x[5]*x[5]));

        double Exponent = exp(-4*(r_1+r_2));


        double Function = Exponent/Denominator;
        return Function;
    }
    else{
        return 0;

    }

}

double Spherical_Function(double r_1, double r_2, double theta_1, double theta_2, double phi_1, double phi_2){

    double cos_Beta = cos(theta_1)*cos(theta_2)+sin(theta_1)*sin(theta_2)*cos(phi_1-phi_2);

    double Denominator = sqrt((r_1*r_1)+(r_2*r_2)-2*r_1*r_2*cos_Beta);
    if (Denominator > ZERO){
        double Exponent = exp(-3*(r_1+r_2));
        double Numerator = Exponent*(r_1*r_1)*(r_2*r_2)*sin(theta_1)*sin(theta_2);
        double Function = Numerator/Denominator;
        return Function;
    }
    else {
        return 0;

    }
}
#undef ZERO;
