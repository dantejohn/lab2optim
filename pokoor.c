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

#define Aa 2
#define Bb -1.3
#define C 0.02
#define D 0.14


double e[5] = {0.1, 0.01, 0.001, 0.0001, 0.00001};
int N0, N1, N2, N, k, i;


double
df (double x1, double x2) {
  N0++;
  return Aa * x1 + Bb * x2 + exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx1 (double x1, double x2) {
  N1++;
  return Aa + 2 * C * x1 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

double
dfx2 (double x1, double x2) {
  N1++;
  return Bb + 2 * D * x2 * exp(C * pow(x1, 2) + D * pow(x2, 2));
}

void
pokoor(){
  int j,l1,l2,choos,des;
  double a,b,d,ymin,x1min,x2min,alpha=0.03;
  N0=0; N1=0; N2=0; N=0; k=0;
  double x[2][3000];
  double y[10];

  x[0][0] = -1;
  x[1][0] = 0;
  
  metka:
    x[0][2*k+1] = x[0][2*k] - alpha*dfx1(x[0][2*k],x[1][2*k]);
    x[1][2*k+1]=x[1][2*k];
    if (i==1) {
      printf("x[1][1] = %f\nx[2][1] = %f\n", x[0][2*k+1], x[1][2*k+1]);
    }
    x[0][2*k+2] = x[0][2*k+1];
    x[1][2*k+2] = x[1][2*k+1] - alpha*dfx2(x[0][2*k+1], x[1][2*k+1]);
    d = pow ((pow(x[0][2*k+2]-x[0][2*k],2)+pow(x[1][2*k+2]-x[1][2*k],2)), 0.5);
    if (d>e[i]) {
      k++;
      if (i==1) {
        printf("k=%d\n", k+1);
      }
      goto metka;
    }
    else {
      x1min = x[0][2*k+2];
      x2min = x[1][2*k+2];
      ymin = df(x1min, x2min);
      printf("X1min = %f\nX2min = %f\nYmin = %f\n N0 = %d\n N1 = %d\n N = %d\n k = %d\n", 
              x1min, x2min, ymin, N0-1, N1, N0+N1-1, k+1);
    }
}

int
main() {
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  pokoor();
}
return 0;
}