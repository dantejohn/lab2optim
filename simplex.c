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

void
simplex(FILE *file) {
  double x[2][200]; x[0][0] = -1; x[0][1] = 0;
  double r = 1, E;
  x[0][1] = x[0][0] + r; x[1][1] = x[1][0];
  x[0][2]= x[0][0]; x[1][2] = x[1][0] + r;
  if (i==0) {
    fprintf (file, "%f\t%f\n%f\t%f\n", x[0][1], x[1][1], x[0][2], x[1][2]);
  }
  double y[4];
  y[0]=df(x[0][0],x[1][0]);
  y[1]=df(x[0][1],x[1][1]);
  y[2]=df(x[0][2],x[1][2]);
  double c1,c2,u1,u2;
  int l1,l2, iter=0;
  metka:
    l1=0; l2=0;
    int j,k;
    for(j=0;j<3;j++) {
      if (y[j]<y[l1]) {
        l1 =j;
      }
    }
    for (k=0; k<3; k++) {
      if (y[k]>y[l2]) {
        l2=k;
      } 
    }
    if (r>e[i]) {
      c1=0,c2=0;
      for(j=0;j<3;j++) {
        if(j!=l2) {
          c1+=x[0][j]; c2+=x[1][j];
        }
      }
      c1/=2;    c2/=2;
      u1=2*c1-x[0][l2];
      u2=2*c2-x[1][l2];
      y[3]=df(u1,u2);
      if(y[3]<y[l2]) { 
        x[0][l2]=u1;
        x[1][l2]=u2;
        y[l2]=y[3];
        if (i==0) {
          fprintf(file, "%f\t%f\n", x[0][l2], x[1][l2]);
        }
      }
      else  { 
        for(j=0;j<3;j++) {
          if(j!=l1) {
            x[0][j]=(x[0][j]+x[0][l1])/2;
            x[1][j]=(x[1][j]+x[1][l1])/2;
            y[j]=df (x[0][j],x[1][j]);
            if (i==0) {
              fprintf(file, "%f\t%f\n", x[0][j], x[1][j]);
            }
          }
        }
        r=r/2;
      } 
      iter++;
      goto metka;
    }
    else {
      double x1min, x2min, ymin;
      x1min = x[0][l1];
      x2min = x[0][l1];
      ymin = y[l1];
      fprintf(file, "%f\t%f\t%f\t%d\t%d\n", 
             x1min, x2min, ymin, N0, iter);
    }
}

int
main() {
  FILE *file = fopen("result/simplex.txt", "w+");
  for (i=0; i < 5; i++) {
  printf("Iteration %d with e = %lf\n", i+1, e[i]);
  simplex(file);
  }
  fclose(file);
  return 0;
}
