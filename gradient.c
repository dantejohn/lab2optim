/*
##################################################
##################################################
####                                          ####
####      LabWork 2 Optimization Methods      ####
####        Student: Eugene Dementyev         ####
####          Group: BZI-104m                 ####
####                                          ####
##################################################
##################################################
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define A 2
#define B -1.3
#define C 0.02
#define D 0.14

double e[5] = {0.1, 0.01, 0.001, 0.0001, 0.00001};
int N0, N1, N2, N, k, i;



void config (void);
void gradopt (void);

double
dz (double x1, double x2) {
  N0++;
  return A * x1 + B * x2 + exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dzdx1 (double x1, double x2) {
  N1++;
  return A + 2 * C * x1 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dzdx2 (double x1, double x2) {
  N1++;
  return B + 2 * D * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

int
main() {
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  gradopt();
  }

  return 0;
}

void
gradopt() {
  int k, m;
  double a, b, d, ymin, x1min, x2min, alpha, y1, y2;
  double z1, z2, p, alpmin, g1, g2;
  double e2 = 0.00025;
  double x[10000][2];
  x[0][0] = -5; x[0][1] = 0;
  k = 0; N0 = 0; N1 = 0; N2 = 0; N = 0; alpha = 2.2;
  z1 = dzdx1 (x[0][0], x[0][1]); z2 = dzdx2 (x[0][0], x[0][1]);
mm1:
  m = 0;
  y1 = dz (x[k][0],x[k][1]);
metka:
  y2 = dz (x[k][0]-(m+1)*alpha*z1,x[k][1]-(m+1)*alpha*z2);
  if (y2 < y1) {
    m++; y1=y2; goto metka;
  }
  else {
    b = (m+1)*alpha;
    if (m == 0) {
      a = 0;
    }
    else {
      a = (m-1)*alpha;
    }
  }
  do {
    p = (a+b)/2;
    g1 = dz (x[k][0]-(p-0.000001)*z1,x[k][1]-(p-0.000001)*z2);
    g2 = dz (x[k][0]-(p+0.000001)*z1,x[k][1]-(p+0.000001)*z2);
    if (g1 < g2) {
      b = p + 0.000001;
    }
    else {
      a = p - 0.000001;
    }
  } while ((b-a)/2>e[i]);
  alpmin = (a+b)/2;
  x[k+1][0]=x[k][0]-alpmin*z1;
  x[k+1][1]=x[k][1]-alpmin*z2;
  if (i==0) {
    printf("\nk=%d", k+1 );
    printf("\nx[1][1]= %lf", x[k+1][0]);
    printf("\nx[1][2]= %lf", x[k+1][1]);
  }
  z1=dzdx1(x[k+1][0],x[k+1][1]);
  z2=dzdx2(x[k+1][0],x[k+1][1]);
  d = pow (z1*z1+z2*z2, 0.5);
  if (d > e2) {
    k++; goto mm1;
  }
  else {
    x1min = x[k+1][0];
    x2min = x[k+1][1];
    ymin = dz (x1min, x2min);
    N = N0 + N1 -1;
    printf ("\n%lf; %lf; %lf; %d; %d; %d; k = %d;\n", x1min, x2min, ymin, N0-1, N1, N, k+1);
  }

}