#include "Monte_Carlo.h"
#include "Coordinates.h"
#include <armadillo>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <omp.h>
#include <ctime>


using namespace arma;
using namespace std;


//double integrand_c(double x_1, double y_1,double z_1,double x_2,double y_2,double z_2);
//double integrand_d(double r1, double r2,double costheta1,double costheta2,double phi1,double phi2);
double ran0(long *idum);
double ran1(long *idum);
double ran2(long *idum);
double ran3(long *idum);

void MC(double a, double b, int N)
{

    double fx,r1,r2, theta1, theta2,phi1,phi2, exact,lambda;
    double int_bMC, int_MC, sum_sigma, var_bMC, var_MC, std_bMC, std_MC;
    long idum = -1;
    double x_1, x_2, y_1, y_2, z_1, z_2;
    const double PI = 4*atan(1);
    double jacobi_bmc = pow((b-a),6);
    double Jacobi_D = 4*pow(PI,4)/16.0;

    double y;
    double x[6];

    exact = (5*PI*PI)/(16*16);

    //rowvec y = zeros<rowvec>(6);    // making space for 6 random numbers in [a,b]

    clock_t t0, t1;

    //arma_rng::set_seed_random(); // change RNG seed

//  computation loop: Brute force monte carlo
    t0 = clock();

    fx = 0; sum_sigma= 0;
    //#pragma omp parallel for private(y) reduction(+:fx) reduction(+:sum_sigma)
    for (int i=1; i <= N; i++)
    {
            x_1=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )
            x_2=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )
            y_1=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )
            y_2=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )
            z_1=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )
            z_2=ran0(&idum)*(b-a)+a; // transformation to [a,b] (general normal dist. )

            //rowvec x = randu<rowvec>(6);      // six random numbers in [0,1]
            //y = a + x*(b-a);

            fx += Cartesian_Function(x_1, x_2, y_1, y_2, z_1, z_2);
            sum_sigma += Cartesian_Function(x_1, x_2, y_1, y_2, z_1, z_2)*Cartesian_Function(x_1, x_2, y_1, y_2, z_1, z_2);
            //fx += Cartesian_Function(y(0),y(1),y(2),y(3),y(4),y(5));
            //sum_sigma += Cartesian_Function(y(0),y(1),y(2),y(3),y(4),y(5))*Cartesian_Function(y(0),y(1),y(2),y(3),y(4),y(5));
    }

    t1 = clock();

    sum_sigma = sum_sigma/((double) N);
    var_bMC = sum_sigma-(fx/((double) N))*(fx/((double) N));
    int_bMC = (fx/((double) N))*pow((b-a),6);
    std_bMC = sqrt(var_bMC/((double)N));

    //arma_rng::set_seed_random(); // change RNG seed

/*
//  computation loop: Monte carlo using importance sampling
    t2 = std::clock();
    lambda = 0.25;     // exp. weight
    fx = 0;  sum_sigma= 0;
    //#pragma omp parallel for private(y) reduction(+:fx) reduction(+:sum_sigma)
    for (long int i=1; i <= N; i++)
    {

            //rowvec x = randu<rowvec>(6);    // draw six random numbers in [0,1]

            r1 = -lambda*log(1-ran0(&idum));       // map to exp.dist [0,inf]
            r2 = -lambda*log(1-ran0(&idum));       // map to exp.dist [0,inf]

            theta1 = PI*ran0(&idum);               // map to uni. dist [0,pi]
            theta2 = PI*ran0(&idum);               // map to uni. dist [0,pi]

            phi1 = 2*PI*ran0(&idum);               // map to uni. dist [0,2pi]
            phi2 = 2*PI*ran0(&idum);               // map to uni. dist [0,2pi]

            fx += MC_Spherical_Function(r1,r2,theta1,theta2,phi1,phi2);
            sum_sigma += MC_Spherical_Function(r1,r2,theta1,theta2,phi1,phi2)*MC_Spherical_Function(r1,r2,theta1,theta2,phi1,phi2);
    }
    t3 = std::clock();
    int_MC = fx*Jacobi_D/(double(N));
    sum_sigma = sum_sigma*Jacobi_D/(double(N));
    var_MC = sum_sigma - int_MC*int_MC;
    std_MC = sqrt(var_MC/((double)N));
*/
    //computation loop: Monte carlo using importance sampling
    clock_t t2, t3;
    t2 = clock();
    lambda = 0.25;     // exp. weight
    fx = 0;  sum_sigma= 0;
    //#pragma omp parallel for private(y) reduction(+:fx) reduction(+:sum_sigma)
    for (int i=1; i <= N; i++){

        for (int j = 0; j < 2; j++){
            y = ran0(&idum);
            x[j] = -lambda*log(1. - y);
        }

        for (int j = 2; j < 4; j++){
            x[j] = PI*ran0(&idum);
        }

        for (int j = 4; j < 6; j++){
            x[j] = 2*PI*ran0(&idum);
        }

        fx += MC_Spherical_Function(x);
        sum_sigma += MC_Spherical_Function(x)*MC_Spherical_Function(x);

    }
    t3 = clock();

    int_MC = fx*Jacobi_D/(double(N));
    sum_sigma = sum_sigma*Jacobi_D/(double(N));
    var_MC = sum_sigma - int_MC*int_MC;
    std_MC = sqrt(var_MC/((double)N));

    cout << "Exact value               " << exact << endl;

    cout << "Brute force Monte carlo   " << endl;
    cout << "I:                        " << int_bMC << endl;
    cout << "Relative error:           " << fabs(int_bMC - exact)/exact << endl;
    cout << "Standard deviation:       " << std_bMC << endl;
    cout << "CPU time:                 " << (t1-t0)/((double)CLOCKS_PER_SEC) << endl;

    cout << "Monte carlo(importance sampling)  " << endl;
    cout << "I:                        " << int_MC << endl;
    cout << "Relative error:           " << fabs(int_MC - exact)/exact << endl;
    cout << "Standard deviation:       " << std_MC << endl;
    cout << "CPU time:                 " << (t3-t2)/((double)CLOCKS_PER_SEC) << endl;

}






