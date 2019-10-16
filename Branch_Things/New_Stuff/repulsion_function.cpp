#include "Repulsion_function.h"
#include <cmath>
#define ZERO 1.0E-6


double Cartesian_Function(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2){

    double Denominator = sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)+(z_1-z_2)*(z_1-z_2));
    if (Denominator == 0.0){
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

double Spherical_Function(double r_1, double r_2, double theta_1, double theta_2, double phi_1, double phi_2){

    double cos_Beta = cos(theta_1)*cos(theta_2)+sin(theta_1)*sin(theta_2)*cos(phi_1-phi_2);
    double D = (r_1*r_1)+(r_2*r_2)-2*r_1*r_2*cos_Beta;

    if (D > ZERO){
        double Numerator = sin(theta_1)*sin(theta_2);
        double Denominator = sqrt(D);
        double Function = Numerator/Denominator;
        return Function;
    }
    else {
        return 0;

    }
}

double MC_Spherical_Function(double *x)
{   double r1 = x[0];
    double r2 = x[1];
    double theta1 = x[2];
    double theta2 = x[3];
    double phi1 = x[4];
    double phi2 = x[5];

    double num = r1*r1*r2*r2*sin(theta1)*sin(theta2);
    double cosB = cos(theta1)*cos(theta2) + sin(theta1)*sin(theta2)*cos(phi1 - phi2);
    double D = r1*r1 + r2*r2 - 2*r1*r2*cosB;
    double Denominator = sqrt(D);

    if(D < 1e-6){ // to avoid zero division
      return 0;
    }
    else{
        return num/Denominator;
    }
}

double integration_limit(double x_1, double y_1, double z_1){

    double r_1 = sqrt((x_1*x_1)+(y_1*y_1)+(z_1*z_1));
    double Exponent = exp(-4*(r_1));
    return Exponent;
}

#undef ZERO
