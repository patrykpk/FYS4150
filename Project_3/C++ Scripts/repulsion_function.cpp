#include "repulsion_function.h"
#include <cmath>

double Cartesian_Function(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2){
    double alpha = 2.0;

    double Denominator = sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)+(z_1-z_2)*(z_1-z_2));
    if (Denominator == 0.0){
        return 0;
    }
    else{
        // evaluate the different terms of the exponential
        double r_1 = sqrt((x_1*x_1)+(y_1*y_1)+(z_1*z_1));
        double r_2 = sqrt((x_2*x_2)+(y_2*y_2)+(z_2*z_2));

        double Exponent = exp(-2*alpha*(r_1+r_2));


        double Function = Exponent/Denominator;
        return Function;
    }
}