#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

double ran0(long *idum){
   long     k;
   double   ans;

   *idum ^= MASK;
   k = (*idum)/IQ;
   *idum = IA*(*idum - k*IQ) - IR*k;
   if(*idum < 0) *idum += IM;
   ans=AM*(*idum);
   *idum ^= MASK;
   return ans;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef MASK

#define MBIG 1000000000
#define MSEED 161803398
#define MZ 0
#define FAC (1.0/MBIG)


#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran1(long *idum)
{
   int             j;
   long            k;
   static long     iy=0;
   static long     iv[NTAB];
   double          temp;

   if (*idum <= 0 || !iy) {
      if (-(*idum) < 1) *idum=1;
      else *idum = -(*idum);
      for(j = NTAB + 7; j >= 0; j--) {
         k     = (*idum)/IQ;
         *idum = IA*(*idum - k*IQ) - IR*k;
         if(*idum < 0) *idum += IM;
         if(j < NTAB) iv[j] = *idum;
      }
      iy = iv[0];
   }
   k     = (*idum)/IQ;
   *idum = IA*(*idum - k*IQ) - IR*k;
   if(*idum < 0) *idum += IM;
   j     = iy/NDIV;
   iy    = iv[j];
   iv[j] = *idum;
   if((temp=AM*iy) > RNMX) return RNMX;
   else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

// End: function ran1()



/*
    ** The function
    **         ran2()
    ** is a long periode (> 2 x 10^18) random number generator of
    ** L'Ecuyer and Bays-Durham shuffle and added safeguards.
    ** Call with idum a negative integer to initialize; thereafter,
    ** do not alter idum between sucessive deviates in a
    ** sequence. RNMX should approximate the largest floating point value
    ** that is less than 1.
    ** The function returns a uniform deviate between 0.0 and 1.0
    ** (exclusive of end-point values).
    */

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran2(long *idum)
{
  int            j;
  long           k;
  static long    idum2 = 123456789;
  static long    iy=0;
  static long    iv[NTAB];
  double         temp;

  if(*idum <= 0) {
     if(-(*idum) < 1) *idum = 1;
     else             *idum = -(*idum);
     idum2 = (*idum);
     for(j = NTAB + 7; j >= 0; j--) {
        k     = (*idum)/IQ1;
    *idum = IA1*(*idum - k*IQ1) - k*IR1;
    if(*idum < 0) *idum +=  IM1;
    if(j < NTAB)  iv[j]  = *idum;
     }
     iy=iv[0];
  }
  k     = (*idum)/IQ1;
  *idum = IA1*(*idum - k*IQ1) - k*IR1;
  if(*idum < 0) *idum += IM1;
  k     = idum2/IQ2;
  idum2 = IA2*(idum2 - k*IQ2) - k*IR2;
  if(idum2 < 0) idum2 += IM2;
  j     = iy/NDIV;
  iy    = iv[j] - idum2;
  iv[j] = *idum;
  if(iy < 1) iy += IMM1;
  if((temp = AM*iy) > RNMX) return RNMX;
  else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

// End: function ran2()




double ran3(long *idum)
{
   static int        inext, inextp;
   static long       ma[56];      // value 56 is special, do not modify
   static int        iff = 0;
   long              mj, mk;
   int               i, ii, k;

   if(*idum < 0 || iff == 0) {                 // initialization
      iff    = 1;

      mj     = MSEED - (*idum < 0 ? -*idum : *idum);
      mj    %= MBIG;
      ma[55] = mj;                            // initialize ma[55]

      for(i = 1, mk = 1; i <= 54; i++) {      // initialize rest of table
         ii     = (21*i) % 55;
     ma[ii] = mk;
     mk     = mj - mk;
     if(mk < MZ) mk += MBIG;
     mj = ma[ii];
      }

      for(k = 1; k <= 4; k++) {   // randimize by "warming up" the generator
         for(i = 1; i <= 55; i++) {
        ma[i] -= ma[1 + (i + 30) % 55];
        if(ma[i] < MZ) ma[i] += MBIG;
     }
      }

      inext  =  0;              // prepare indices for first generator number
      inextp = 31;              // 31 is special
      *idum  = 1;
   }

   if(++inext == 56)  inext  = 1;
   if(++inextp == 56) inextp = 1;
   mj = ma[inext] - ma[inextp];
   if(mj < MZ) mj += MBIG;
   ma[inext] = mj;
   return mj*FAC;
}
#undef MBIG
#undef MSEED
#undef MZ
#undef FAC

// End: function ran3()
