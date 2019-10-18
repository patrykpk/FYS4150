#ifndef REPULSION_FUNCTION_H
#define REPULSION_FUNCTION_H

double Cartesian_Function(double x_1, double y_1, double z_1, double x_2, double y_2, double z_2);
double Spherical_Function(double r_1, double r_2, double theta_1, double theta_2, double phi_1, double phi_2);
double MC_Spherical_Function(double *x);
double integration_limit(double x_1, double y_1, double z_1);
#endif // REPULSION_FUNCTION_H
